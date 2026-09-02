// ?forward@Gen_00730e20@@QAEXUGen_00730e20_Value@@I@Z
// partial score=0.75 date=2026-09-02
// BFME retail 0x00730E20: guarded forwarding of a 12-byte value and one dword.

struct Gen_00730e20_Value
{
	volatile unsigned a;
	volatile unsigned b;
	volatile unsigned c;
};

class Gen_00730e20_Target
{
public:
	void forward(Gen_00730e20_Value value, unsigned tail);
};

class Gen_00730e20
{
public:
	void forward(Gen_00730e20_Value value, unsigned tail);

private:
	unsigned char m_pad[0x10];
	Gen_00730e20_Target * volatile m_target;
};

void Gen_00730e20::forward(Gen_00730e20_Value value, unsigned tail)
{
	if (m_target)
		m_target->forward(value, tail);
}
