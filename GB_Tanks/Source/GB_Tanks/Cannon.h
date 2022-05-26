#pragma once
#include "CoreMinimal.h"
#include "GameStructs.h"
#include "CanonShotProjectile.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class GB_TANKS_API ACannon : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params | Cannon shot class")
		TSubclassOf<ACanonShotProjectile> CanonShotClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params | Special Fire - burst fire rate")
		float Special_BurstFireDelay = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params | Special Fire - burst size")
		int Special_BurstSize = 3;

	FTimerHandle ReloadTimerHandle;
	FTimerHandle BurstHandle;

	bool ReadyToFire = false;
	virtual void BeginPlay() override;
	void Reload();

	int MaxAmmoCount = 30;
	int AmmoCount = MaxAmmoCount;
	int Special_BurstShotCount = 0;

public:
	ACannon();
	void Fire();
	void FireSpecial();
	void Burst();
	bool IsReadyToFire();
	void AddAmmoPoints(int addedPoints);
};
