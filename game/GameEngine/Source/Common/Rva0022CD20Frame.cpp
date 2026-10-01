// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the frame field at +0x3C
// through its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class GameLogicFrameSlice
{
public:
	unsigned int m_pad[0x3C / sizeof(unsigned int)];
	unsigned int m_frame;
};

class Rva0022CD20Obj
{
public:
	bool pending() const;

private:
	char m_pad[0xAC];
	unsigned int m_frame;
};

bool Rva0022CD20Obj::pending() const
{
	return ((GameLogicFrameSlice *)TheGameLogic)->m_frame < m_frame;
}
