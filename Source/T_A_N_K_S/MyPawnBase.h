
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CanonShot.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "DamageTaker.h"

#include "MyPawnBase.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UTextRenderComponent;

UCLASS()
class T_A_N_K_S_API AMyPawnBase : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	AMyPawnBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* PrimaryShootVFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* PrimaryShootSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* AltShootVFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AltShootSFX;
		
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* BodySMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* WreckedBodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Movement")
		float fMaxMovementSpeed_forward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Movement")
		float fMaxMovementSpeed_backward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Movement")
		float fMaxRotationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Shot Types")
		TSubclassOf<ACanonShot> ShotType_1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Shot Types")
		TSubclassOf<ACanonShot> ShotType_2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Shot Types")
		TSubclassOf<ACanonShot> ShotType_3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | ShotClass")
		TSubclassOf<ACanonShot> CanonShotClass = ShotType_1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | ShotClass")
		TSubclassOf<ACanonShot> AltShotClass;

	bool bPrimaryCanShoot = true;
	bool bAltCanShoot = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		bool bHaveAltFireMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		float fPrimaryFireReloadTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		float fAltFireReloadTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		float fTurretRotSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		int iMaxPrimaryAmmo = 15;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Firepower")
		int iMaxAltAmmo = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Characteristics | Health")
		float fMaxHP = 1000;

	float fCurrentHP = fMaxHP;

	int iPrimaryAmmoCurrent = iMaxPrimaryAmmo;
	int iAltAmmoCurrent = iMaxAltAmmo;

	float fCurrentMoveAxis;
	float fCurrentRotationAxis;

	float fTurretRotationZ;

	FTimerHandle _primaryReloadTimerHandle;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PrimaryFire();

	void ReloadPrimary();
	void ReloadAlt();

	void AltFire(float axis);

	void SetForwardAxis(float fAxis);
	void MoveForward(float DeltaTime);

	void SetRotationAxis(float rAxis);
	void Rotate(float DeltaTime);

	void TakeHit(float DamageValue);
	void Death();

	void AddTurretRotation(float rAxis);
	
	UFUNCTION(BlueprintCallable, Category = "Turret Funcs")
		float GetTurretRotationZ();

	void SelectShot_1();
	void SelectShot_2();
	void SelectShot_3();

	void LoadNewShotType();

	void SetAmmoPoints(int iPrimaryAmmoAdded, int iAltAmmoAdded);
};

