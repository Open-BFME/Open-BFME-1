// cl: /DNDEBUG /MD /EHsc
//
// Retail's ArrowStormUpdateModuleData vtable at 0x010B3668 names this scalar
// deleting destructor in slot zero (ILT 0x00032FEC -> 0x00257620). Its call
// target is the independently matched destructor body at 0x00257650.

class __declspec(novtable) ArrowStormUpdateModuleDataBase
{
public:
	virtual ~ArrowStormUpdateModuleDataBase();
};

class ArrowStormUpdateModuleData : public ArrowStormUpdateModuleDataBase
{
	friend void forceArrowStormUpdateModuleDataDeletingDestructorCopy(const ArrowStormUpdateModuleData &that);
public:
	__declspec(noinline) virtual ~ArrowStormUpdateModuleData();
};

// ~ArrowStormUpdateModuleData is matched out of line (ArrowStormUpdateModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceArrowStormUpdateModuleDataDeletingDestructorCopy(const ArrowStormUpdateModuleData &that)
{
	ArrowStormUpdateModuleData value(that);
}
