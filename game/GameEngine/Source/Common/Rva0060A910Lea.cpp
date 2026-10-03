// cl: /O2 /Ob0

// 0x00019010 is the incremental-link thunk for ?bfmeQueueCR@@YGXPAVBfmeSrcCR@@@Z
// at 0x0060a880 (declared and defined in game/GameEngine/Source/Common/
// BfmeConv1927.cpp). Retail passes this+8 in a stack slot and leaves ECX
// holding `this`, so the argument address must be materialised in EAX: taking
// the address of the pointer local first is what makes MSVC 7.1 give the
// pushed load EAX instead of reusing ECX. m_field stands in for the
// BfmeSrcCR the real callee reads.
class BfmeSrcCR;

void __stdcall bfmeQueueCR(BfmeSrcCR *src);

class Rva0060A910
{
	char m_lead[8];
	char m_field;

public:
	void run();
};

void Rva0060A910::run()
{
	char *field = &m_field;
	char **fieldSlot = &field;
	bfmeQueueCR(*(BfmeSrcCR **)fieldSlot);
}
