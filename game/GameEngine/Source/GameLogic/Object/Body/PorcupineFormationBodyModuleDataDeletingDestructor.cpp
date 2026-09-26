// cl: /O2

// The exact constructor at 0x00214470 identifies this 30-byte scalar-deleting
// destructor as the PorcupineFormationBodyModuleModuleData vtable slot.
class PorcupineFormationBodyModuleModuleData
{
public:
	virtual ~PorcupineFormationBodyModuleModuleData();
};

void forcePorcupineFormationBodyModuleModuleDataDeletingDestructor()
{
	PorcupineFormationBodyModuleModuleData value;
}
