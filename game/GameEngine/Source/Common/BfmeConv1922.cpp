class GameEngine
{
public:
	virtual void bfmeSlot00BZ();
	virtual void bfmeSlot01BZ();
	virtual void bfmeSlot02BZ();
	virtual void bfmeSlot03BZ();
	virtual void bfmeSlot04BZ();
	virtual void bfmeSlot05BZ();
	virtual void bfmeSlot06BZ();
	virtual void bfmeSlot07BZ();
	virtual void bfmeSlot08BZ();
	virtual void bfmeInitBZ(void *first, void *second);
	virtual void bfmeRunBZ();
};

extern GameEngine *TheGameEngine;

extern "C" GameEngine *__cdecl bfmeMakeBZ(void);
extern "C" void __cdecl bfmeExitBZ(void);

void __cdecl bfmeBootBZ(void *first, void *second)
{
	TheGameEngine = bfmeMakeBZ();
	TheGameEngine->bfmeInitBZ(first, second);
	TheGameEngine->bfmeRunBZ();
	bfmeExitBZ();
}
