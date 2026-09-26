// cl: /DNDEBUG /MD /EHsc

// SplitHordeSpecialPowerModuleData's constructor, retail 0x0026B1D0. Eighteen bytes: the
// base's constructor and then this class's own vftable pointer, nothing else.
//
// The name used to sit on 0x00852130, which is INI::initFromINIMultiProc - a
// seventy-nine byte function that clears two sixteen-entry tables and is not a
// module-data constructor at all. It was one of seven names aliased onto those
// bytes; that claim is retracted here.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();
};

class SplitHordeSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	SplitHordeSpecialPowerModuleData();
};

SplitHordeSpecialPowerModuleData::SplitHordeSpecialPowerModuleData()
{
}
