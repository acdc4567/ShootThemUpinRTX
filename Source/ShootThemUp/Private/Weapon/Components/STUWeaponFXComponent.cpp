// ShootThemUp Game. All Rights Reserved...


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystemComponent.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	


	PrimaryComponentTick.bCanEverTick = 0;

	



}



void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit){
	auto Impactdata = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("MaterialValid"));
		const auto PhysMat = Hit.PhysMaterial.Get();
		//UE_LOG(LogTemp, Warning, TEXT("Material: %s"),*PhysMat.GetName());

		if (ImpactDataMap.Contains(PhysMat)){
			UE_LOG(LogTemp, Warning, TEXT("MapContainsPhysMat"));
			Impactdata = ImpactDataMap[PhysMat];

		}

	}
	if (ImpactParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, Hit.ImpactPoint);

	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Impactdata.NiagaraEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());

	auto DecalComponent= UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),Impactdata.DecalData.Material
		,Impactdata.DecalData.Size,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());

	if (DecalComponent) {
		DecalComponent->SetFadeOut(Impactdata.DecalData.LifeTime, Impactdata.DecalData.FadeOutTime);
	}

}












