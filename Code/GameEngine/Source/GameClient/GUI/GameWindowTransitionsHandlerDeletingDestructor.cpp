// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: GameWindowTransitionsHandler scalar-deleting destructor at
// retail 0x0048B8A0 (30 bytes).  The primary vtable at 0x010F9610 is installed
// by the matched constructor at 0x0048BF40, and slot zero routes through the
// complete destructor at 0x0048B410.  The GameWindowManager-owned singleton
// and exact complete-destructor identity establish this deleting wrapper.

class GameWindowTransitionsHandler
{
public:
	virtual ~GameWindowTransitionsHandler();
};

void Force_GameWindowTransitionsHandler_Deleting_Destructor()
{
	GameWindowTransitionsHandler value;
}
