// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// ScriptConditions::evaluateHasUnits names this lookup through ILT 0x0002AB9E.
// The matched two-argument overload receives the split owner and local name.

template <typename T>
class StringBase
{
protected:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase &other );
	~StringBase();
	void set( const StringBase &other );

private:
	void *m_data;
};

class BfmeWordEL;

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const BfmeWordEL &other );
};

class BfmeWordEL : private StringBase<char>
{
	friend class AsciiString;

public:
	BfmeWordEL( const BfmeWordEL &other ) : StringBase<char>( other ) {}
	~BfmeWordEL() {}
};

AsciiString &AsciiString::operator=( const BfmeWordEL &other )
{
	set( other );
	return *this;
}

struct BfmePairEL
{
	BfmeWordEL first;
	BfmeWordEL second;
};

BfmePairEL __cdecl Rva00194810( const BfmeWordEL &name );

static __forceinline void assignPair(AsciiString &localName,
	AsciiString &ownerName, const BfmePairEL &split)
{
	localName = split.first;
	ownerName = split.second;
}

class TeamPrototype;

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype( const AsciiString &name );
	TeamPrototype *findTeamPrototype( const AsciiString &name,
		const AsciiString &owner );
};

// ?findTeamPrototype@TeamFactory@@QAEPAVTeamPrototype@@ABVAsciiString@@@Z
TeamPrototype *TeamFactory::findTeamPrototype( const AsciiString &name )
{
	AsciiString localName;
	AsciiString ownerName;
	assignPair(localName, ownerName, Rva00194810(
		*reinterpret_cast<const BfmeWordEL *>( &name ) ));
	return findTeamPrototype( localName, ownerName );
}
