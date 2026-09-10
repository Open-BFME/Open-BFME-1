// ?findTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// BFME's one-argument TeamFactory::findTeam accepts the slash-qualified
// owner/name key.  The two-name lookup and createInactiveTeam bodies are
// already matched in sibling TUs; this TU keeps their overloads local so the
// generated names remain the BFME decorations.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString& operator=(const AsciiString& other);
	~AsciiString();

private:
	void *m_data;
};

class BfmeWordEL;

template <typename T>
class StringBaseEL
{
friend class BfmeWordEL;

private:
	StringBaseEL(const StringBaseEL &other);
	StringBaseEL(const StringBaseEL &other, int start, int length);
	~StringBaseEL() { releaseBuffer(); }
	void releaseBuffer();

protected:
	int getLength() const { return m_data ? m_data->length : 0; }
	T getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class BfmeWordEL : private StringBaseEL<char>
{
public:
	BfmeWordEL(const BfmeWordEL &other)
		: StringBaseEL<char>(other) {}
	BfmeWordEL(const BfmeWordEL &other, int start, int length)
		: StringBaseEL<char>(other, start, length) {}
	~BfmeWordEL() {}
};

struct BfmePairEL
{
public:
	BfmeWordEL first;
	BfmeWordEL second;
};

extern BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

class Team;

class TeamPrototype
{
public:
	Team *firstTeam() const
	{
		return m_firstTeam;
	}

	bool isSingleton() const
	{
		return (m_flags & 1) != 0;
	}

private:
	char m_prefix[0x18];
	unsigned int m_flags;
	char m_body[0x258];
	Team *m_firstTeam;
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);
	Team *createInactiveTeam(const AsciiString &name,
		const AsciiString &ownerName);
	Team *findTeam(const AsciiString &name);
};

// ?findTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z
Team *TeamFactory::findTeam(const AsciiString &name)
{
	TeamFactory *factory = this;
	AsciiString teamName;
	AsciiString ownerName;
	const BfmePairEL &split = Rva00194810(
		*reinterpret_cast<const BfmeWordEL *>(&name));
	const BfmePairEL *splitPtr = &split;
	teamName = *reinterpret_cast<const AsciiString *>(&splitPtr->first);
	ownerName = *reinterpret_cast<const AsciiString *>(&splitPtr->second);

	TeamPrototype *prototype = factory->findTeamPrototype(teamName, ownerName);
	if (prototype)
	{
		Team *team = prototype->firstTeam();
		if (team)
			return team;
		if (!prototype->isSingleton())
			return factory->createInactiveTeam(teamName, ownerName);
	}
	return 0;
}
