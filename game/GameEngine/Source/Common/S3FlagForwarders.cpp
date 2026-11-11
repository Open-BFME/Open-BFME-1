// Two retained flag-then-forward wrappers.
// Native dynamic-audio overrides are recovered in Audio/DynamicAudioEventInfo.cpp.

typedef unsigned int UnsignedInt;


class MapObject
{
public:
	void ambientAudio00088480();
};

class Gen_00088B60
{
public:
	void bfmeClearForward(void);
	void bfmeForward(void);

private:
	char m_bfmeHead[0x44];
	UnsignedInt m_bfmeFlags;				// +0x44
};






// ?bfmeClearForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeClearForward(void)
{
	m_bfmeFlags &= ~0x10U;

	reinterpret_cast<MapObject *>(this)->ambientAudio00088480();
}

// ?bfmeForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeForward(void)
{
	m_bfmeFlags |= 0x10;

	reinterpret_cast<MapObject *>(this)->ambientAudio00088480();
}
