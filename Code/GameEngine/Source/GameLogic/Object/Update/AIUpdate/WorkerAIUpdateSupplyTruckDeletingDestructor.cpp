// cl: /DNDEBUG /MD /EHsc
//
// ActAsSupplyTruckState is defined in WorkerAIUpdate.cpp.  This focused
// declaration emits its compiler-generated scalar deleting destructor without
// pulling the full update module into the byte-match translation unit.

class ActAsSupplyTruckState
{
public:
	virtual ~ActAsSupplyTruckState();
};

__declspec(noinline) ActAsSupplyTruckState::~ActAsSupplyTruckState() {}

void Force_ActAsSupplyTruckState_Deleting_Destructor(ActAsSupplyTruckState *state)
{
	delete state;
}
