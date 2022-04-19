// ShootThemUp Game. All Rights Reserved...


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"



USTUHealthComponent::USTUHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = 0;



}



void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner) {

		ComponentOwner->OnTakeAnyDamage.AddDynamic(this,&USTUHealthComponent::OnTakeAnyDamage);
	}




}
void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	if (Damage <= 0.f || IsDead()||!GetWorld())return;
	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (IsDead()) {
		OnDeath.Broadcast();
	}
	else if (bAutoHeal) {
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USTUHealthComponent::HealUpdate,HealUpdateTime,1,HealDelay);


	}
	



}

void USTUHealthComponent::HealUpdate(){
	SetHealth(Health + HealModifier);
	if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}

}

void USTUHealthComponent::SetHealth(float NewHealth){
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(Health);



}




