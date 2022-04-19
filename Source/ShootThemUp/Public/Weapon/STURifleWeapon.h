// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:

	virtual void MakeShot() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		float TimeBetweenShots = .1f;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		float BulletSpread = 1.5f;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, Category = Weapon)
		float DamageAmount = 10.f;


private:

	FTimerHandle ShotTimerHandle;






};
