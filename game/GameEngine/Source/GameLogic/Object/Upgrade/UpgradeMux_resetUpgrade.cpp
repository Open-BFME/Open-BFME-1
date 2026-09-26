// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// UpgradeMux::resetUpgrade at retail 0x002D9DF0.  The FireWeaponWhenDeadBehavior
// secondary vtable at 0x010A3F40 routes slot 3 through ILT 0x0001C071 to this
// body; UpgradeModule.h's interface order identifies that slot as resetUpgrade.

#include <bitset>

typedef bool Bool;

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	Bool testForAny( const BitFlags &other ) const;
};

typedef BitFlags<192> UpgradeMaskType;

class UpgradeMux
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void getUpgradeActivationMasks( UpgradeMaskType &activation,
		UpgradeMaskType &conflicting ) const = 0;
	virtual void slot11();
	virtual void requiresAllActivationUpgrades();

	virtual Bool resetUpgrade( const UpgradeMaskType &keyMask );

	Bool m_upgradeExecuted;
};

// ?resetUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0MA@@@@Z
Bool UpgradeMux::resetUpgrade( const UpgradeMaskType &keyMask )
{
	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );

	if ( activation.testForAny( keyMask ) && m_upgradeExecuted )
	{
		m_upgradeExecuted = false;
		return true;
	}
	return false;
}
