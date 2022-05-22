#include "Cannon.h"
#include "CanonShotProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ACannon::Fire()
{
	if (!ReadyToFire || (AmmoCount <= 0))
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Reloading is in progress or have no ammo");
		return;
	}

	AmmoCount--;
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");

		FActorSpawnParameters params;
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

		GetWorld()->SpawnActor<ACanonShotProjectile>(CanonShotClass, Location, Rotation, params);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFire || (AmmoCount <= 0))
	{
		return;
	}

	AmmoCount--;
	ReadyToFire = false;

	Burst(); // first instant shot
	Special_BurstShotCount++;

	GetWorld()->GetTimerManager().SetTimer(BurstHandle, this, &ACannon::Burst, Special_BurstFireDelay, true);
}


//RMB alt fire mode, automatic. 3-round burst, costs 1 ammo point
void ACannon::Burst()
{
	Special_BurstShotCount++;

	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 0.05f, FColor::Red, "SpecialFire - projectile");

		FActorSpawnParameters params;
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

		GetWorld()->SpawnActor<ACanonShotProjectile>(CanonShotClass, Location, Rotation, params);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 0.05f, FColor::Red, "SpecialFire - trace");
	}

	if (Special_BurstSize < Special_BurstShotCount) {
		Special_BurstShotCount = 0;

		GetWorld()->GetTimerManager().ClearTimer(BurstHandle);

		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
	}
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}
