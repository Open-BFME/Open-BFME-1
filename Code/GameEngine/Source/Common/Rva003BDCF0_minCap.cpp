// cl: /DNDEBUG /MD /EHsc
//
// Rva003BDCF0::get, retail 0x003BDCF0, 81 bytes.
//
// Niladic getter on d_003b8450: if m_at28 is nil return 0; else return the
// signed min of (owner[+0x34] + this[+0xD0]) and
// (-100 - (int)(TheWritableGlobalData[+0xEC4] * -100.0f)) via lea-select.
// Sum is written through an int* so MSVC keeps ecx as this for the +0xD0 add
// and stores the total before the fmul/ftol2 limit path.

class Glo012ED5C8Type
{
public:
	char m_pad00[ 0xEC4 ];
	float m_atEC4;
};

extern Glo012ED5C8Type *TheWritableGlobalData;

class Gen003BDCF0Owner
{
public:
	char m_pad00[ 0x34 ];
	int m_at34;
};

class Rva003BDCF0
{
public:
	int get();

private:
	char m_pad00[ 0x28 ];
	Gen003BDCF0Owner *m_at28;
	char m_pad2C[ 0xD0 - 0x2C ];
	int m_atD0;
};

// ?get@Rva003BDCF0@@QAEHXZ
int Rva003BDCF0::get()
{
	int sum;
	int lim;
	Gen003BDCF0Owner *owner = m_at28;
	if( owner )
	{
		int *ps = &sum;
		*ps = owner->m_at34;
		*ps += m_atD0;
		lim = -100 - (int)( TheWritableGlobalData->m_atEC4 * -100.0f );
		return *( ( sum < lim ) ? &sum : &lim );
	}
	return 0;
}
