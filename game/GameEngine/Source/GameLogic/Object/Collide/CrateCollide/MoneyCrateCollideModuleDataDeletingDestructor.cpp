// cl: /DNDEBUG /MD /EHsc

// Retail @0x00126F90: MoneyCrateCollideModuleData scalar-deleting
// destructor.  The named complete destructor is matched at 0x00125E40;
// this declaration gives MSVC the authentic class name while emitting the
// small retail wrapper.
//
// The 0x00127020 friend_newModuleData factory allocates this exact type, and
// its companion TU installs the dedicated vtable at 0x0108EAA0.  Slot zero's
// ILT 0x00027A39 routes to this wrapper.  The complete-destructor call is ILT
// 0x0002BB2A, which jumps to 0x00126FC0 and the matched destructor body.
class MoneyCrateCollideModuleData
{
public:
	virtual ~MoneyCrateCollideModuleData();
};

void forceMoneyCrateCollideModuleDataDeletingDestructor()
{
	MoneyCrateCollideModuleData value;
}
