// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The body reads the simulation frame from TheGameLogic+0x3C and compares it
// unsigned against an indexed dword at this+0x30.  The class and method names
// remain descriptive because the surrounding binary does not prove a stronger
// identity.

class GameLogicFrameSlice
{
public:
	char         m_lead[ 0x3C ];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

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
	return TheGameLogic->m_frame < m_deadlines[ index ];
}
