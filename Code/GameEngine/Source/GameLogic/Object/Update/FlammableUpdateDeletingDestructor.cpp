// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: FlammableUpdate scalar-deleting destructor at retail RVA
// 0x002937D0 (30 bytes). Its exact constructor at 0x00293270, complete
// destructor at 0x00293440, factories, pool, module name, and landed update
// methods establish the class. The destructor ILT is 0x0001BADB.

class FlammableUpdate
{
public:
	virtual ~FlammableUpdate();
};

void forceFlammableUpdateDeletingDestructor()
{
	FlammableUpdate value;
}
