// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();


	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USphereComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float DamageRadius=200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float DamageAmount= 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool DoFullDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float LifeSeconds = 5.f;

private:
	FVector ShotDirection;


	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;


};
