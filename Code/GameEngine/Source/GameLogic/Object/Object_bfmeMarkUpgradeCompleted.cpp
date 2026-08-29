// cl: /DNDEBUG /MD /EHsc

// Open-BFME: retail 0x001C5B90, 54 bytes.  This compact BFME helper marks one
// upgrade bit complete and immediately refreshes the Object's upgrade modules.
// It is distinct from canonical Object::giveUpgrade at 0x001C9F70, which also
// handles null input and the contain-module upgrade sink; the original public
// spelling of this smaller path has not survived.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeIndex( void ) const { return m_upgradeIndex; }

private:
	unsigned char m_unmodelled_00[ 0x20 ];
	UnsignedInt m_upgradeIndex;                         // +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeMarkUpgradeCompleted( const UpgradeTemplate *upgrade );
	void updateUpgradeModules( void );

private:
	unsigned char m_unmodelled_000[ 0x224 ];
	UnsignedInt m_objectUpgradesCompleted[ 6 ];          // +0x224
};

// ?bfmeMarkUpgradeCompleted@Object@@QAEXPBVUpgradeTemplate@@@Z
void Object::bfmeMarkUpgradeCompleted( const UpgradeTemplate *upgrade )
{
	UnsignedInt index = upgrade->getUpgradeIndex();
	m_objectUpgradesCompleted[ index >> 5 ] |= (1 << (index & 31));
	updateUpgradeModules();
}
