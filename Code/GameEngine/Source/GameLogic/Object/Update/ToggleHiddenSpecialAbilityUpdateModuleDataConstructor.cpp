// cl: /DNDEBUG /MD /EHsc

// ToggleHiddenSpecialAbilityUpdateModuleData's constructor, retail 0x0026BFB0. Eighteen bytes: the
// base's constructor and then this class's own vftable pointer, nothing else.
//
// The name used to sit on 0x00852130, which is INI::initFromINIMultiProc - a
// seventy-nine byte function that clears two sixteen-entry tables and is not a
// module-data constructor at all. It was one of seven names aliased onto those
// bytes; that claim is retracted here.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

	virtual void moduleDataAnchor();
};

class ToggleHiddenSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
};

ToggleHiddenSpecialAbilityUpdateModuleData::ToggleHiddenSpecialAbilityUpdateModuleData()
{
}
