// ShootThemUp Game. All Rights Reserved...


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Controller.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"





DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit):
	Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = 1;
	SpringArmComponent->SocketOffset =FVector (0.f,100.f,90.f);


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	HealthText = CreateDefaultSubobject<UTextRenderComponent>("HealthText");
	HealthText->SetupAttachment(GetRootComponent());
	HealthText->SetOwnerNoSee(1);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");

}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthText);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());

	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);

	





}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();
	

	//TakeDamage(0.1f, FDamageEvent{}, Controller, this);






}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ASTUBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &ASTUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &ASTUBaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);


}

bool ASTUBaseCharacter::IsRunning() const{
	return bWantsToRun&&bIsMovingForward&&!GetVelocity().IsNearlyZero();
}

float ASTUBaseCharacter::GetMovementDirection() const{
	if (GetVelocity().IsNearlyZero())return 0.f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount){
	bIsMovingForward = Amount > 0.f;
	if (Amount == 0.f)return;
	AddMovementInput(GetActorForwardVector(), Amount);

}

void ASTUBaseCharacter::MoveRight(float Amount){
	if (Amount == 0.f)return;
	AddMovementInput(GetActorRightVector(), Amount);

}

void ASTUBaseCharacter::LookUp(float Amount){

	AddControllerPitchInput(Amount * .7f);
}

void ASTUBaseCharacter::TurnAround(float Amount){
	AddControllerYawInput(Amount * .7f);
}

void ASTUBaseCharacter::OnStartRunning(){

	bWantsToRun = 1;

}

void ASTUBaseCharacter::OnStopRunning(){

	bWantsToRun = 0;

}

void ASTUBaseCharacter::OnDeath(){
	PlayAnimMontage(DeathAnimMontage);
	//UE_LOG(LogBaseCharacter, Display, TEXT("Player %s isDead"), *GetName());
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.f);
	if (Controller) {
		Controller->ChangeState(NAME_Spectating);

	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WeaponComponent->StopFire();



}

void ASTUBaseCharacter::OnHealthChanged(float Health){

	HealthText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));


}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit){
	const auto FallVelocityZ = -GetVelocity().Z;
	//UE_LOG(LogTemp, Warning, TEXT("fALLvELOCITY:%f"), FallVelocityZ);
	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
		//UE_LOG(LogTemp, Warning, TEXT("OnLanded:%f"), FinalDamage);


	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);

}











