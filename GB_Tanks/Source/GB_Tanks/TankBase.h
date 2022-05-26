// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBase.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankBaseController;
class ACannon;


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

	float _targetForwardAxisValue;
	float _targetRotationAxisValue;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
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


	// tank movement funcs
	UFUNCTION()
		void GetForwardAxis(float AxisValue);
	UFUNCTION()
		void GetRotationAxis(float AxisValue);

	// tank combat funcs
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void FireSpecial();
	UFUNCTION()
		void SwitchCannon();
	UFUNCTION()
		ACannon* GetActiveCannon();

	// event tick funcs
	UFUNCTION()
		void TankMovement(float DeltaTime);
	UFUNCTION()
		void TurretRotation();
};
