// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;
	static const char *s_bitNameList[];

public:
	BitFlags();
	Bool any() const;
	Bool testForAny( const BitFlags &other ) const;
	Bool testForNone( const BitFlags &other ) const;
	Bool testForAll( const BitFlags &other ) const;

};

template <int NUMBITS>
BitFlags<NUMBITS>::BitFlags()
{
}

template <int NUMBITS>
Bool BitFlags<NUMBITS>::any() const
{
	return m_bits.any();
}

typedef BitFlags<192> UpgradeMaskType;

class UpgradeMux
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
	virtual void slot9() = 0;
	virtual void getUpgradeActivationMasks( UpgradeMaskType &activation,
		UpgradeMaskType &conflicting ) const = 0;
	virtual void slot11() = 0;
	virtual Bool requiresAllActivationUpgrades() const = 0;

	Bool wouldUpgrade( const UpgradeMaskType &keyMask ) const;

	Bool m_upgradeExecuted;
};

// ?wouldUpgrade@UpgradeMux@@QBE_NABV?$BitFlags@$0MA@@@@Z
Bool UpgradeMux::wouldUpgrade( const UpgradeMaskType &keyMask ) const
{
	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );

	if ( activation.any() && !m_upgradeExecuted &&
		conflicting.testForNone( keyMask ) )
	{
		if ( requiresAllActivationUpgrades() )
			return keyMask.testForAll( activation );
		return keyMask.testForAny( activation );
	}
	return false;
}
