struct BfmeSubCCA
{
	void bfmeNotifyCCA();
	unsigned char m_bfmeHead[0x12c];
	unsigned int m_bfmeFlags;
};

struct StateMachine
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubCCA *m_owner;
};

class BfmeThingCCA
{
public:
	void onExit(void *spare);
	unsigned char m_bfmeHead[0x1c];
	StateMachine *m_machine;
};

void BfmeThingCCA::onExit(void *spare)
{
	BfmeSubCCA *sub = m_machine->m_owner;
	if (sub->m_bfmeFlags & 0x200000u)
	{
		sub->m_bfmeFlags &= ~0x200000u;
		sub->bfmeNotifyCCA();
	}
}
