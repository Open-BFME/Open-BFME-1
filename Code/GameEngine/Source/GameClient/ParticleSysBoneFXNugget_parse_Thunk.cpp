// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: ParticleSysBone FXList nugget parse at 0x0042C980 (401B).
// Keyword ParticleSysBone in FXList's FieldParse; type discriminator 9.
// Custom token parser (not MultiIniFieldParse): inline derived ctor, then
// getNextAsciiString + toLower into +0xB4, strncpy bone name into +0xCC,
// optional FollowBone bool at +0xB8, optional FXTrigger index at +0xBC,
// then list push_back. INI seps come from +0x41C (getSepsColon).

#include <list>

extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *, const char *, unsigned int);
#pragma intrinsic(strcmp)

typedef bool Bool;

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
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other);
	void toLower();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	AsciiString getNextAsciiString();
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	const char *getSepsColon() const { return m_sepsColon; }
	static Bool scanBool(const char *token);
	static int scanIndexList(const char *token, const char *const *names);

	char m_unreconstructed_000[0x41c];
	const char *m_sepsColon;
};

const char *const TheFXTriggerNames[] = {
	"NONE",
	"CATAPULT_ROCK",
	"TREBUCHET_ROCK",
	0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual void v0();

	int m_nuggetType;
	char m_unreconstructed_08[0xb4 - 8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	int m_unreconstructed_00;
	std::list<FXNugget *> m_nuggets;
	char m_added;

	void addFXNugget(FXNugget *fxn)
	{
		m_nuggets.push_back(fxn);
		m_added = 1;
	}
};

class ParticleSysBoneFXNugget : public FXNugget
{
public:
	ParticleSysBoneFXNugget()
	{
		m_nuggetType = 9;
	}

	static void parse(INI *, void *, void *, const void *);

private:
	AsciiString m_name;
	Bool m_followBone;
	unsigned char m_padB9[3];
	int m_fxTrigger;
	unsigned char m_unreconstructed_c0[0xc];
	char m_boneName[0x40];
};

// ?parse@ParticleSysBoneFXNugget@@SAXPAVINI@@PAX1PBX@Z
void ParticleSysBoneFXNugget::parse(INI *ini, void *instance, void *, const void *)
{
	ParticleSysBoneFXNugget *nugget = new ParticleSysBoneFXNugget;
	INI *p = ini;
	nugget->m_name = p->getNextAsciiString();
	nugget->m_name.toLower();
	const char *bone = p->getNextTokenOrNull(p->getSepsColon());
	strncpy(nugget->m_boneName, bone, 0x3F);
	const char *tok = p->getNextTokenOrNull(p->getSepsColon());
	if (tok && strcmp(tok, "FollowBone") == 0)
		nugget->m_followBone = INI::scanBool(p->getNextToken(p->getSepsColon()));
	else
		nugget->m_followBone = false;
	tok = p->getNextTokenOrNull(p->getSepsColon());
	if (tok && strcmp(tok, "FXTrigger") == 0)
	{
		const char *trigger = p->getNextToken(p->getSepsColon());
		nugget->m_fxTrigger = INI::scanIndexList(trigger, TheFXTriggerNames);
	}
	else
		nugget->m_fxTrigger = 0;
	((FXList *)instance)->addFXNugget(nugget);
}
