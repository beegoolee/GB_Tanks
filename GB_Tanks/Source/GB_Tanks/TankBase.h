// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "HealthComponent.h"
#include "DamageTaker.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "TankBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ATankBaseController;
class ACannon;
class UHealthComponent;
class UStaticMeshComponent;

UCLASS()
class GB_TANKS_API ATankBase : public APawn
{
	GENERATED_BODY()

protected:
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
	/* Общие у танка и турели компоненты */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Tank base")
		float fMoveSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Tank base")
		float fBodyRotationSpeed = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat | Tank turret rotation speed")
		float fTurretRotationSpeed = 0.2f;

	float _targetForwardAxisValue;
	float _targetRotationAxisValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClassMain;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret| Alternative Cannon")
		TSubclassOf<ACannon> CannonClassAlt;

	UPROPERTY()
		ACannon* CannonMain;
	UPROPERTY()
		ACannon* CannonAlt;
	UPROPERTY()
		ACannon* ActiveCannon = CannonMain;

	bool isMainCannonSelected = true;
	int iScorePoints = 0;

public:	

	ATankBase();

	void SetupCannon(TSubclassOf<ACannon> newCannonClass);

	void OnCannonPickup(TSubclassOf<ACannon> newCannonClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Tank base")
		float rotateInterpKey = 0.02f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Tank base")
		float forwardMoveInterpKey = 0.02f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Combat | Turret target location")
		FVector TurretFacetoLocation;
	UPROPERTY()
		ATankBaseController* TankController;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Общие у танка и турели методы */
	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData);
	UFUNCTION()
		virtual void Die();
	UFUNCTION()
		virtual void DamageTaked(float DamageValue);
	UFUNCTION()
		virtual void Fire();
	/* Общие у танка и турели методы */


	// tank movement funcs
	UFUNCTION()
		void GetForwardAxis(float AxisValue);
	UFUNCTION()
		void GetRotationAxis(float AxisValue);

	// tank combat funcs
	UFUNCTION()
		void FireSpecial();
	UFUNCTION()
		void SwitchCannon();
	UFUNCTION()
		ACannon* GetActiveCannon();

	
	UFUNCTION()
		void AddScorePoints(int AddedPoints);

	// event tick funcs
	UFUNCTION()
		void TankMovement(float DeltaTime);
	UFUNCTION()
		void TurretRotation();
};
