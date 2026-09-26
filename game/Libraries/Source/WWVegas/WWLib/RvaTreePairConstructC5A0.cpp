// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Structural recovery for the retail pair construction body at 0x0094C5A0.

struct Rva0094C5A0Thing
{
	int head;
	unsigned short refs;
};

class Rva0094C5A0Handle
{
	public:
	Rva0094C5A0Handle(void) : value( 0 ) {}
	Rva0094C5A0Handle(const Rva0094C5A0Handle &other)
	{
		Rva0094C5A0Thing *thing = other.value;
		value = thing;
		if ( thing )
			++thing->refs;
	}
	~Rva0094C5A0Handle(void)
	{
		if ( value )
			--value->refs;
	}
	Rva0094C5A0Thing *value;
};

struct Rva0094C5A0Value
{
	unsigned value[ 4 ];
};

struct Rva0094C5A0Pair
{
	Rva0094C5A0Pair(const Rva0094C5A0Handle &first,
		const Rva0094C5A0Value &second)
		: m_first(first), m_second(second)
	{
	}
	Rva0094C5A0Handle m_first;
	Rva0094C5A0Value m_second;
};

Rva0094C5A0Pair __cdecl rva0094C5A0MakePair(
	const Rva0094C5A0Handle *first, const Rva0094C5A0Value *second)
{
	return Rva0094C5A0Pair(*first, *second);
}
