#include "Turret.h"

ATurret::ATurret()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret turret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(TurretMesh);

	UStaticMesh * turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp) {
		TurretMesh->SetStaticMesh(turretMeshTemp);
	}

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp) {
		BodyMesh->SetStaticMesh(bodyMeshTemp);
	}	

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret::DamageTaked);

	OnDestroyVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("On destroy particle"));
	OnDestroyVFX->SetupAttachment(RootComponent);

	OnDestroySFX = CreateDefaultSubobject<UAudioComponent>(TEXT("On destroy sound"));
	OnDestroySFX->SetupAttachment(RootComponent);

	OnDamageVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("On getting damage particle"));
	OnDamageVFX->SetupAttachment(RootComponent);

	OnDamageSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("On getting damage particle sound"));
	OnDamageSFX->SetupAttachment(RootComponent);
}

void ATurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	OnDamageVFX->ActivateSystem();
	OnDamageSFX->Play();
}

void ATurret::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s is dead"), *GetName());

	OnDestroyVFX->ActivateSystem();
	OnDestroySFX->Play();

	Destroy();
}

void ATurret::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
}

void ATurret::Destroyed()
{
	if (Cannon) {
		Cannon->Destroy();
	}
}

void ATurret::Targeting()
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
	}
	if (CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}
}

void ATurret::RotateToPlayer()
{
	FVector targetLoc = PlayerPawn->GetActorLocation();

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetLoc);
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;

	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	
	FVector targetLoc = PlayerPawn->GetActorLocation();

	FHitResult TargetHitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("GameObjectTrace")), true, this);

	GetWorld()->LineTraceSingleByChannel(TargetHitResult, GetEyesPosition(), targetLoc, ECollisionChannel::ECC_Visibility, traceParams);

	ATankBase* targetPawn = Cast<ATankBase>(TargetHitResult.Actor.Get());

	if (targetPawn == PlayerPawn) {
		return aimAngle <= Accurency;
	}
	else {
		return false;
	};
}

void ATurret::Fire()
{
	if (Cannon) {
		Cannon->Fire();
	}	
}

FVector ATurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}
