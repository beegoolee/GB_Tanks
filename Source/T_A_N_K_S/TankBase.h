#pragma once

#include "MyPawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"

#include "TankBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class T_A_N_K_S_API ATankBase : public AMyPawnBase
{
	GENERATED_BODY()

public:
	ATankBase();

	void AddCameraRotY(float rAxis);
	void AddCameraRotX(float rAxis);
	void SwitchCamera();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;
	
	/*
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* AimCamera;
		*/
};
