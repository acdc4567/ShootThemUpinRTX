// ShootThemUp Game. All Rights Reserved...


#include "Pickups/STUAmmoPickup.h"
#include "Weapon/STUBaseWeapon.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"



bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn){
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent||HealthComponent->IsDead()) {
		return 0;
	}

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if (!WeaponComponent)return 0;



    return WeaponComponent->TryToAddAmmo(WeaponType,ClipsAmount);
}
