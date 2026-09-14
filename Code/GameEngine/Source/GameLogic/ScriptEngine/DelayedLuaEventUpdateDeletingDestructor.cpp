// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DelayedLuaEventUpdate scalar-deleting destructor at retail RVA
// 0x0028BFC0 (30 bytes). The exact constructor at 0x0028BEF0, complete
// destructor at 0x0028BCB0, factories, module name, and vtable 0x00CBD3B4
// establish the class. The destructor ILT is 0x0001B531.

class DelayedLuaEventUpdate
{
public:
	virtual ~DelayedLuaEventUpdate();
};

void forceDelayedLuaEventUpdateDeletingDestructor()
{
	DelayedLuaEventUpdate value;
}
