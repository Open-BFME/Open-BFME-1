// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of Rva0059EE10AttackNuggetFactory.cpp (retail 0x0059EE10, 135B)
// and sibling of Rva005A01F0AttackNuggetFactory.cpp (retail 0x005A01F0,
// 152B): same S4_PARSE_WITH_FIELDS shape, same base constructor pinned as
// ??0BfmeAttackNuggetBase@@QAE@XZ at 0x0001B522, but this instance carries a
// wider tail -- two words (m_10, m_14) plus two bytes (m_18, m_19) -- and
// re-installs +0 with its own address before the post-parse m_04=m_14
// resync. Class re-declared locally per file policy; identity of the
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

extern int g_s4HeadRva0059D1F0;
extern const FieldParse s4TableRva0059D1F0;

struct S4BuiltRva0059D1F0 : public Rva00489210
{
	int m_10, m_14;
	char m_18, m_19;

	S4BuiltRva0059D1F0()
	{
		m_00 = &g_s4HeadRva0059D1F0;
		m_10 = 0;
		m_14 = 0x1e;
		m_18 = 1;
		m_19 = 0;
		m_04 = 0x1e;
	}
};

void s4ParseFieldsRva0059D1F0(INI *ini, Gen_00489270 *sink)
{
	S4BuiltRva0059D1F0 *t = new S4BuiltRva0059D1F0;

	ini->initFromINI(t, &s4TableRva0059D1F0);
	t->m_04 = t->m_14;

	sink->m((int)t);
}
