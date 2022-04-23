// ShootThemUp Game. All Rights Reserved...


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


ASTURifleWeapon::ASTURifleWeapon() {

	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
	
	

}



void ASTURifleWeapon::BeginPlay() {
	Super::BeginPlay();
	check(WeaponFXComponent);

	if (RifleMuzzleParticles)
		MuzzleVFX = UGameplayStatics::SpawnEmitterAttached(RifleMuzzleParticles, WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator);

	
	SetMuzzleFXVisibility(0);

}





void ASTURifleWeapon::StartFire(){
	SetMuzzleFXVisibility(1);
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, 1);
	MakeShot();

}

void ASTURifleWeapon::StopFire(){
	SetMuzzleFXVisibility(0);
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::SetMuzzleFXVisibility(bool Visible){
	
	

	if (MuzzleVFX && RifleMuzzleParticles && RifleTraceParticles &&Visible) {
		MuzzleVFX = UGameplayStatics::SpawnEmitterAttached(RifleMuzzleParticles, WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator);
		TraceVFX= UGameplayStatics::SpawnEmitterAttached(RifleTraceParticles, WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator);
		TraceVFX->SetVectorParameter(FName("ShockBeamEnd"), TraceFXEnd);
	}
	else	if (MuzzleVFX && !Visible) {
		MuzzleVFX->DeactivateSystem();
	}
}



void ASTURifleWeapon::MakeShot(){

	if (!GetWorld() || IsAmmoEmpty()) {
		StopFire();
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) {
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit) {
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		
		WeaponFXComponent->PlayImpactFX(HitResult);
		
		//WeaponFXComponent->HitResultData(HitResult,HitRut);
	
	}
	else {
		

	}
	DecreaseAmmo();
	

}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return 0;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return 1;
}


void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult) {
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}




