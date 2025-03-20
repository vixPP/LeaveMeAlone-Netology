
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponClipEmpty);
USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ALMABaseWeapon();
	FAmmoWeapon CurrentAmmoWeapon;

protected:

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{ 30, 0, true };

	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.1f;


public:	
	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnWeaponClipEmpty OnWeaponClipEmpty;
	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

	virtual void Tick(float DeltaTime) override;
	void StartFire();
	void StopFire();
	void  Fire();
	void Shoot();
	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	bool IsClipFull() const;
	void ChangeClip();
};
