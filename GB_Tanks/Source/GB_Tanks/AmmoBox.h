#pragma once

#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankBase.h"
#include "AmmoBox.generated.h"

class UStaticMeshComponent;

UCLASS()
class GB_TANKS_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmmoBox();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon> CannonClass;

	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
