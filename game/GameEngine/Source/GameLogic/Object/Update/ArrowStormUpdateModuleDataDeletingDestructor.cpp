// cl: /DNDEBUG /MD /EHsc
//
// Retail's ArrowStormUpdateModuleData vtable at 0x010B3668 names this scalar
// deleting destructor in slot zero (ILT 0x00032FEC -> 0x00257620). Its call
// target is the independently matched destructor body at 0x00257650.

class ArrowStormUpdateModuleDataBase
{
public:
	virtual ~ArrowStormUpdateModuleDataBase();
};

class ArrowStormUpdateModuleData : public ArrowStormUpdateModuleDataBase
{
public:
	__declspec(noinline) virtual ~ArrowStormUpdateModuleData();
};

ArrowStormUpdateModuleData::~ArrowStormUpdateModuleData()
{
}
