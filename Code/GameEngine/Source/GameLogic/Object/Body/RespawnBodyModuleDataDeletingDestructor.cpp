// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for RespawnBodyModuleData.
// The exact constructor at 0x002149D0 installs dedicated vtable 0x010A92C8;
// slot zero routes through ILT 0x0001A46A to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0001BE1E.

class RespawnBodyModuleData
{
public:
	virtual ~RespawnBodyModuleData();
};

void forceRespawnBodyModuleDataDeletingDestructor()
{
	RespawnBodyModuleData value;
}
