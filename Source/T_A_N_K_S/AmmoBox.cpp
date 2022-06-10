#include "AmmoBox.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
}

void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();

	BoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
}

void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("AMMO BOX %s collided with %s. "), *GetName(), *OtherActor->GetName());

	AMyPawnBase* TankOverlapped = Cast<AMyPawnBase>(OtherActor);

	if (TankOverlapped) {
		TankOverlapped->SetAmmoPoints(PrimaryAmmo, AltAmmo); 
		Destroy();
	}
}
