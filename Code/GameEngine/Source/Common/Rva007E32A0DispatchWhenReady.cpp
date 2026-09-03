// ?dispatchWhenReady@Rva007E32A0State@@QAE_NHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva007E32A0State
{
public:
	bool dispatchWhenReady( int first, int second, int third );
	bool forward( int first, int second, int third, int *thirdOut,
		int enabled );

private:
	char m_unknown[ 8 ];
	int m_state;
};

bool Rva007E32A0State::dispatchWhenReady( int first, int second, int third )
{
	if ( m_state == 6 ) {
		return forward( first, second, third, &third, true );
	}
	return false;
}
