// cl: /EHsc -D_STLP_NO_EXCEPTIONS
// stlport
//
// The nine `<Something>Nugget = ` field callbacks of the INI `Weapon` block.
//
// WHICH KEY REACHES WHICH FUNCTION IS READ OUT OF THE EXE, not inferred.  The
// `Weapon` block is parsed by `WeaponStore::parseWeaponTemplateDefinition`
// (0x001E9C40), whose 112-entry `FieldParse` table at 0x0109FE18 pairs each
// token with its `INIFieldParseProc`.  Nine of those pairs land here:
//
//     AttributeModifierNugget      -> 0x001E5A20
//     SpecialModelConditionNugget  -> 0x001E5AF0
//     ParalyzeNugget               -> 0x001E5BC0
//     WeaponOCLNugget              -> 0x001E5D60
//     ProjectileNugget             -> 0x001E5E30
//     MetaImpactNugget             -> 0x001E5F00
//     HordeAttackNugget            -> 0x001E60A0
//     SpawnAndFadeNugget           -> 0x001E6170
//     LuaEventNugget               -> 0x001E6240
//
// The other four nugget keys are siblings in WeaponNuggetParseDamage.cpp
// (`DamageNugget`), Q4MakeNotifyLinkFlagC90.cpp (`DamageFieldNugget`) and
// Q4MakeNotifyLinkFlagFD0.cpp (`GrabNugget`).
//
// So the second parameter is the block instance -- the `WeaponTemplate` being
// parsed -- and the first is the `INI` reader.  The trailing `store` and
// `userData` arguments of `INIFieldParseProc` are pushed by the caller and
// never read, which is why these are two-parameter __cdecl bodies.
//
// Each is 157 bytes and does the same five things: allocate the nugget, point
// it back at the weapon, run the per-nugget field parse, copy one flag byte
// down from the weapon, and append the nugget to the weapon's nugget list:
//
//     p = new <MADE>;                      (SIZE varies; null path leaves p=0)
//     p->m_owner = weapon;
//     <NOTIFY>( ini, p, 0, 0 );
//     p->m_flag = weapon->m_flag;          (byte at weapon+0x528 -> p+0x54)
//     weapon->m_list.push_back( p );       (list head pointer at weapon+0x538)
//
// WHAT THE BYTES SHOW.  The tail is STLport's list insert, fully inlined and
// unmistakable: `push 0xc / call 0x0082E540` allocates a twelve-byte node,
// `lea ecx,[eax+8] / test / je / mov [ecx],esi` is the NULL-GUARDED PLACEMENT
// CONSTRUCT of the four-byte payload at node+8, and the four stores that
// follow splice the node in before the sentinel -- node->next = sentinel,
// node->prev = sentinel->prev, sentinel->prev->next = node, sentinel->prev =
// node.  That fixes the node layout as {next, prev, data} and the payload as
// one pointer, so the container is a list of pointers and weapon+0x538 is its
// _M_node.  The whole thing is compiled from the VENDORED STLport header; no
// replica.
//
// THE INLINING IS A FLAG, NOT LUCK.  Under plain `/EHsc` STLport's
// _M_create_node keeps its unwind guard and does NOT inline: the body then
// ends in `lea edx,[esp+8] / lea ecx,[weapon+0x538] / push edx / call
// _M_create_node` and carries an extra `mov [esp+0x18],esi` spill for the EH
// cleanup.  Adding `-D_STLP_NO_EXCEPTIONS` removes STLport's guard while
// leaving MSVC's own frame -- which retail needs, because the `new` and the
// constructor ARE protected (states 0 then -1 around them).  So retail built
// this translation unit with C++ EH on and STLport exceptions off, and both
// halves of that are in the bytes.
//
// The deferred `add esp,0x14` covers five dwords -- the notify call's four
// arguments and the later `push 0xc` -- which is why the node allocation looks
// like it is missing its own cleanup.
//
// THREE FIELDS VARY: the allocation size, the constructor's REL32 and the
// notify callee's REL32.  Sizes are 0x58, 0x60, 0x64, 0x68 (four times), 0x6c,
// 0x7c; every one of the nine has its own constructor AND its own notify
// callee, and the four rows sharing size 0x68 have four different pairs, so no
// field stands in for another.  The offsets 0x34, 0x54, 0x528 and 0x538 are
// identical in all nine, which is why ONE owner class is declared rather than
// nine, and why the list is spelled `list<void *>`: the payload is one pointer
// and the nine nugget classes differ.
//
// THE NUGGET CLASSES THEMSELVES ARE STILL UNIDENTIFIED.  `Made001E5A20` and
// friends, their constructors and their `q4Notify` field parsers are pinned by
// address in reverse/symbols.csv and keep address-derived names; only the entry
// points the INI table names are named here.  `WeaponTemplate` carries an
// opaque layout because this TU proves only the three offsets it touches.

#include <list>

class INI;

class WeaponTemplate
{
public:
	char m_gap0[ 0x528 ];
	char m_flag;
	char m_gap1[ 0x538 - 0x529 ];
	_STL::list<void *> m_list;
};

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();
	virtual void slot();

	char m_gap04[ 0x34 - 4 ];
	WeaponTemplate *m_owner;
	char m_gap38[ 0x54 - 0x38 ];
	char m_flag;
	char m_tail55[ 3 ];
};

#define Q4_MAKE_AND_LINK( T, NAME, SIZE, MADE )                                 	class MADE : public GenBase002DF2B0                                   	{                                                                     	public:                                                               		__declspec(noinline) MADE();                                      		virtual void slot();                                               		char m_tail[ SIZE - 0x58 ];                                       	};                                                                    	void q4Notify##T( void *ini, MADE *m, int c, int d );                   	void NAME( INI *ini, WeaponTemplate *weapon )                            	{                                                                     		MADE *m = new MADE;                                               		m->m_owner = weapon;                                                   		q4Notify##T( ini, m, 0, 0 );                                        		m->m_flag = weapon->m_flag;                                            		weapon->m_list.push_back( m );                                         	}

#define Q4_MAKE_AND_LINK_TAIL( T, NAME, MADE, TAIL )                            	class MADE : public GenBase002DF2B0                                   	{                                                                     	public:                                                               		__declspec(noinline) MADE();                                      		virtual void slot();                                               	private:                                                              		TAIL m_tail;                                                       	};                                                                    	void q4Notify##T( void *ini, MADE *m, int c, int d );                   	void NAME( INI *ini, WeaponTemplate *weapon )                            	{                                                                     		MADE *m = new MADE;                                               		m->m_owner = weapon;                                                   		q4Notify##T( ini, m, 0, 0 );                                        		m->m_flag = weapon->m_flag;                                            		weapon->m_list.push_back( m );                                         	}

// These are members so MSVC keeps the derived vptr store ahead of their
// initialization, matching the constructor order retail records.
struct Tail001E5E30
{
	__forceinline Tail001E5E30() { m_60 = 0; m_64 = 0; m_58 = 0; m_5c = 0; }
	int m_58, m_5c, m_60, m_64;
};

struct Tail001E6240
{
	__forceinline Tail001E6240()
	{
		m_58 = 0; m_5c = 0; m_60 = 0; m_61 = 0; m_62 = 0;
	}
	int m_58, m_5c;
	char m_60, m_61, m_62, m_pad63;
};

extern "C" char Made001E5A20_vtbl;

class __declspec(novtable) Made001E5A20 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E5A20();
	virtual void slot();

	volatile int m_58;
	volatile int m_5c;
	volatile int m_60;
	volatile float m_64;
};

void q4Notify001E5A20(void *a, Made001E5A20 *m, int c, int d);

void parseAttributeModifierNugget(INI *ini, WeaponTemplate *weapon)
{
	Made001E5A20 *m = new Made001E5A20;
	m->m_owner = weapon;
	q4Notify001E5A20(ini, m, 0, 0);
	m->m_flag = weapon->m_flag;
	weapon->m_list.push_back(m);
}

Made001E5A20::Made001E5A20()
{
	int zero = 0;
	*reinterpret_cast<char *volatile *>(this) = &Made001E5A20_vtbl;
	m_58 = zero;
	m_60 = zero;
	m_5c = 15;
	m_64 = 3.14159274f;
}
Q4_MAKE_AND_LINK( 001E5AF0, parseSpecialModelConditionNugget, 0x68, Made001E5AF0 )
Q4_MAKE_AND_LINK( 001E5BC0, parseParalyzeNugget, 0x68, Made001E5BC0 )
Q4_MAKE_AND_LINK_TAIL( 001E5E30, parseProjectileNugget, Made001E5E30, Tail001E5E30 )
Q4_MAKE_AND_LINK( 001E5F00, parseMetaImpactNugget, 0x7c, Made001E5F00 )
Q4_MAKE_AND_LINK( 001E60A0, parseHordeAttackNugget, 0x58, Made001E60A0 )
Q4_MAKE_AND_LINK( 001E6170, parseSpawnAndFadeNugget, 0x6c, Made001E6170 )
Q4_MAKE_AND_LINK_TAIL( 001E6240, parseLuaEventNugget, Made001E6240, Tail001E6240 )

class Made001E5D60 : public GenBase002DF2B0
{
public:
	__declspec(noinline) Made001E5D60();
	virtual void slot();

private:
	class Tail
	{
	public:
		__forceinline Tail() { m_second = 0; m_first = 0; }
	private:
		int m_first;
		int m_second;
	} m_tail;
};

void q4Notify001E5D60( void *a, Made001E5D60 *m, int c, int d );

void parseWeaponOCLNugget( INI *ini, WeaponTemplate *weapon )
{
	Made001E5D60 *m = new Made001E5D60;
	m->m_owner = weapon;
	q4Notify001E5D60( ini, m, 0, 0 );
	m->m_flag = weapon->m_flag;
	weapon->m_list.push_back( m );
}

Made001E5D60::Made001E5D60()
{
}

Made001E5E30::Made001E5E30()
{
}

Made001E6240::Made001E6240()
{
}
