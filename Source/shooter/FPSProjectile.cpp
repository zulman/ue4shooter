// Fill out your copyright notice in the Description page of Project Settings.

#include "shooter.h"
#include "FPSProjectile.h"


AFPSProjectile::AFPSProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);
	
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
	//CollisionComp->SetCollisionEnabled(ECollisionEnabled::);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//UE_LOG(LogTemp, Error, TEXT("%s"), *CollisionComp->BodyInstance.GetCollisionProfileName().ToString());

	RootComponent = CollisionComp;
	

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	
}
//
//// Sets default values
//AFPSProjectile::AFPSProjectile()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFPSProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		// set the projectile's velocity to the desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void AFPSProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("COLLISION 0"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("COLLISION 1"));
		OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("COLLISION 2"));
	}
}