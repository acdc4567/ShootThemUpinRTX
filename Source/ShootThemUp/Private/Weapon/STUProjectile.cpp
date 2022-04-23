// ShootThemUp Game. All Rights Reserved...


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"




ASTUProjectile::ASTUProjectile()
{

	PrimaryActorTick.bCanEverTick = 0;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius (5.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = 1;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 3000.f;
	MovementComponent->ProjectileGravityScale = .7f;


	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");


}


void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), 1);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);

}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){

	if (!GetWorld())return;

	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFullDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Cyan, 0, 5.f);
	
	WeaponFXComponent->PlayImpactFX(Hit);
	Destroy();



}

AController* ASTUProjectile::GetController() const{

	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn?Pawn->GetController():nullptr;
}


