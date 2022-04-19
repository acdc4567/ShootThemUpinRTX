// ShootThemUp Game. All Rights Reserved...


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"





DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);


ASTUBaseWeapon::ASTUBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = 0;
	
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);





}



void ASTUBaseWeapon::BeginPlay() {
	Super::BeginPlay();
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT(""));
	checkf(DefaultAmmo.Clips > 0, TEXT(""));

	CurrentAmmo = DefaultAmmo;

}

void ASTUBaseWeapon::StartFire(){
	
	
	

}

void ASTUBaseWeapon::StopFire(){

	
}



void ASTUBaseWeapon::MakeShot(){
	

}

APlayerController* ASTUBaseWeapon::GetPlayerController() const{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)return nullptr;
	return Player->GetController<APlayerController>();
	
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const{
	const auto Controller = GetPlayerController();
	if (!Controller)return 0;

	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	return 1;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const{


	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return 0;

	TraceStart = ViewLocation;
	
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return 1;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd){
	if (!GetWorld())return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

}

void ASTUBaseWeapon::DecreaseAmmo(){
	if (CurrentAmmo.Bullets == 0) {
		UE_LOG(LogTemp, Warning, TEXT(" ClipIsEmpty"));
		return;
	}
	CurrentAmmo.Bullets--;
	LogAmmo();
	if (IsClipEmpty()&&!IsAmmoEmpty()) {
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty() const{



	return !CurrentAmmo.bInfinite&&CurrentAmmo.Clips==0&&IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const{



	return CurrentAmmo.Bullets==0;
}

void ASTUBaseWeapon::ChangeClip(){

	
	if (!CurrentAmmo.bInfinite) {
		if (CurrentAmmo.Clips==0) {
			UE_LOG(LogTemp, Warning, TEXT("No More Clips"));
			return;
		}
		CurrentAmmo.Clips--;

	}
	
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogTemp, Warning, TEXT("--------ChangeClip-------"));

}

bool ASTUBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets<DefaultAmmo.Bullets&&CurrentAmmo.Clips>0;
}

void ASTUBaseWeapon::LogAmmo(){

	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
	AmmoInfo += CurrentAmmo.bInfinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *AmmoInfo);
}




