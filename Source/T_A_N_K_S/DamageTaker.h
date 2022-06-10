#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};


class T_A_N_K_S_API IDamageTaker
{
	GENERATED_BODY()

public:
	virtual void TakeHit(float DamageValue) = 0;
};
