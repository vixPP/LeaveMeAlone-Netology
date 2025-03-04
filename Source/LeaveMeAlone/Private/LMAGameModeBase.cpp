
#include "LMAGameModeBase.h"
#include "Player/LMADefaultCharacter.h"
#include "Player/LMAPlayerController.h"

ALMAGameModeBase::ALMAGameModeBase()
{
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMAPlayerController::StaticClass();

}

