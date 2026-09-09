// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
// LivingWorld region ConnectsTo callback at 0x0061AD20, 188 bytes.
// Table 0x01116D70 registers ILT 0x0002245D under ConnectsTo at
// 0x01116E20; the callback appends strings to instance+0x30. The
// historical class/callback names are unproven, so the class is tagged
// by the body address. There is no GameSpyGroupRoom temporary.
//
// INI constructor 0x00851230 initializes +0x41C to 0x011304B8:
// whitespace, equals and colon separators. A quoted-string label would
// be wrong: the quote separators are the next field at +0x420.
#include "StringInline.h"
#include <vector>
// Reuse the established 0x00063700 vector element tag from AptScreenShow.
// Its out-of-line StringBase copy distinguishes this growth body from the
// 0x00757C70 instantiation; both elements occupy one pointer.
class Open2Elem063700 : public AsciiString
{
public:
	Open2Elem063700(const char *text) : AsciiString(text) {}
	Open2Elem063700(const Open2Elem063700 &other) : AsciiString(other) {}
};

class INI
{
public:
	char m_prefix[0x41c];
	const char *m_colonSeparators;

	const char *getSepsColon() { return m_colonSeparators; }
	const char *getNextTokenOrNull(const char *);
};

struct Rva0061AD20Region
{
	char m_prefix[0x30];
	_STL::vector<Open2Elem063700> m_connections;
};

class Rva0061AD20
{
public:
	static void parseConnections(INI *, void *, void *, const void *);
};

// Full retail body ends with ret at +0xBB; padding starts at +0xBC.
void Rva0061AD20::parseConnections(INI *ini, void *instance, void *, const void *)
{
	Rva0061AD20Region *self = (Rva0061AD20Region *)instance;
	for (const char *token = ini->getNextTokenOrNull(ini->getSepsColon()); token;
		token = ini->getNextTokenOrNull(ini->getSepsColon()))
	{
		self->m_connections.push_back(token);
	}
}
