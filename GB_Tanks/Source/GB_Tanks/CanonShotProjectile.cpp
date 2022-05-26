#include "CanonShotProjectile.h"

ACanonShotProjectile::ACanonShotProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotMesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACanonShotProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void ACanonShotProjectile::Move()
{
	FVector NextPos = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	this->SetActorLocation(NextPos);
}

void ACanonShotProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ACanonShotProjectile::Move, MoveRate, true, MoveRate);
}

void ACanonShotProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(),
		*OtherActor->GetName());
	OtherActor->Destroy();
	this->Destroy();
}

