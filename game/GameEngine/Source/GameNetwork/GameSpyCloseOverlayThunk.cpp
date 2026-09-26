// cl: /DNDEBUG /MD /EHsc

enum GSOverlayType
{
	GSOverlayType_Thunk
};

void GameSpyCloseOverlayShim(GSOverlayType);

void GameSpyCloseOverlay(GSOverlayType type)
{
	GameSpyCloseOverlayShim(type);
}
