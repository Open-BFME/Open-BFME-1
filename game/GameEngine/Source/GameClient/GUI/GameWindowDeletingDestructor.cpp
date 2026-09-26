// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME: GameWindow protected scalar-deleting destructor at retail RVA
// 0x00479DD0 (30 bytes).  Its unique destructor ILT 0x0002C98F enters the
// matched complete destructor at 0x00479CD0; the exact ctor at 0x004792F0
// and the recovered BFME window layout establish the class identity.

class GameWindow
{
protected:
	virtual ~GameWindow();

	friend void forceGameWindowDeletingDestructor();
};

void forceGameWindowDeletingDestructor()
{
	GameWindow value;
}
