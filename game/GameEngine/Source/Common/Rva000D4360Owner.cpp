// cl: /O2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x000D4360 (?d_000d4360@@YAXXZ, dump d_000c81e0.asm). cdecl,
// 2 stack params. Full control-flow decode (tools/dis_retail.py):
//   arg0 = a Thing/BFMEActionObject-layout object (vtable+0 like Thing,
//          m_template at +4 like Thing, m_status at +0x90 like
//          BFMEActionObject -- same "this" reused as both, matching Object).
//   arg1 = a peer record: field+0 is a pointer whose target has an
//          AsciiString at +0x28; field+4 is set to arg0 on success.
//   if (arg0 == 0) return true (failure sentinel);
//   if (arg1->m_owner != 0) return true;
//   if (!arg0->isKindOf(0x11)) return true;          (matched Thing::isKindOf)
//   tmpl = arg0->getTemplate();                       (matched inline Thing::getTemplate)
//   if (tmpl->m_name.compare(arg1->m_peer->m_name) != 0) return true;   (matched AsciiString::compare)
//   if (arg0->testStatus(2)) return true;
//   if (arg0->testStatus(0x13)) return true;          (matched BFMEActionObject::testStatus)
//   arg1->m_owner = arg0;
//   return false;
// callees: matched Thing::isKindOf (0x000A2CF0), matched Overridable::
// getFinalOverride (ILT 0x000022BB, inlined via Thing::getTemplate),
// matched AsciiString::compare (0x0005FEB0), matched BFMEActionObject::
// testStatus (0x000C4D40). No named caller; arg0/arg1's real class and the
// +0x28 field name are unproven, only the shape and the four real callees.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType { KINDOF_INVALID = 0 };

class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;

	Overridable *m_nextOverride;
};

class Rva000D4360Template : public Overridable
{
public:
	char m_pad0xc[0x28 - 8];
	AsciiString m_name;
};

class Thing
{
public:
	const Rva000D4360Template *getTemplate(void) const;
	Bool isKindOf(KindOfType t) const;

private:
	virtual ~Thing();

	const Rva000D4360Template *m_template;
};

inline const Rva000D4360Template *Thing::getTemplate(void) const
{
	const Rva000D4360Template *tmpl = m_template;
	if (tmpl == 0)
		return 0;
	if (tmpl->m_nextOverride)
		tmpl = (const Rva000D4360Template *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;

private:
	char m_slice_pad[0x90];
	UnsignedInt m_status[1];
};

class Rva000D4360Peer
{
public:
	Rva000D4360Template *m_peer;
	Thing *m_owner;
};

int rva000D4360(Thing *arg0, Rva000D4360Peer *arg1)
{
	if (arg0 == 0)
		return true;

	if (arg1->m_owner != 0)
		goto returnTrue;

	if (!arg0->isKindOf((KindOfType)0x11))
		goto returnTrue;

	const Rva000D4360Template *tmpl = arg0->getTemplate();

	if (tmpl->m_name.compare(arg1->m_peer->m_name) != 0)
		goto returnTrue;

	if (*(UnsignedInt *)((char *)arg0 + 0x90) & 4)
		goto returnTrue;

	if (!((BFMEActionObject *)arg0)->testStatus(0x13))
	{
		arg1->m_owner = arg0;
		return false;
	}

returnTrue:
	return true;
}
