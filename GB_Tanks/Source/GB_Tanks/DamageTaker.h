
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStructs.h"
#include "DamageTaker.generated.h"

UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GB_TANKS_API IDamageTaker
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(FDamageData DamageData) = 0;
};
