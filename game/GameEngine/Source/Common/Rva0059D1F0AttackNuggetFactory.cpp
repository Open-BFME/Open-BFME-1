// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of Rva0059EE10AttackNuggetFactory.cpp (retail 0x0059EE10, 135B)
// and sibling of Rva005A01F0AttackNuggetFactory.cpp (retail 0x005A01F0,
// 152B): same S4_PARSE_WITH_FIELDS shape, same base constructor pinned as
// ??0BfmeAttackNuggetBase@@QAE@XZ at 0x0001B522, but this instance carries a
// wider tail -- two words (m_10, m_14) plus two bytes (m_18, m_19) -- and
// re-installs +0 with its own address before the post-parse m_04=m_14
// resync. Class re-declared locally per file policy; identity of the
// derived struct is not recovered.  The vtable-shaped global IS identified:
// the `mov dword ptr [esi],<imm32>` at 0x0059D1F0+0x29 stores 0x0110C780,
// which is Rva0059D1E0TailDtor's emitted vftable, so the reference is spelled
// through that symbol's real definer below.  The field table is still owed as a
// datum: the `push` at +0x62 is 0x0110C7C8 and no TU in game/ defines it (nor
// its siblings 0x0110C730 for 0x0059C4C0 and 0x0110C76C for 0x0059CB30).

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

// 0x0110C780 is not a datum this TU may own: it is Rva0059D1E0TailDtor's
// emitted vftable, and game/GameEngine/Source/Common/VptrTailJumpDestructors.cpp
// defines that symbol.  __identifier spells the compiler-emitted name and the
// array type keeps the decay-to-pointer the `mov dword ptr [esi],<imm32>` needs,
// the convention AptBooleanCreate.cpp uses for the same reason.
extern "C" const char __identifier("??_7Rva0059D1E0TailDtor@@6B@")[];
extern const FieldParse s4TableRva0059D1F0;

struct S4BuiltRva0059D1F0 : public Rva00489210
{
	int m_10, m_14;
	char m_18, m_19;

	S4BuiltRva0059D1F0()
	{
		m_00 = (int *)__identifier("??_7Rva0059D1E0TailDtor@@6B@");
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
