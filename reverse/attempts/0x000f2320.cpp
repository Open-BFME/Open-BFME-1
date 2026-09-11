// ?d_000f2320@@YAXXZ
// partial score=0.9 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BFME's one-argument TeamFactory lookup splits a qualified team name into
// its owner and local-name components, then forwards both to the independently
// matched two-argument overload at 0x000EFE10.  The named
// ScriptConditions::evaluateHasUnits caller reaches this overload through ILT
// 0x0002AB9E; Rva00194810 is the matched first-'/' splitter.

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
	{
		BfmePairEL split = Rva00194810(
			*reinterpret_cast<const BfmeWordEL *>( &name ) );

		localName = split.first;
		ownerName = split.second;
	}
	return findTeamPrototype( localName, ownerName );
}
