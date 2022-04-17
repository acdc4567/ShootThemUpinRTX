// ShootThemUp Game. All Rights Reserved...


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STIIceDamageType.h"



USTUHealthComponent::USTUHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = 0;



}



void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner) {

		ComponentOwner->OnTakeAnyDamage.AddDynamic(this,&USTUHealthComponent::OnTakeAnyDamage);
	}




}
void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	Health -= Damage;
	
	if (DamageType) {
		if (DamageType->IsA<USTUFireDamageType>()) {
			//UE_LOG(LogTemp, Warning, TEXT("SoHot!!!"));
		}
		else if (DamageType->IsA<USTIIceDamageType>()) {
			//UE_LOG(LogTemp, Warning, TEXT("SoCold!!!"));

		}
	}



}




