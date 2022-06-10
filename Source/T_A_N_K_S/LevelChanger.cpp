#include "LevelChanger.h"

ALevelChanger::ALevelChanger()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = BodyMesh;

	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collider"));

	OverlapCollision->OnComponentBeginOverlap.AddDynamic(this, &ALevelChanger::OnMeshOverlapBegin);
}

void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn == OtherActor) {
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}
