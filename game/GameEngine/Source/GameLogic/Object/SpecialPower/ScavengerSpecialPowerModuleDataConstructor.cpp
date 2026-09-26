// cl: /DNDEBUG /MD /EHsc

// ScavengerSpecialPowerModuleData's constructor, retail 0x00265A80.
//
// The base constructor is 0x00268120, shared by every SpecialPower module data
// and running to +0x210 where each one's own fields start. That address is
// byte-identical to and folded with RiderChangeContainModuleData's, so it
// cannot name the class, and SpecialPowerModuleData is already pinned elsewhere
// - at 0x002A5AA0, which is SpecialAbilityUpdateModuleData - so the base is
// pinned here under a stand-in name of this tree's rather than that one.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

class ScavengerSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	ScavengerSpecialPowerModuleData();

private:
	int m_unmodelled_210;					// +0x210
};

ScavengerSpecialPowerModuleData::ScavengerSpecialPowerModuleData()
	: m_unmodelled_210( 0 )
{
}
