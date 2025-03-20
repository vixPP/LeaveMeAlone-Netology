#pragma once

#include "Weapon/LMABaseWeapon.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULMAWeaponComponent();

	void Reload();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UAnimMontage* ReloadMontage;

	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	UFUNCTION()
	void OnClipEmpty();

	virtual void BeginPlay() override;




public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const;

	void StartFire();
	void StopFire();

	void ReloadWeapon();
	bool CanReload() const;

private:


	bool AnimReloading = false;
	
	void SpawnWeapon();
	void InitAnimNotify();

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	

};
