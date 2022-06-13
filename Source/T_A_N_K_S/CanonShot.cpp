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
		else
		{
			UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
					FVector forceVector = OtherActor->GetActorLocation() - GetActorLocation();
					forceVector.Normalize();
					mesh->AddImpulse(forceVector * PushForce, NAME_None, 	true);
				}
			}
		}

		Destroy();
	}
}

// lesson 8-2b
TArray<FHitResult> ACanonShot::CheckExplosionCanDealDamageActor() {
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);

	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;

	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";

	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;

	bool sweepResult = GetWorld()->SweepMultiByChannel
	(
		AttackHit,
		startPos,
		endPos,
		Rotation,
		ECollisionChannel::ECC_Visibility,
		Shape,
		params
	);

	GetWorld()->DebugDrawTraceTag = "Explode Trace";

	return AttackHit;
}

void ACanonShot::Explode()
{
	// lesson 8-2a
	if (!bCanExplode) return;

	TArray<FHitResult> AttackHit = CheckExplosionCanDealDamageActor();

	if (AttackHit.Num() > 0)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
				continue;
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
			if (damageTakerActor)
			{
				damageTakerActor->TakeHit(fDamage);
			}
			else
			{
				UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
				if (mesh)
				{
					if (mesh->IsSimulatingPhysics())
					{
						FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
						forceVector.Normalize();
						// lesson 8-1
						//mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
						mesh->AddForce(forceVector * PushForce, NAME_None, true);
					}
				}
			}
		}
	}

}