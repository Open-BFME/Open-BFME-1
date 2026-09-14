// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RadarUpdateModuleData.
// Constructor 0x002A01C0 installs dedicated vtable 0x00CC1428; its slot
// zero routes through ILT 0x000400C0 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00041BF5 reaches cleanup body 0x002A03D0.

class RadarUpdateModuleData
{
protected:
	virtual ~RadarUpdateModuleData();
private:
	friend void forceRadarUpdateModuleDataDeletingDestructor();
};

void forceRadarUpdateModuleDataDeletingDestructor()
{
	RadarUpdateModuleData value;
}
