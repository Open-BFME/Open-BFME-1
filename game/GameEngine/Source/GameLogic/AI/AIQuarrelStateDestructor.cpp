// cl: /O2 /Ob0
//
// Open-BFME: AIQuarrelState complete destructor at retail RVA 0x00180440
// (5 bytes). The scalar-deleting wrapper 0x00180410 calls it through ILT
// 0x000317A0; the body is a bare jmp to ILT 0x00016725, which routes to the
// State destructor 0x000A1B30: an empty derived destructor tail-calling its
// base.

class State
{
public:
	virtual ~State();

private:
	unsigned char m_stateStorage[0x3c];
};

class __declspec(novtable) AIQuarrelState : public State
{
public:
	virtual ~AIQuarrelState();
};

AIQuarrelState::~AIQuarrelState()
{
}
