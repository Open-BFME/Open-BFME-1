// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of Rva0059EE10AttackNuggetFactory.cpp (retail 0x0059EE10, 135B):
// same S4_PARSE_WITH_FIELDS shape (allocate, call the matched base
// constructor through the ILT thunk pinned as
// ??0BfmeAttackNuggetBase@@QAE@XZ at 0x0001B522, then override fields), but
// this instance carries a TWO-WORD TAIL (m_10, m_14) beyond the base's own
// +0x0C, re-installs +0 with its own address (a richer vtable-shaped
// constant, see tools/vtable_lookup.py 0x0110CC98) instead of leaving the
// base's default, and re-reads the tail word back into +4 AFTER
// initFromINI() runs (the parse can rewrite +0x14, and +0x04 is kept in
// sync with it). Class re-declared locally per file policy; identity of the
// derived struct, its vtable-shaped global and the field table is not
// recovered.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

struct Gen_00489270
{
	void m(int a);
};

class Rva00489210
{
public:
	Rva00489210();		// ILT 0x0001B522, pinned ??0BfmeAttackNuggetBase@@QAE@XZ
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

extern int g_s4HeadRva005A01F0;
extern const FieldParse s4TableRva005A01F0;

struct S4BuiltRva005A01F0 : public Rva00489210
{
	int m_10, m_14;

	S4BuiltRva005A01F0()
	{
		m_00 = &g_s4HeadRva005A01F0;
		m_10 = 0;
		m_14 = 0x1e;
		m_04 = 0x1e;
		m_0C = 0;
		m_09 = 1;
	}
};

void s4ParseFieldsRva005A01F0(INI *ini, Gen_00489270 *sink)
{
	S4BuiltRva005A01F0 *t = new S4BuiltRva005A01F0;

	ini->initFromINI(t, &s4TableRva005A01F0);
	t->m_04 = t->m_14;

	sink->m((int)t);
}
