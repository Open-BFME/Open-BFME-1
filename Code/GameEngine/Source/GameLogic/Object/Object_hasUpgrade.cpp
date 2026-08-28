// cl: /DNDEBUG /MD /EHsc
// readable body of ?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::hasUpgrade, retail 0x001C9F50. A null template is false without
// asking anything; otherwise the template's mask at +0x20 replaces the argument
// in place and the test is tail-jumped to, so this function keeps nothing.

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	unsigned char m_unmodelled_00[ 0x20 ];
	UnsignedInt m_mask;						// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool hasUpgrade( const UpgradeTemplate *upgrade ) const;

	Bool hasUpgradeMask( UnsignedInt mask ) const;
};

// ?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z
Bool Object::hasUpgrade( const UpgradeTemplate *upgrade ) const
{
	if( upgrade == 0 )
		return false;

	return hasUpgradeMask( upgrade->m_mask );
}
