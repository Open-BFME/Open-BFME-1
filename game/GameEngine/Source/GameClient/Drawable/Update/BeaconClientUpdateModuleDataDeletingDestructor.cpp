// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BeaconClientUpdateModuleData scalar-deleting destructor at retail
// RVA 0x006032C0 (30 bytes). The exact constructor at 0x006031C0 installs
// vtable 0x01115280, whose slot zero routes through ILT 0x000217BA to this
// wrapper. The named module-data factory at 0x00121BF0 corroborates identity;
// the complete destructor is called through ILT 0x0000AC9A.

class BeaconClientUpdateModuleData
{
public:
	virtual ~BeaconClientUpdateModuleData();
};

void forceBeaconClientUpdateModuleDataDeletingDestructor()
{
	BeaconClientUpdateModuleData value;
}
