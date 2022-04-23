// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"


class USTUWeaponFXComponent;
class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	

public:

	ASTURifleWeapon();


	virtual void StartFire() override;
	virtual void StopFire() override;
	void SetMuzzleFXVisibility(bool Visible);

protected:
	virtual void BeginPlay() override;

	virtual void MakeShot() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		float TimeBetweenShots = .1f;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		float BulletSpread = 1.5f;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, Category = Weapon)
		float DamageAmount = 10.f;


	UPROPERTY(VisibleAnywhere, Category = VFX)
		USTUWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly,  BlueprintReadWrite,Category = VFX)
		UParticleSystem* RifleMuzzleParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		UParticleSystem* RifleTraceParticles;

	UPROPERTY(VisibleAnywhere, Category = VFX)
		UParticleSystemComponent* MuzzleVFX;

	FVector TraceFXEnd;

	UPROPERTY(VisibleAnywhere, Category = VFX)
		UParticleSystemComponent* TraceVFX;


	FHitResult HitRut;
private:

	FTimerHandle ShotTimerHandle;






};
