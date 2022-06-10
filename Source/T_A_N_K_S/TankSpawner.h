#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TankBase.h"
#include "DamageTaker.h"


#include "TankSpawner.generated.h"

UCLASS()
class T_A_N_K_S_API ATankSpawner : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	ATankSpawner();

protected:
	virtual void BeginPlay() override;

	void TryToRespawnTank();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* SpawnVFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* SpawnSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DeathVFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* DeathSFX;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* WreckedBodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* GatesMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn | tanks class")
		TSubclassOf<ATankBase> SpawnTankClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn | Max tanks count")
		int iMaxTanksCount = 5;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Spawn | Spawned tanks count")
		int iSpawnedTanksCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn | Spawn interval")
		float fSpawnInterval = 3.0f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Health")
		float fMaxHP = 1000;
	float fCurrentHP = fMaxHP;

	bool isDead = false;

public:	
	virtual void Tick(float DeltaTime) override;

	void TakeHit(float DamageValue);
	void Death();
};
