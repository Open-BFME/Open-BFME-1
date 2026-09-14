// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: State scalar-deleting destructor at retail RVA 0x000A1B00
// (30 bytes). The exact State constructor at 0x000A19E0 installs vtable
// 0x01080770, whose slot zero routes through ILT 0x00049904 to this wrapper.
// The wrapper calls the complete destructor through ILT 0x00016725.

class State
{
public:
	virtual ~State();
};

void forceStateDeletingDestructor()
{
	State value;
}
