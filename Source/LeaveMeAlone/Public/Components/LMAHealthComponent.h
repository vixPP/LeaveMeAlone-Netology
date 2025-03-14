#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

class ULMAHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAHealthComponent();
	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

	FOnDeath OnDeath;
	UFUNCTION(BlueprintCallable)
	bool IsDead() const;
	FOnHealthChanged OnHealthChanged;
	bool AddHealth(float NewHealth);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	
	float MaxHealth = 100.0f;

	bool IsHealthFull() const;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser);

};
