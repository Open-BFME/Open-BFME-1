// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: HordeSiegeEngineContainModuleData scalar-deleting destructor at
// retail RVA 0x0022CC40 (30 bytes). The exact constructor at 0x0022CB80 and
// complete destructor at 0x0022B0E0 agree on the derived module-data layout.
// This wrapper calls the destructor through ILT 0x000471A4.

class HordeSiegeEngineContainModuleData
{
public:
	virtual ~HordeSiegeEngineContainModuleData();
};

void forceHordeSiegeEngineContainModuleDataDeletingDestructor()
{
	HordeSiegeEngineContainModuleData value;
}
