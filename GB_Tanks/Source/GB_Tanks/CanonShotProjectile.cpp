#include "CanonShotProjectile.h"

ACanonShotProjectile::ACanonShotProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon shot "));
	Mesh->SetupAttachment(RootComponent);
}

