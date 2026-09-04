// ?BfmeLess00574AA0@S4SortElem8@@QBE_NABU1@@Z
// partial score=0.94 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	int bfmeCompare(AsciiString const &other) const;
};

class LivingWorldArmy
{
public:
	AsciiString getName() const;

	unsigned char Prefix[0x44];
	int SortKey;
};

class LivingWorldArmyState
{
public:
	unsigned char Prefix[0xD0];
	unsigned Flags;
};

struct S4SortElem8
{
	LivingWorldArmy *Army;
	LivingWorldArmyState *State;

	bool BfmeLess00574AA0(S4SortElem8 const &other) const;
};

bool S4SortElem8::BfmeLess00574AA0(S4SortElem8 const &other) const
{
	unsigned leftFlags = State->Flags;
	const S4SortElem8 &right = other;
	unsigned rightFlags = right.State->Flags;
	unsigned leftSpecial = leftFlags >> 25;
	unsigned rightSpecial = rightFlags >> 25;
	if (leftSpecial != rightSpecial)
		return leftSpecial != 0;
	if (Army->SortKey != other.Army->SortKey)
		return Army->SortKey > other.Army->SortKey;
	return Army->getName().bfmeCompare(other.Army->getName()) < 0;
}
