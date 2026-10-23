// ?dispatchWhenReady@Rva007E32A0State@@QAE_NHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// The callee retail entered here (through the incremental-link thunk at
// 0x0003F80F) is BfmeB996::readPacket at 0x007E2F50. It is entered with this
// in ECX and five stack arguments and answers in AL.
class BfmeB996
{
public:
	char readPacket( int **output, int *first, int *second, char *stop, char flag );
};

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
		char result = reinterpret_cast<BfmeB996 *>( this )->readPacket(
			reinterpret_cast<int **>( first ), reinterpret_cast<int *>( second ),
			reinterpret_cast<int *>( third ), reinterpret_cast<char *>( &third ),
			static_cast<char>( true ) );
		return *reinterpret_cast<bool *>( &result );
	}
	return false;
}
