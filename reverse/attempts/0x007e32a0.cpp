// ?dispatchWhenReady@Rva007E32A0State@@QAE_NHHH@Z
// partial score=0.62 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// Address-derived recovery: the surrounding state owner has not yet been named.
// State 6 forwards the three values and an output flag to the shared dispatcher.

extern bool __stdcall Rva007E32A0Dispatch( int first, int second, int third,
	int *thirdOut, int enabled );

class Rva007E32A0State
{
public:
	bool dispatchWhenReady( int first, int second, int third );

private:
	char m_unknown[ 8 ];
	int m_state;
};

bool Rva007E32A0State::dispatchWhenReady( int first, int second, int third )
{
	if ( m_state == 6 ) {
		return Rva007E32A0Dispatch( *(volatile int *)&first,
			*(volatile int *)&second, third, &third, true );
	}
	return false;
}
