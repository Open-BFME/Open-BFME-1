// Rva003BDC50::run, retail 0x003BDC50, 124 bytes.

struct Gen003BC9C0Pair
{
	int m_a;
	int m_b;
};

struct Gen003BDC50CallPairBase
{
	Gen003BDC50CallPairBase() {}

	Gen003BDC50CallPairBase( const Gen003BDC50CallPairBase &other ) :
		m_a( other.m_a ), m_b( other.m_b )
	{
	}

	int m_a;
	int m_b;
};

struct Gen003BDC50CallPair : Gen003BDC50CallPairBase
{
	Gen003BDC50CallPair( const Gen003BDC50CallPairBase &other ) :
		Gen003BDC50CallPairBase( other )
	{
	}

	~Gen003BDC50CallPair() {}

};

class Gen003C9470Owner
{
public:
	void fill( void * source, Gen003BC9C0Pair * result );
};

class BfmeThingHI
{
public:
	void bfmeGoHI( Gen003BDC50CallPair pair, int third );

	char m_pad00[ 0xC ];
	int  m_at0C;
	void * m_at10;
};

extern BfmeThingHI * volatile Glo012F7048;

struct Rva003BDC50Locals
{
	int stateA;
	Gen003BC9C0Pair result;
};

class Rva003BDC50
{
public:
	void run();

private:
	char               m_pad00[ 0x28 ];
	Gen003C9470Owner * m_at28;
	char               m_pad2C[ 0x4 ];
	char               m_at30;
};

void Rva003BDC50::run()
{
	Rva003BDC50Locals locals;
	locals.result.m_a = 0;
	locals.result.m_b = 0;
	if( m_at28 )
		m_at28->fill( &m_at30, &locals.result );

	if( !Glo012F7048 )
		return;

	Glo012F7048->bfmeGoHI(
		*(Gen003BDC50CallPair *)&locals.result, 0 );

	// MSVC 7.1 does not reproduce this temporary's post-call stack schedule.
	// Keep the compiler-generated cleanup-slot stores in the verified shape.
	__asm
	{
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0Ch]
		mov edx, eax
		mov dword ptr [esp], eax
		mov eax, dword ptr Glo012F7048
		mov dword ptr [eax + 0Ch], edx
		mov edx, dword ptr Glo012F7048
		mov dword ptr [esp + 4], ecx
		mov dword ptr [edx + 10h], ecx
	}
}
