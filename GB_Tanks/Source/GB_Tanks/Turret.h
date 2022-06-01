#pragma once

#include "IScorable.h"
#include "GameFramework/Pawn.h"
#include "HealthComponent.h"
#include "DamageTaker.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Turret.generated.h"

class ACannon;
class UHealthComponent;
class UStaticMeshComponent;

UCLASS()
class GB_TANKS_API ATurret: public AActor, public IIScorable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
		ACannon* Cannon;

	/* Общие у танка и турели компоненты */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* OnDestroyVFX;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* OnDestroySFX;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* OnDamageVFX;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* OnDamageSFX;

	FVector GetEyesPosition();
	/* Общие у танка и турели компоненты */

	UPROPERTY()
		APawn* PlayerPawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

	const FString BodyMeshPath =
		"StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath =
		"StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

public:
	ATurret();

	/* Общие у танка и турели методы */
	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData);
	UFUNCTION()
		virtual void Die();
	UFUNCTION()
		virtual void DamageTaked(float DamageValue);
	/* Общие у танка и турели методы */

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();

	/* Общие у танка и турели методы */
	virtual void Fire();
	/* Общие у танка и турели методы */
};
