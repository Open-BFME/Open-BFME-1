// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RadarUpdateModuleData.
// Constructor 0x002A01C0 installs dedicated vtable 0x00CC1428; its slot
// zero routes through ILT 0x000400C0 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00041BF5 reaches cleanup body 0x002A03D0.

class RadarUpdateModuleData
{
public:
	virtual ~RadarUpdateModuleData();
private:
	friend void forceRadarUpdateModuleDataDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceRadarUpdateModuleDataDeletingDestructor(const RadarUpdateModuleData &that)
{
	RadarUpdateModuleData value(that);
}
