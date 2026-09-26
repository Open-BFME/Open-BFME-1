// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: INI parse-and-register factory at retail 0x0059EE10 (135B).
// Same S4_PARSE_WITH_FIELDS shape as S4ParseThenRegisterWithFields.cpp
// (twin 0x0059C4C0, 142B): allocate 0x10 bytes, run the matched base
// constructor Rva00489210 (its own call goes through the ILT thunk pinned
// as ??0BfmeAttackNuggetBase@@QAE@XZ at 0x0001B522, which jumps to
// 0x00489210), then override m_00/m_04/m_0C/m_09.  This instance has no
// tail fields (S4_NO_TAIL) and AT4 == 2.  Class re-declared locally per
// file policy; identity of the derived struct, s4Head global and field
// table is not recovered.

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
	Rva00489210();
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

extern int g_s4HeadRva0059EE10;
extern const FieldParse s4TableRva0059EE10;

struct S4BuiltRva0059EE10 : public Rva00489210
{
	S4BuiltRva0059EE10()
	{
		m_00 = &g_s4HeadRva0059EE10;
		m_04 = 2;
		m_0C = 0;
		m_09 = 1;
	}
};

void s4ParseFieldsRva0059EE10(INI *ini, Gen_00489270 *sink)
{
	S4BuiltRva0059EE10 *t = new S4BuiltRva0059EE10;

	ini->initFromINI(t, &s4TableRva0059EE10);

	sink->m((int)t);
}
