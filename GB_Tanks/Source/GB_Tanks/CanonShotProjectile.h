
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "CanonShotProjectile.generated.h"

UCLASS()
class GB_TANKS_API ACanonShotProjectile : public AActor
{
	GENERATED_BODY()
public:	
	ACanonShotProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
};
