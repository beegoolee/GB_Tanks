// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GB_TANKS_API ATankBase : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat | Shooting range")
		float fShootingRange = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
		UParticleSystem* canonShotFX;
	
	float _targetForwardAxisValue;
	float _targetRotationAxisValue;
	float _targetTurretRotationAxisValue;

public:	

	ATankBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// tank movement funcs
	UFUNCTION()
		void GetForwardAxis(float AxisValue);
	UFUNCTION()
		void GetRotationAxis(float AxisValue);
	

	// tank combat funcs
	UFUNCTION()
		void GetTurretRotationAxis(float AxisValue);
	UFUNCTION()
		void CanonFire();


	// event tick funcs
	UFUNCTION()
		void TankMovement();
	UFUNCTION()
		void TurretRotation();
};
