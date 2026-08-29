// cl: /DNDEBUG /MD /EHsc
// stlport

#include <bitset>

class BehaviorModule;

class Rva002D9A70Object
{
};

void Rva002D9A70Invoke(Rva002D9A70Object *upgrade);

template <unsigned int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	void clear()
	{
		m_bits.reset();
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> UpgradeMaskType;

class __declspec(novtable) BFMEBehaviorUpgradeShim
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual Rva002D9A70Object *getUpgrade() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeResetAllUpgrades();

private:
	unsigned char m_pad000[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[0x30];
	UpgradeMaskType m_objectUpgradesCompleted;
};

// Clear the full object mask, then reset every upgrade-bearing behavior.
void Object::bfmeResetAllUpgrades()
{
	m_objectUpgradesCompleted.clear();

	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BFMEBehaviorUpgradeShim *shim =
			reinterpret_cast<BFMEBehaviorUpgradeShim *>(
				reinterpret_cast<char *>(*module) + 0x0c);
		Rva002D9A70Object *upgrade = shim->getUpgrade();
		if (upgrade)
			Rva002D9A70Invoke(upgrade);
	}
}
