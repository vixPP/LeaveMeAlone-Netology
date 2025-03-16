
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ALMABaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
	Category="Weapon")
	USkeletalMeshComponent* WeaponComponent;

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
