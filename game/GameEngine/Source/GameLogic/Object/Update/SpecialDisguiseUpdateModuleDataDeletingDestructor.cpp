// cl: /DNDEBUG /MD /EHsc
//
// Retail's SpecialDisguiseUpdateModuleData vtable at 0x010B7770 names this
// scalar deleting destructor in slot zero (ILT 0x0002DC04 -> 0x00267A60). Its
// call target is the independently matched destructor body at 0x00267A90.

class __declspec(novtable) SpecialDisguiseUpdateModuleDataBase
{
public:
	virtual ~SpecialDisguiseUpdateModuleDataBase();
};

class SpecialDisguiseUpdateModuleData : public SpecialDisguiseUpdateModuleDataBase
{
	friend void forceSpecialDisguiseUpdateModuleDataDeletingDestructorCopy(const SpecialDisguiseUpdateModuleData &that);
public:
	__declspec(noinline) virtual ~SpecialDisguiseUpdateModuleData();
};

// ~SpecialDisguiseUpdateModuleData is matched out of line (SpecialDisguiseUpdateModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceSpecialDisguiseUpdateModuleDataDeletingDestructorCopy(const SpecialDisguiseUpdateModuleData &that)
{
	SpecialDisguiseUpdateModuleData value(that);
}
