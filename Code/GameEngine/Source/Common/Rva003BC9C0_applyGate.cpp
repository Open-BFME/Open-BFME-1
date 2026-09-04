// cl: /DNDEBUG /MD /EHsc
//
// Rva003BC9C0::run, retail 0x003BC9C0, 70 bytes.
//
// thiscall with two pointer args on d_003b8450: null-guards both, asks
// m_at28 to fill an 8-byte stack local from (src+4), then forwards that
// local into Gen003C0110Result::apply with TheEmptyString twice plus (1,0).

struct Gen003BC9C0Pair
{
	int m_a;
	int m_b;
};

class Gen003C9470Owner
{
public:
	void fill( void * srcPlus4, Gen003BC9C0Pair * out );
};

class Gen003C0110Result
{
public:
	void apply( int a, int b, int c, int d, int e );
};

// Retail AsciiString::TheEmptyString / shared empty at 0x01336E50.
extern int TheEmptyString;

class Rva003BC9C0
{
public:
	void run( Gen003C0110Result * target, void * src );

private:
	char m_pad00[ 0x28 ];
	Gen003C9470Owner * m_at28;
};

// ?run@Rva003BC9C0@@QAEXPAVGen003C0110Result@@PAX@Z
void Rva003BC9C0::run( Gen003C0110Result * target, void * src )
{
	if( target )
	{
		if( src )
		{
			Gen003BC9C0Pair local;
			m_at28->fill( (char *)src + 4, &local );
			target->apply( (int)(void *)&local, (int)(void *)&TheEmptyString,
				(int)(void *)&TheEmptyString, 1, 0 );
		}
	}
}
