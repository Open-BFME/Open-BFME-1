// cl: /DNDEBUG /MD /EHsc
//
// AIDeadState scalar-deleting destructor at 0x0017FF50. Its exact constructor
// at 0x001713C0 installs vtable 0x01097EA0, whose slot-zero ILT 0x00042B04
// reaches this wrapper. The protected destructor ABI comes from the pool macro
// in AIStateMachine.h; the complete destructor tail-jumps to State::~State().

class State
{
public:
	virtual ~State();
};

class AIDeadState : public State
{
	friend void forceAIDeadStateDeletingDestructor();

protected:
	virtual ~AIDeadState();
};

void forceAIDeadStateDeletingDestructor()
{
	AIDeadState value;
}

