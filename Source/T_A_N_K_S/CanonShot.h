#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "DamageTaker.h"

#include "CanonShot.generated.h"

class UStaticMeshComponent;

UCLASS()
class T_A_N_K_S_API ACanonShot : public AActor
{
	GENERATED_BODY()
	
public:	
	ACanonShot();

	void Start();
	
protected:
	virtual void BeginPlay() override;

	void SelfDestroyByTimer();
	void Move();
	float const LIFE_TIME_SEC = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* ShotMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Movement")
		float fShotSpeed = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Movement")
		float fShotMoveRate = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Combat")
		float fDamage = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Combat")
		float ArmorPiercing = 0.0f;

	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
			FHitResult& SweepResult);
};
