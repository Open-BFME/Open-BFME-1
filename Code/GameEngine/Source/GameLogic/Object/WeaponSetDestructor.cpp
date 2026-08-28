// cl: /DNDEBUG /MD /EHsc

// WeaponSet's retail destructor owns four pointer slots at +0x08 and then
// performs the inlined base teardown.  Keep the recovered object view in the
// proper WeaponSet source family.

class WeaponSetElement
{
public:
	virtual ~WeaponSetElement();
};

class WeaponSetBase
{
public:
	virtual void weaponSetBaseVslot();
	~WeaponSetBase() {}

private:
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponSet : public WeaponSetBase
{
public:
	virtual void weaponSetVslot();
	~WeaponSet();

private:
	WeaponSetElement *m_slots[4];
};

// ??1WeaponSet@@QAE@XZ
WeaponSet::~WeaponSet()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_slots[i])
		{
			delete m_slots[i];
		}
	}
}
