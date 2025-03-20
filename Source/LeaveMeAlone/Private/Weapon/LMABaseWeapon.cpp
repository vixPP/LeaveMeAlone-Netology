DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);
#include "Weapon/LMABaseWeapon.h"
#include "TimerManager.h"

ALMABaseWeapon::ALMABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);
}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ALMABaseWeapon::StartFire() {
	if (!IsCurrentClipEmpty()) {
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ALMABaseWeapon::Fire, FireRate, true);
		Fire();
	}
}

void ALMABaseWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ALMABaseWeapon::Fire() {
	if (!IsCurrentClipEmpty())
	{
		Shoot();
	}
	else {
		StopFire();
	}
}
void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false,1.0f);
	}

	DecrementBullets();
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}
bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

void ALMABaseWeapon::DecrementBullets()
{
	if(CurrentAmmoWeapon.Bullets > 0)
	{
	CurrentAmmoWeapon.Bullets--;
	}

	if (IsCurrentClipEmpty()) 
	{
		OnWeaponClipEmpty.Broadcast();
	}
}

bool ALMABaseWeapon::IsClipFull() const 
{
	return CurrentAmmoWeapon.Bullets == AmmoWeapon.Bullets;
}