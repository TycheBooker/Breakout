#include "BaseScreen.h"
#include "AssetManager.h"

BaseScreen::BaseScreen()
{
}

BaseScreen::BaseScreen(StateManager * stateManager) :
	stateManager(stateManager)
{
}

BaseScreen::~BaseScreen()
{
}
