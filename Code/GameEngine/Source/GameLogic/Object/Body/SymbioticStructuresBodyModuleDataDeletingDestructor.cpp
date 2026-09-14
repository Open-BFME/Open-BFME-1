// cl: /DNDEBUG /MD /EHsc
//
// ModuleFactory registration and the matched constructor at 0x00128D20
// identify SymbioticStructuresBodyModuleData. Its dedicated vtable
// 0x0108EC78 routes slot zero through ILT 0x00046236 to wrapper 0x00129530;
// that wrapper calls complete-destructor ILT 0x0002473A.

class SymbioticStructuresBodyModuleData
{
public:
	virtual ~SymbioticStructuresBodyModuleData();
};

void forceSymbioticStructuresBodyModuleDataDeletingDestructor()
{
	SymbioticStructuresBodyModuleData value;
}
