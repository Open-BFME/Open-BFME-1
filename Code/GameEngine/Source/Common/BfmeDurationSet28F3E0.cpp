// Retail x87 codegen exception: ordinary cast emits _ftol; /QIfist emits
// 64-bit fistp and an extra stack slot. Plain/reused/volatile float shapes
// did not reproduce retail. This helper preserves retail 32-bit fistp and
// ambient rounding mode; the surrounding algorithm remains C++.
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

class Rva0037C600Callback
{
public:
	void invoke37C600(void);
};

struct BfmeDeadlineSource
{
	char m_bfmeFields[0x74];
	int m_bfmeValue;
};

class Gen_0028F3E0
{
public:
	void bfmeSet(int value, float seconds, BfmeDeadlineSource *source);

private:
	__forceinline long bfmeFloatToLong(float f)
	{
		long i;
		__asm
		{
			fld [f]
			fistp [i]
		}
		return i;
	}

	char m_bfmeFields[0x8C];
	Rva0037C600Callback *m_pendingCallback;
	char m_bfmeGap[0x10];
	int m_bfmeValue;
	int m_bfmeFrames;
	int m_bfmeSourceValue;
};

// ?bfmeSet@Gen_0028F3E0@@QAEXHMPAUBfmeDeadlineSource@@@Z
void Gen_0028F3E0::bfmeSet(int value, float seconds, BfmeDeadlineSource *source)
{
	if (seconds <= 0.0f)
		return;

	m_bfmeValue = value;
	m_bfmeFrames = (int)bfmeFloatToLong(
		(float)ceil((double)(seconds * 5.0f)));
	m_bfmeSourceValue = source != 0 ? source->m_bfmeValue : 0;

	if (m_pendingCallback != 0)
	{
		m_pendingCallback->invoke37C600();
		m_pendingCallback = 0;
	}
}
