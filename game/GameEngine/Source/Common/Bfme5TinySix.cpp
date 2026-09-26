// Four tiny ones: a bit read out of a byte, an inequality, a scaled difference of two floats and an
// unsigned comparison against a singleton.
//
// The bit test stays in the byte register only if every step is written on a
// byte variable; promoted to int it works in eax and grows three bytes. The
// comparison puts our own stamp in the register and the singleton's in
// memory, which is the order the operands are written in.

class Gen_001C5BE0
{
public:
	unsigned char bfmeIsClear(void) const;

private:
	int m_bfmeHead[105];					// +0x000
	unsigned char m_bfmeBits;				// +0x1A4
};

// ?bfmeIsClear@Gen_001C5BE0@@QBEEXZ
unsigned char Gen_001C5BE0::bfmeIsClear(void) const
{
	unsigned char bits = m_bfmeBits;

	bits >>= 4;
	bits = ~bits;
	bits &= 1;

	return bits;
}

class Gen_001DD250
{
public:
	unsigned char bfmeDiffers(int value) const;

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeValue;					// +0x08
};

// ?bfmeDiffers@Gen_001DD250@@QBEEH@Z
unsigned char Gen_001DD250::bfmeDiffers(int value) const
{
	return value != m_bfmeValue;
}

extern float g_bfmeScaleBK;					// retail 0x01075C70

// ?bfmeScaled@@YGMMMMM@Z
float __stdcall bfmeScaled(float first, float second, float third, float fourth)
{
	return (fourth - second) * g_bfmeScaleBK;
}

class BfmeClockBK
{
public:
	int m_bfmeHead[15];					// +0x00
	unsigned int m_bfmeStamp;				// +0x3C
};

extern BfmeClockBK *g_bfmeClockBK;				// retail 0x012F0898

class Gen_001E1A10
{
public:
	int bfmeIsLater(void) const;

private:
	int m_bfmeHead[20];					// +0x00
	unsigned int m_bfmeStamp;				// +0x50
};

// ?bfmeIsLater@Gen_001E1A10@@QBEHXZ
int Gen_001E1A10::bfmeIsLater(void) const
{
	return m_bfmeStamp > g_bfmeClockBK->m_bfmeStamp;
}
