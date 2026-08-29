// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PropagandaTowerBehaviorModuleData@@: Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// PropagandaTowerBehaviorModuleData's constructor, retail 0x0028DC60. The name
// used to sit on its five-byte incremental-link thunk, lifted naked; a thunk is
// not the constructor.
//
// There is no call to a base constructor at all - the derived class writes the
// vftable pointer at +0x00 itself and the base's one word at +0x04 is left
// alone, which is what an implicit base constructor looks like. Everything from
// +0x08 is zeroed, seven dwords and two flags, in one run off a zeroed register.

class PropagandaTowerBehaviorModuleDataBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h
class PropagandaTowerBehaviorModuleData : public PropagandaTowerBehaviorModuleDataBase
{
public:
	PropagandaTowerBehaviorModuleData();

private:
	int m_unmodelled_08;
	int m_unmodelled_0C;
	int m_autoHealPercentPerSecond;
	int m_pulseFX;
	int m_upgradeRequired;
	int m_upgradedAutoHealPercentPerSecond;
	int m_unmodelled_20;
	bool m_unmodelled_24;
	bool m_unmodelled_25;
};

PropagandaTowerBehaviorModuleData::PropagandaTowerBehaviorModuleData()
	: m_unmodelled_08( 0 ),
	  m_unmodelled_0C( 0 ),
	  m_autoHealPercentPerSecond( 0 ),
	  m_pulseFX( 0 ),
	  m_upgradeRequired( 0 ),
	  m_upgradedAutoHealPercentPerSecond( 0 ),
	  m_unmodelled_20( 0 ),
	  m_unmodelled_24( false ),
	  m_unmodelled_25( false )
{
}
