// ShootThemUp Game. All Rights Reserved...


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/STUEquipFinishedAnimNotify.h"
#include "Animation/STUReloadFinishedAnimNotify.h"
#include "Animation/AnimUtils.h"



DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);




USTUWeaponComponent::USTUWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = 0;

	
}



void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == 2, TEXT(""));

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){

	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons) {
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();

	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);



}

void USTUWeaponComponent::StartFire(){

	if (!CanFire())return;
	CurrentWeapon->StartFire();


}

void USTUWeaponComponent::StopFire(){
	if (!CurrentWeapon)return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon(){
	if (!CanEquip())return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);


}




void USTUWeaponComponent::SpawnWeapons() {

	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character|| !GetWorld())return;

	for (auto OneWeaponData : WeaponData) {
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon)continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon,Character->GetMesh(),WeaponArmorySocketName);

	}

	
	
	

	
	


}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName){
	
	if (!Weapon || !SceneComponent)return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, 0);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	



}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex){
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) {
		UE_LOG(LogTemp, Warning, TEXT("InvalidNumber of Weapons"));
		return;
	}


	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())return;

	if (CurrentWeapon) {
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);

	}

	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;


	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	bEquipAnimInProgress = 1;
	PlayAnimMontage(EquipAnimMontage);

}

void USTUWeaponComponent::Reload() {
	
	ChangeClip();

}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation){
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())return;

	Character->PlayAnimMontage(Animation);



}

void USTUWeaponComponent::InitAnimations(){
	


	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify) {
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("EquipFinishedNotify Not Set"));
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData) {
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage );
		if (!ReloadFinishedNotify) {
			UE_LOG(LogTemp, Warning, TEXT("ReloadFinishedNotify Not Set"));
			checkNoEntry();
		}
	
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);


		
	}







}

bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const{
	if (CurrentWeapon) {
		UIData = CurrentWeapon->GetUIData();
		return 1;

	}
	return 0;
}

bool USTUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const{
	if (CurrentWeapon) {
		AmmoData = CurrentWeapon->GetAmmoData();
		return 1;

	}
	return 0;
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount){

	for (const auto Weapon:Weapons) {
		if (Weapon && Weapon->IsA(WeaponType)) {
			return Weapon->TryToAddAmmo(ClipsAmount);

		}
	}


	return false;
}





void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp){
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh())return;


	bEquipAnimInProgress = 0;

	

}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp) {
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh())return;


	bReloadAnimInProgress = 0;



}

bool USTUWeaponComponent::CanFire() const{


	return CurrentWeapon&&!bEquipAnimInProgress&&!bReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const{

	return !bEquipAnimInProgress&&!bReloadAnimInProgress; 
}


bool USTUWeaponComponent::CanReload() const {


	return CurrentWeapon && !bEquipAnimInProgress && !bReloadAnimInProgress && CurrentWeapon->CanReload();;
}

void USTUWeaponComponent::OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon){
	if (!AmmoEmptyWeapon)return;
	if (CurrentWeapon == AmmoEmptyWeapon) {
		ChangeClip();
	}
	else {
		for (const auto Weapon:Weapons) {
			if (Weapon==AmmoEmptyWeapon) {
				Weapon->ChangeClip();
			}
		}
	}
}

void USTUWeaponComponent::ChangeClip(){
	if (!CanReload())return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	bReloadAnimInProgress = 1;
	PlayAnimMontage(CurrentReloadAnimMontage);
}




