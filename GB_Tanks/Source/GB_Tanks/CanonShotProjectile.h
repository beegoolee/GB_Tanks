
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "IScorable.h"

#include "CanonShotProjectile.generated.h"

UCLASS()
class GB_TANKS_API ACanonShotProjectile : public AActor
{
	GENERATED_BODY()


	DECLARE_EVENT(ACanonShotProjectile, FOnKillEnemy)

public:	
	ACanonShotProjectile();

	FOnKillEnemy OnKillEnemy;

	UFUNCTION()
		void AddScoreOnKill();
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float Damage = 1.0f;

	FTimerHandle MovementTimerHandle;

	void Move();
	virtual void BeginPlay() override;
	
	
	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
		FHitResult& SweepResult);
};
