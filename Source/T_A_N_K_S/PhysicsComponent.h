#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PhysicsComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class T_A_N_K_S_API UPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gravity params")
		float Gravity = -9.8f;
public:
	TArray<FVector> GenerateTrajectory(FVector StartPos, FVector Velocity, float
		MaxTime, float TimeStep, float MinZValue = 0);
};