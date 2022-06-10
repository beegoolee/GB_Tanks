
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankBase.h"

#include "MyTankController.generated.h"

class ATankPawn;

UCLASS()
class T_A_N_K_S_API AMyTankController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyTankController();
	virtual void SetupInputComponent() override;

	void SelectShot_1();
	void SelectShot_2();
	void SelectShot_3();

protected:
	UPROPERTY()
		ATankBase* TankPawn;

	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void Rotate(float AxisValue);

	void RotateCameraX(float AxisValue);

	void RotateCameraY(float AxisValue);

	void RotateTurret(float AxisValue);

	void Fire();
	void AltFire(float axis);
};
