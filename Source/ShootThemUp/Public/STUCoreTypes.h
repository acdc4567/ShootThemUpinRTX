#pragma once

#include "STUCoreTypes.generated.h"
//Weapon

class ASTUBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature,ASTUBaseWeapon*);



USTRUCT(BlueprintType)
struct FAmmoData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!bInfinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		bool bInfinite;

};

USTRUCT(BlueprintType)
struct FWeaponData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!bInfinite"))
		UAnimMontage* ReloadAnimMontage;



};

USTRUCT(BlueprintType)
struct FWeaponUIData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!bInfinite"))
		UTexture2D* CrosshairIcon;



};

//Health
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


//VFX

class UNiagaraSystem;


USTRUCT(BlueprintType)
struct FDecalData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		UMaterialInterface* Material;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		FVector Size = FVector(10.f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		float LifeTime = 5.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		float FadeOutTime = .2f;

};


USTRUCT(BlueprintType)
struct FImpactData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		UNiagaraSystem* NiagaraEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
		FDecalData DecalData;
};



USTRUCT(BlueprintType)
struct FGameData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game,meta=(ClampMin="1",ClampMax="100"))
		int32 PlayersNum=2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, meta = (ClampMin = "1", ClampMax = "10"))
		int32 RoundsNum = 4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game, meta = (ClampMin = "3", ClampMax = "300"))
		int32 RoundTime = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FLinearColor DefaultTeamColor = FLinearColor::Red;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FLinearColor> TeamColors ;

};






