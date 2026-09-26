// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIQuarrelState scalar-deleting destructor at retail RVA
// 0x00180410 (30 bytes). Constructor 0x001719A0 passes the literal class name
// and installs vtable 0x01098470. Its slot zero routes through ILT 0x0001B243
// to this wrapper; slot two returns "AIQuarrelState", and slot six is the
// independently matched AIQuarrelState::update.

class AIQuarrelState
{
protected:
	virtual ~AIQuarrelState();

private:
	friend void forceAIQuarrelStateDeletingDestructor();
};

void forceAIQuarrelStateDeletingDestructor()
{
	AIQuarrelState value;
}
