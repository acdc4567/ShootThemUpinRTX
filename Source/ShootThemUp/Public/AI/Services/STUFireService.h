// ShootThemUp Game. All Rights Reserved...

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFireService.generated.h"


class ASTUAIController;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFireService : public UBTService
{
	GENERATED_BODY()
public:
	USTUFireService();




protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FBlackboardKeySelector EnemyActorKey;

	
	bool HasAim;
	


	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	ASTUAIController* Controller;







};
