// ShootThemUp Game. All Rights Reserved...


#include "AI/Services/STUFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"
#include "AI/STUAIController.h"



USTUFireService::USTUFireService() {

	NodeName = "Fire";


}



void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	Controller = Cast<ASTUAIController>(OwnerComp.GetAIOwner());

	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if (Controller) {
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

		if (WeaponComponent) {
			
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();

			

		}
	}


	
	

	Super::TickNode(OwnerComp,  NodeMemory,  DeltaSeconds);





}




