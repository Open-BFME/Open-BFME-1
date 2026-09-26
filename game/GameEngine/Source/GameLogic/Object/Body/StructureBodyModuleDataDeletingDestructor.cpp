// cl: /DNDEBUG /MD /EHsc
//
// The shipped class declaration leaves StructureBodyModuleData's implicit
// virtual destructor public. Constructor 0x001293C0 installs vtable
// 0x0108ED20; slot-zero ILT 0x00046C90 reaches wrapper 0x00129460, which
// calls complete-destructor ILT 0x0000A781.

class StructureBodyModuleData
{
public:
	virtual ~StructureBodyModuleData();
};

void forceStructureBodyModuleDataDeletingDestructor()
{
	StructureBodyModuleData value;
}
