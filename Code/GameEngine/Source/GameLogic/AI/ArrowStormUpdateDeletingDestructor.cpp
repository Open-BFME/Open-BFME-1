// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: ArrowStormUpdate scalar-deleting destructor at retail RVA
// 0x00257C70 (30 bytes). Its exact constructor at 0x002576E0, complete
// destructor at 0x00257940, unique factories, module name, and vtable
// 0x00CB37C0 establish the class. The destructor ILT is 0x0003E879.

class ArrowStormUpdate
{
public:
	virtual ~ArrowStormUpdate();
};

void forceArrowStormUpdateDeletingDestructor()
{
	ArrowStormUpdate value;
}
