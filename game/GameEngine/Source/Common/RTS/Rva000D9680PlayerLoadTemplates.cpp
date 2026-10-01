// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x000D9680 is reached only from the matched Player::loadPostProcess
// (0x000D9D30) through ILT 0x0000D305, so the owner is Player; the method name
// is not recovered. It copies the vector<AsciiString> at PlayerTemplate+0xF4,
// resolves each name through TheThingFactory and hands every found template,
// with the Player, to the helper on the Player subobject at +0x684.
//
// The inline forwarder the Zero Hour header declares (ThingFactory.h:
// `return findTemplateInternal(name, check)`) is what yields retail's LEA EAX;
// BFME's out-of-line lookup is BfmeThingFactory::findTemplate at 0x00137E80 and
// takes the name only (RET 4). Calling the lookup directly allocates the
// element address in ECX/EDX instead.

#include "ascii_string.h"
#include <vector>

struct Rva000D9680Template
{
	char pad[0xf4];
	std::vector<AsciiString> strings;
};

class ThingTemplate;

class ThingFactory
{
};

// Retail's factory lookup is BfmeThingFactory::findTemplate (0x00137E80). The
// TU-local inline forwarder keeps retail's LEA EAX shape and is always inlined,
// so it needs no name of its own beyond the call it forwards to.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplateForwarder(const AsciiString &name) { return findTemplate(name); }
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class Rva000D9680Player;

// Retail 0x000FB3F0 (ILT 0x00049B1B): thiscall on Player+0x684 taking two
// stack arguments (RET 8). Identity not recovered.
struct Rva000FB3F0
{
	void rva000FB3F0(const ThingTemplate *, Rva000D9680Player *);
};

class Rva000D9680Player
{
public:
	void rva000D9680();

	void *vtable;
	Rva000D9680Template *m_playerTemplate;
	char pad008[0x684 - 8];
	Rva000FB3F0 field684;
};

void Rva000D9680Player::rva000D9680()
{
	if (m_playerTemplate)
	{
		std::vector<AsciiString> names = m_playerTemplate->strings;
		int count = names.size();
		for (int index = 0; index < count; ++index)
		{
			const ThingTemplate *resolved = ((BfmeThingFactory *)TheThingFactory)->findTemplateForwarder(names[index]);
			if (resolved)
				field684.rva000FB3F0(resolved, this);
		}
	}
}
