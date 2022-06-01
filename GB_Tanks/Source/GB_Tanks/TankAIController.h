#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankBase.h"

#include "TankAIController.generated.h"

class ATankBase;

UCLASS()
class GB_TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		ATankBase* TankPawn;
	UPROPERTY()
		APawn* PlayerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;
	int32 CurrentPatrolPointIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
		float MovementAccurency;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	float GetRotationgValue();
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool IsPlayerSeen();
	bool CanFire();
	void Fire();

};
