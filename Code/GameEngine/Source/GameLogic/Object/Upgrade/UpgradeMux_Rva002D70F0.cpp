// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// near-twin of ?wouldUpgrade@UpgradeMux@@QBE_NABV?$BitFlags@$0MA@@@@Z (0x002D9D00,
// UpgradeMux_wouldUpgrade.cpp): identical shape (getUpgradeActivationMasks,
// activation.any(), conflicting.testForNone(keyMask), requiresAllActivationUpgrades
// branch to testForAll/testForAny) but WITHOUT the `!m_upgradeExecuted` guard --
// retail loads the keyMask pointer and calls testForNone directly after
// activation.any() with no byte ptr[esi+4] load/test in between. Real name and
// owning class unproven; landed address-derived under the UpgradeMux home dir
// since the vtable/field shape otherwise matches the class exactly.

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

class Rva002D70F0Mux
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
	virtual Bool requiresAllActivationUpgrades() const = 0;

	Bool rva002d70f0( const UpgradeMaskType &keyMask ) const;
};

// ?d_002d70f0@@YAXXZ
Bool Rva002D70F0Mux::rva002d70f0( const UpgradeMaskType &keyMask ) const
{
	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );

	if ( activation.any() && conflicting.testForNone( keyMask ) )
	{
		if ( requiresAllActivationUpgrades() )
			return keyMask.testForAll( activation );
		return keyMask.testForAny( activation );
	}
	return false;
}
