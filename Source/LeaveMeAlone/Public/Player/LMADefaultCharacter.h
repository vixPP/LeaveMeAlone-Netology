#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class ULMAWeaponComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{	

	GENERATED_BODY()
		
public:

	ALMADefaultCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);


	//Camera zoom settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
		float MinZoomLenght = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
		float MaxZoomLenght = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
		float ZoomStep = 10.f;

	//HP
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	//dead
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathMontage;

	//sprint

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint")
	bool isSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeed = 650.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float Stamina = 100.0f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float MinusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float PlusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float MaxStamina = 100.0f;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;


	virtual void BeginPlay() override;
	
public:	
	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnDeath();
private:

	float YRotation = -75.0f;
	float FOV = 55.0f;
	float ArmLength = 1700.0f;
	float defaultWalkSpeed = 300.0f;
	float MinStaminaToSprint = 10.0f;
	
	void MoveForward(float Value); // будет отвечать за движение персонажа по оси X.
	void MoveRight(float Value);   // будет отвечать за движение персонажа по оси Y.
	void CameraZoom(float Value); //Приближение камеры

	void RotationPlayerOnCursor();
	
	void OnHealthChanged(float NewHealth);

	//Srint//
	void StartSprint();
	void StopSprint();
	void DecreseaseStamina();
	void IncreaseStamina();
	void UpdateStamina();
	
};
