// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"


class USTUAIPerceptionComponent;


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASTUAIController();
		


protected:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AIComponents)
		USTUAIPerceptionComponent* STUAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName FocusOnKeyName = "EnemyActor";



private:

	AActor* GetFocusOnActor() const;



};
