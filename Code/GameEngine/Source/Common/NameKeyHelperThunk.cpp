// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Open-BFME5: NAMEKEY(const AsciiString&)
// Retail: if data non-null, nameToKey(data+8); else nameToKey(empty literal).

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	int m_refCount;
	int m_numChars;
	// char payload follows at +8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};

// DIR32: TheNameKeyGenerator
extern NameKeyGenerator *g_theNameKeyGenerator;
// empty string literal for null AsciiString data
extern "C" char g_NAMEKEY_empty_string;

// ?NAMEKEY@@YA?AW4NameKeyType@@ABVAsciiString@@@Z
NameKeyType NAMEKEY(const AsciiString &s)
{
	const char *p;
	if (s.m_data)
		p = (const char *)s.m_data + 8;
	else
		p = &g_NAMEKEY_empty_string;
	return g_theNameKeyGenerator->nameToKey(p);
}
