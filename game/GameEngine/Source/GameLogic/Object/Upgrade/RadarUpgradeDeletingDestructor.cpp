// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RadarUpgrade.
// Vtable 0x00CCDB64 slots name this class (?getClassMemoryPool@RadarUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00005AF6 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00021D55 reaches cleanup body 0x002D7A20.

class RadarUpgrade
{
protected:
	virtual ~RadarUpgrade();
private:
	friend void forceRadarUpgradeDeletingDestructor();
};

void forceRadarUpgradeDeletingDestructor()
{
	RadarUpgrade value;
}
