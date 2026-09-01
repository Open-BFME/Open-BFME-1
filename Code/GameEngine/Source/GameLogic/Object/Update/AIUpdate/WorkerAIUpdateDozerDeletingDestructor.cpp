// cl: /DNDEBUG /MD /EHsc
//
// ActAsDozerState is defined in WorkerAIUpdate.cpp.  The focused declaration
// keeps its compiler-generated scalar deleting destructor available as a
// standalone byte-match candidate.

class ActAsDozerState
{
public:
	virtual ~ActAsDozerState();
};

__declspec(noinline) ActAsDozerState::~ActAsDozerState() {}

void Force_ActAsDozerState_Deleting_Destructor(ActAsDozerState *state)
{
	delete state;
}
