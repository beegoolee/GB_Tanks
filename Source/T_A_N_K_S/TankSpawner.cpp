#include "TankSpawner.h"

ATankSpawner::ATankSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collider"));
	RootComponent = HitCollider;

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	BodyMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	WreckedBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WreckedBody"));
	WreckedBodyMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	GatesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gates"));
	GatesMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	DeathVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathVFX"));
	DeathVFX->SetupAttachment(RootComponent);

	DeathSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathSFX"));
	DeathSFX->SetupAttachment(RootComponent);

	SpawnVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnVFX"));
	SpawnVFX->SetupAttachment(RootComponent);

	SpawnSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("SpawnSFX"));
	SpawnSFX->SetupAttachment(RootComponent);
}

void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle _spawnTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		_spawnTimerHandle,
		this,
		&ATankSpawner::TryToRespawnTank,
		fSpawnInterval,
		true,
		fSpawnInterval
	);

	BodyMesh->SetVisibility(true);
	WreckedBodyMesh->SetVisibility(false);
}

void ATankSpawner::TryToRespawnTank() {
	if (iSpawnedTanksCount < iMaxTanksCount && !isDead) {
		FVector SpawningLoc = SpawnPoint->GetComponentLocation();
		FRotator SpawningRot = SpawnPoint->GetComponentRotation();

		GetWorld()->SpawnActor<ATankBase>(SpawnTankClass, SpawningLoc, SpawningRot);
		iSpawnedTanksCount++;

		SpawnVFX->ActivateSystem();
		SpawnSFX->Play();
	}
}

void ATankSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankSpawner::TakeHit(float DamageValue)
{
	fCurrentHP -= DamageValue;
	fCurrentHP = FMath::Clamp(fCurrentHP, 0.0f, fMaxHP);

	if (fCurrentHP == 0.0f) {
		Death();
	}
}

void ATankSpawner::Death()
{
	DeathVFX->ActivateSystem();
	DeathSFX->Play();

	isDead = true;
	BodyMesh->SetVisibility(false);
	WreckedBodyMesh->SetVisibility(true);
}
