// cl: /DNDEBUG /MD /EHsc

// Retail @0x00123A40: AssaultTransportAIUpdateModuleData
// scalar-deleting destructor.  The named complete destructor is matched at
// 0x0027E4E0 (the shared ModuleData body); this declaration gives MSVC the
// authentic class name while emitting the retail wrapper shape.
//
// The 0x00118870 friend_newModuleData factory allocates this exact type, and
// its companion TU installs the dedicated vtable at 0x01089CC0.  Its slot-zero
// ILT 0x000218AF routes to this wrapper.  The wrapper's complete-destructor
// call is the ILT at 0x000235A1, which jumps through 0x00123A70 and the shared
// 0x00029D02 thunk to the matched body at 0x0027E4E0.
class AssaultTransportAIUpdateModuleData
{
public:
	virtual ~AssaultTransportAIUpdateModuleData();
};

void forceAssaultTransportAIUpdateModuleDataDeletingDestructor()
{
	AssaultTransportAIUpdateModuleData value;
}
