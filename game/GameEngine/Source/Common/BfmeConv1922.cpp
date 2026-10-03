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

// The ILT thunk at 0x00040F3E is the retail body at this call site
// (targets/game/reverse/functions.csv ?j_00040f3e@@YAXXZ, 5 bytes, tail jmp
// to 0x0045D710).  Retail calls it cdecl with no arguments and takes the
// engine pointer in EAX, so it is spelled as the defined thunk symbol.
extern void j_00040f3e();

extern "C" void __cdecl bfmeExitBZ(void);

void __cdecl bfmeBootBZ(void *first, void *second)
{
	TheGameEngine = ((GameEngine *(__cdecl *)())j_00040f3e)();
	TheGameEngine->bfmeInitBZ(first, second);
	TheGameEngine->bfmeRunBZ();
	bfmeExitBZ();
}
