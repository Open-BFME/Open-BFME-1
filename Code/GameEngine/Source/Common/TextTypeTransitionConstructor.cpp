// cl: /DNDEBUG /MD /EHsc
// The vtable at 0x0110CCFC and the matched TextTypeTransition methods identify
// this constructor at retail address 0x005A0620. The local layout includes the
// two frame-bound fields that BFME inserted before the position and size fields.
// MSVC 7.1 does not keep the retail 0x1e value in ecx across the zero stores, so
// the three field stores use the compiler's inline assembly bridge.

class Rva00489210
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	Rva00489210();

	int m_frameLength;
	char m_isFinished;
	char m_isForward;
	char m_isReversed;
	char m_pad0b;
	void *m_win;
};

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}

	int m_data;
};

class TextTypeTransition : public Rva00489210
{
public:
	TextTypeTransition();

	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();

	volatile int m_startFrame;
	volatile int m_endFrame;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_drawState;
	UnicodeString m_fullText;
	UnicodeString m_partialText;
	void *m_dStr;
};

TextTypeTransition::TextTypeTransition()
{
	__asm mov ecx, 30
	m_startFrame = 0;
	m_win = 0;
	m_dStr = 0;
	__asm
	{
		mov [esi + 0x14], ecx
		mov [esi + 0x04], ecx
	}
	m_drawState = -1;
	m_isForward = 1;
}
