// cl: /DNDEBUG /MD /EHsc

// Retail @0x00123140: AnimalAIUpdateModuleData scalar-deleting destructor.
// The named complete destructor is recovered at 0x0027E4E0; declaring the
// authentic class here and forcing a local instance lets MSVC emit the small
// wrapper while the existing TU owns the complete body.
//
// The factory at 0x00116A10 returns this exact module-data type and its
// companion TU installs the pinned AnimalAIUpdateModuleData vtable at
// 0x010899F0.  This is the class evidence for the wrapper; the shared module
// constructor body is ICF-folded with neighboring ModuleData constructors.
class AnimalAIUpdateModuleData
{
public:
	virtual ~AnimalAIUpdateModuleData();
};

void forceAnimalAIUpdateModuleDataDeletingDestructor()
{
	AnimalAIUpdateModuleData value;
}
