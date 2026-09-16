// ?bfmeWrapFFF@BfmeThingFFF@@QAEXPAX@Z
// partial score=0.6 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x0035BB70. The thunk at ILT 0x00016C3E names the callee
// BfmeThingFFF::bfmeStepFFF, and the receiver reaching that call is this
// body's own, so the wrapper belongs to the same class.

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeSubFFF
{
	int m_bfmeSlotFFF;
};

class BfmeThingFFF
{
public:
	void bfmeWrapFFF(void *payload);
	void bfmeStepFFF(BfmeSubFFF *sub, void *payload);

	int m_bfmeHeadFFF;
	BfmeSubFFF m_bfmeSubFFF;
};

void BfmeThingFFF::bfmeWrapFFF(void *payload)
{
	if (this != 0)
	{
		_WriteBarrier();

		void *inner = payload;
		BfmeSubFFF *sub = &m_bfmeSubFFF;

		bfmeStepFFF(sub, inner);
		return;
	}

	_ReadWriteBarrier();

	void *inner = payload;
	BfmeSubFFF *sub = 0;

	bfmeStepFFF(sub, inner);
}
