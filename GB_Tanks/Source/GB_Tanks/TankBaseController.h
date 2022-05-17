// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankBase.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankBaseController.generated.h"

class ATankBase;

/**
 * 
 */
UCLASS()
class GB_TANKS_API ATankBaseController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		ATankBase* TankBase;

	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void Rotate(float AxisValue);
	void RotateTurret(float AxisValue);
	void CanonFire();

public:
	ATankBaseController();
	virtual void SetupInputComponent() override;
};
