// The call at 0x00027B01 is the 5-byte ILT thunk that jumps to the body at
// 0x0019A260, which the ledger owns as
// ?cleanup@Rva0019A260State@@QAEXPAX@Z (game/GameEngine/Source/Common/
// Rva0019A260Cleanup.cpp): one thiscall pointer argument, matching the call
// site exactly. Declared here only, so the reference links to that definition.
class Rva0019A260State
{
public:
	void cleanup(void *what);

private:
	char m_bfmePad[0x18];
};

class BfmeThingCMC
{
public:
	int bfmeAddCMC(void *what);
	unsigned char m_bfmeHead[0x28];
	int m_bfmeCount;
	Rva0019A260State m_bfmeItems[0x20];
};

int BfmeThingCMC::bfmeAddCMC(void *what)
{
	int n = m_bfmeCount;
	if (n < 0x20)
	{
		m_bfmeCount = n + 1;
		m_bfmeItems[n].cleanup(what);
		return n;
	}
	return -1;
}