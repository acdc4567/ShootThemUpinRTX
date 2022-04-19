// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
		//ASTUProjectile

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TSubclassOf<ASTUProjectile> ProjectileClass;

	virtual void MakeShot() override;






};
