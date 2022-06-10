#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MyPawnBase.h"

#include "AmmoBox.generated.h"


class UStaticMeshComponent;

UCLASS()
class T_A_N_K_S_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmmoBox();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Points | Primary")
		int PrimaryAmmo = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Points | Alt")
		int AltAmmo = 200;

	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
			FHitResult& SweepResult);
public:	
	virtual void Tick(float DeltaTime) override;

};
