// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletsBox.h"
#include "TankBase.h"

ABulletsBox::ABulletsBox() {
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABulletsBox::OnMeshOverlapBegin);
	Mesh->SetCollisionProfileName(FName("OverlapAll"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

void ABulletsBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankBase* playerPawn = Cast<ATankBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (OtherActor == playerPawn)
	{
		ACannon* Cannon = playerPawn->GetActiveCannon();
		Cannon->AddAmmoPoints(AmmoPoints);
		Destroy();
	}
}