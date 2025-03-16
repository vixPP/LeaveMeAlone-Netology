


#include "Weapon/LMABaseWeapon.h"


ALMABaseWeapon::ALMABaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
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

