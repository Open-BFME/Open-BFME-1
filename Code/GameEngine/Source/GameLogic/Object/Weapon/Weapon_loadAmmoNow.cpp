// cl: /DNDEBUG /MD /EHsc
// readable body of ?loadAmmoNow@Weapon@@QAEXPBVObject@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp

// Open-BFME5: Weapon::loadAmmoNow, retail 0x001E9D60, 95 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and both
// members it calls are already ledgered names.
//
// A local bonus is built, filled in by computeBonus for this source with a zero
// mask, and handed to reloadWithBonus with a true. The bonus is twenty-four
// bytes of six floats, all starting at 1.0f -- its constructor is inlined and
// its six stores are what fix the size, which the frame's sub esp,0x18 agrees
// with.
//
// The stores are interleaved with the pushes for the first call because nothing
// orders them against each other; the compiler lays the arguments down first
// and fills the object behind them.

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonus
{
public:
	WeaponBonus()
	{
		m_bfmeA = 1.0f;
		m_bfmeB = 1.0f;
		m_bfmeC = 1.0f;
		m_bfmeD = 1.0f;
		m_bfmeE = 1.0f;
		m_bfmeF = 1.0f;
	}

	Real m_bfmeA, m_bfmeB, m_bfmeC, m_bfmeD, m_bfmeE, m_bfmeF;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	void loadAmmoNow(const Object *source);

protected:
	void computeBonus(const Object *source, UnsignedInt mask,
			WeaponBonus &bonus) const;			// ILT 0x00024591
	void reloadWithBonus(const Object *source, const WeaponBonus &bonus,
			Bool now);					// ILT 0x0003A0DA
};

// ?loadAmmoNow@Weapon@@QAEXPBVObject@@@Z
void Weapon::loadAmmoNow(const Object *source)
{
	WeaponBonus bonus;

	computeBonus(source, 0, bonus);

	reloadWithBonus(source, bonus, true);
}
