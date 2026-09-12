// cl: /DNDEBUG /MD /EHsc
//
// Retail's SpecialDisguiseUpdateModuleData vtable at 0x010B7770 names this
// scalar deleting destructor in slot zero (ILT 0x0002DC04 -> 0x00267A60). Its
// call target is the independently matched destructor body at 0x00267A90.

class SpecialDisguiseUpdateModuleDataBase
{
public:
	virtual ~SpecialDisguiseUpdateModuleDataBase();
};

class SpecialDisguiseUpdateModuleData : public SpecialDisguiseUpdateModuleDataBase
{
public:
	__declspec(noinline) virtual ~SpecialDisguiseUpdateModuleData();
};

SpecialDisguiseUpdateModuleData::~SpecialDisguiseUpdateModuleData()
{
}
