// ShootThemUp Game. All Rights Reserved...


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"


DEFINE_LOG_CATEGORY_STATIC(BAseCharacterLog, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit):
	Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = 1;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	HealthText = CreateDefaultSubobject<UTextRenderComponent>("HealthText");
	HealthText->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthText);



}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();
	HealthText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));


	//TakeDamage(0.1f, FDamageEvent{}, Controller, this);






}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ASTUBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &ASTUBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &ASTUBaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);



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


