// cl: /EHsc -D_STLP_NO_EXCEPTIONS
// stlport
//
// The INI `Weapon` block's `DamageNugget = ` field callback (the exe's
// FieldParse table at 0x0109FE18 maps that token to 0x001E5940), a sibling of
// the nine allocate-notify-and-link bodies in WeaponNuggetParse.cpp. Same owner offsets (0x34 / 0x54 / 0x528 / 0x538),
// plus a byte store at owner+0x4DC after the list splice. Allocation size
// 0xA4. The nugget class and its field parser are pinned by address in
// reverse/symbols.csv and keep their address-derived names.

#include <list>

class WeaponTemplate
{
public:
	char m_gap0[0x4DC];
	char m_ready;
	char m_gap1[0x528 - 0x4DD];
	char m_flag;
	char m_gap2[0x538 - 0x529];
	_STL::list<void *> m_list;
};

class Made001E5940
{
public:
	__declspec(noinline) Made001E5940();
	virtual void slot();

	char m_gap04[0x34 - 4];
	WeaponTemplate *m_owner;
	char m_gap38[0x54 - 0x38];
	char m_flag;
	char m_tail55[0xA4 - 0x55];
};

class INI;

void q4Parse001E5940(INI *a, Made001E5940 *m, int c, int d);

void parseDamageNugget(INI *ini, WeaponTemplate *weapon)
{
	Made001E5940 *m = new Made001E5940;
	m->m_owner = weapon;
	q4Parse001E5940(ini, m, 0, 0);
	m->m_flag = weapon->m_flag;
	weapon->m_list.push_back(m);
	weapon->m_ready = 1;
}
