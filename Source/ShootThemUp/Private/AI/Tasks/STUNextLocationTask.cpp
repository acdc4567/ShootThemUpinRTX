// ShootThemUp Game. All Rights Reserved...


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"




USTUNextLocationTask::USTUNextLocationTask() {

	NodeName = "NextLocation";

}





EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	Super::ExecuteTask(OwnerComp, NodeMemory);
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard)return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!Pawn)return EBTNodeResult::Failed;

	auto Location = Pawn->GetActorLocation();
	if (!bSelfCenter) {
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));

		if (!CenterActor)return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();

	}




	FNavLocation NavLocation;
	const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if (!Found)return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;



}




