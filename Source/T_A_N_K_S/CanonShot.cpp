#include "CanonShot.h"

ACanonShot::ACanonShot()
{
	PrimaryActorTick.bCanEverTick = true;

	ShotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotMesh"));
	RootComponent = ShotMesh;
}

void ACanonShot::BeginPlay()
{
	Super::BeginPlay();

	ShotMesh->OnComponentBeginOverlap.AddDynamic(this, &ACanonShot::OnMeshOverlapBegin);
}

void ACanonShot::Start()
{
	FTimerHandle _moveTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_moveTimerHandle, this, &ACanonShot::Move, fShotMoveRate, true, fShotMoveRate);

	FTimerHandle _shotDestroyerTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_shotDestroyerTimerHandle, this, &ACanonShot::SelfDestroyByTimer, LIFE_TIME_SEC, false, LIFE_TIME_SEC);
}

void ACanonShot::SelfDestroyByTimer() {
	Destroy();
}

void ACanonShot::Move()
{
	FVector newLoc = GetActorLocation() + GetActorForwardVector() * fShotSpeed;
	SetActorLocation(newLoc);
}

void ACanonShot::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	AActor* owner = GetOwner();

	if (OtherActor != owner)
	{	
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			damageTakerActor->TakeHit(fDamage);
		}

		Destroy();
	}
}

