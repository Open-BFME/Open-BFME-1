// cl: /DNDEBUG /MD /EHsc

#include "../../Include/Common/Enums/GSOverlayType.h"




void GameSpyCloseOverlayShim(GSOverlayType);

void GameSpyCloseOverlay(GSOverlayType type)
{
	GameSpyCloseOverlayShim(type);
}
