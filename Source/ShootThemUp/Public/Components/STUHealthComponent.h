// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Health,meta=(ClampMin="0.0",ClampMax="1000.0"))
	float MaxHealth = 100.f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		bool bAutoHeal = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealDelay = 3.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealModifier = 5.f;



private:
	float Health = 0.f;
	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle HealTimerHandle;
	void HealUpdate();
	void SetHealth(float NewHealth);



public:	
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable,Category=Health)
		bool IsDead()const { return FMath::IsNearlyZero(Health); }
		
	UFUNCTION(BlueprintCallable, Category = Health)
		float GetHealthPercent()const { return Health / MaxHealth; }
};
