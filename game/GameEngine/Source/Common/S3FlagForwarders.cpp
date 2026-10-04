// Two retained flag-then-forward wrappers.
// Native dynamic-audio overrides are recovered in Audio/DynamicAudioEventInfo.cpp.

typedef unsigned int UnsignedInt;


class Gen_00088B60
{
public:
	void bfmeClearForward(void);
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x00031FCF

	char m_bfmeHead[0x44];
	UnsignedInt m_bfmeFlags;				// +0x44
};






// ?bfmeClearForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeClearForward(void)
{
	m_bfmeFlags &= ~0x10U;

	bfmeNext();
}

// ?bfmeForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeForward(void)
{
	m_bfmeFlags |= 0x10;

	bfmeNext();
}
