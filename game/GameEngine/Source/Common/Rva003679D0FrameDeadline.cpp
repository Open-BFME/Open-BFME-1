// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The body reads the simulation frame from TheGameLogic+0x3C and compares it
// unsigned against an indexed dword at this+0x30.  The class and method names
// remain descriptive because the surrounding binary does not prove a stronger
// identity.

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the frame field at +0x3C
// through its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class GameLogicFrameSlice
{
public:
	char         m_lead[ 0x3C ];
	unsigned int m_frame;
};

class Rva003679D0FrameDeadline
{
public:
	unsigned char isPending( int index ) const;

private:
	char         m_lead[ 0x30 ];
	unsigned int m_deadlines[ 1 ];
};

unsigned char Rva003679D0FrameDeadline::isPending( int index ) const
{
	return ((GameLogicFrameSlice *)TheGameLogic)->m_frame < m_deadlines[ index ];
}
