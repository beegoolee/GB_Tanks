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

void ACanonShotProjectile::AddScoreOnKill()
{

}

void ACanonShotProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		IIScorable* scorableActor = Cast<IIScorable>(OtherActor);


		bool isTargetScorable = false;

		if (scorableActor) {
			isTargetScorable = true;
		}

		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;
			damageTakerActor->TakeDamage(damageData);

			if (!damageTakerActor && isTargetScorable) {
				// даем очки, ибо актор был уничтожен как мертвый, и в то же время мы зафиксировали тот факт, что он дает очки. TODO

				UE_LOG(LogTemp, Warning, TEXT("Get ScorePoints by kill"));
				

				if (OnKillEnemy.IsBound()) {
					OnKillEnemy.Broadcast();
				}
			}
		}
	}

	Destroy();
}

