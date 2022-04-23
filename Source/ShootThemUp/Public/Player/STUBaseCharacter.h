// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USpringArmComponent* SpringArmComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UTextRenderComponent* HealthText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		FVector2D LandedDamage = FVector2D(10.f, 50.f);
	UPROPERTY(EditDefaultsOnly, Category = Material)
		FName MaterialColorName = "PrimaryArmorColor";
	

	virtual void OnDeath();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Movement)
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = Movement)
		float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

private:

	bool bWantsToRun=0;
	bool bIsMovingForward = 0;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void TurnAround(float Amount);
	void OnStartRunning();
	void OnStopRunning();

	
	void OnHealthChanged(float Health);
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	





public:




};
