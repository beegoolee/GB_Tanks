// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBase.h"
#include "BulletsBox.generated.h"

class UStaticMeshComponent;

UCLASS()
class GB_TANKS_API ABulletsBox : public AActor
{
	GENERATED_BODY()
public:
	ABulletsBox();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo points")
		int AmmoPoints = 0;
	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

