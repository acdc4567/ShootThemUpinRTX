// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;






UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();


	void ChangeClip();
	bool CanReload() const;

	FOnClipEmptySignature OnClipEmpty;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);

	void SpawnMuzzleEffects();


	bool IsAmmoEmpty() const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		FAmmoData DefaultAmmo {30,10,0};

	virtual void MakeShot();
	
	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd)const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		UParticleSystem* MuzzleParticles;


	UPROPERTY(EditAnywhere, Category = Weapon)
		float TraceMaxDistance = 50000.f;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		FName MuzzleSocketName = "MuzzleFlashSocket";

	void DecreaseAmmo();
	bool IsClipEmpty() const;
	bool IsAmmoFull() const;
	void LogAmmo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		FWeaponUIData UIData;


private:	
	
	FAmmoData CurrentAmmo;
	

	




};
