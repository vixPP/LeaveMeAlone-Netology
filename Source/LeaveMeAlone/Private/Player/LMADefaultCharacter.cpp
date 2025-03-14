#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Components/LMAHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"




ALMADefaultCharacter::ALMADefaultCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArmComponent->SetupAttachment(GetMesh(), "CameraSocket");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f)); /*-структура FRotator хранит аргументы 
																				в следующей последовательности : Pitch, Yaw, Roll.Так как нам необходимо определить значения по оси Y, мы
																				устанавливаем Pitch аргумент.*/
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	//Настройка камеры
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;/* – данное условие запрещаем камере вращаться относительно SpringArmComponent.*/

	//Здоровье
	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent"); 

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}


void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize,
			FVector(0));
	}

	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
}

void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		Super::Tick(DeltaTime);
		if (!(HealthComponent->IsDead()))
		{
			RotationPlayerOnCursor();
		}
	}

	UpdateStamina();
}

void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);

	PlayerInputComponent->BindAxis("CameraZoom", this, &ALMADefaultCharacter::CameraZoom);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::CameraZoom(float Value) 
{
	if (Value == 0) 
		return;

	float NewArmLength = SpringArmComponent->TargetArmLength + Value * ZoomStep;

	SpringArmComponent->TargetArmLength = FMath::Clamp(NewArmLength, MinZoomLenght, MaxZoomLenght);
}

void ALMADefaultCharacter::OnDeath()
{

	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(10.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;

		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
		ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));

			if (CurrentCursor)
			{

				CurrentCursor->SetWorldLocation(ResultHit.Location);

			}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"),
	NewHealth));
}

//SPRINT / STAMINA//

void ALMADefaultCharacter::StartSprint()
{

	GetCharacterMovement()->MaxWalkSpeed = 650.0f;
	isSprinting = true;
	UpdateStamina();
}

void ALMADefaultCharacter::StopSprint()
{
	
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	isSprinting = false;
	//UpdateStamina();
}

void ALMADefaultCharacter::DecreseaseStamina()
{
	CurrentStamina = Stamina - MinusStamina;
	Stamina = CurrentStamina;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Stamina Decreased %f"), Stamina));
}

void ALMADefaultCharacter::IncreaseStamina()
{
	if(isSprinting == false)
	{
		CurrentStamina = Stamina + PlusStamina;
		Stamina = CurrentStamina;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Stamina Increased %f"), Stamina));
	}

};

void ALMADefaultCharacter::UpdateStamina()
{
	if (isSprinting == true && Stamina != 0.f)
	{
		DecreseaseStamina();
	}
	else
	{	
		if(isSprinting == false && Stamina != 100.f)
		
		IncreaseStamina();
	}

	if (FMath::IsNearlyZero(Stamina))
	{
		StopSprint();
	}
}





