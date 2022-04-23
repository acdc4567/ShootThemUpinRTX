// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class UAnimMontage;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const; 
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType,int32 ClipsAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TArray<FWeaponData> WeaponData;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName WeaponEquipSocketName="WeaponSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		UAnimMontage* EquipAnimMontage;

	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTUBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	bool CanFire() const;
	bool CanEquip() const;


	void EquipWeapon(int32 WeaponIndex);


	



private:	
	
	void SpawnWeapons();
	
	

	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage=nullptr;

		bool bEquipAnimInProgress = 0;

		bool bReloadAnimInProgress = 0;


	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	
	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	
	bool CanReload() const;

	void OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();

	


	




};
