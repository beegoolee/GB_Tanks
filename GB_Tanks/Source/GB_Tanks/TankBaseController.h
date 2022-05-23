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

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void Rotate(float AxisValue);
	
	float forwardCurrentAxis = 0;
	float rotateCurrentAxis = 0;

	UFUNCTION()
		void SetMousePosition();

	void Fire();

	void FireSpecial();

public:
	ATankBaseController();

	virtual void SetupInputComponent() override;

	UPROPERTY()
		FVector MousePosition;
};
