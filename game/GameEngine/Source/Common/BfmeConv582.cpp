// Callees (tools/callees.py 0x6BC330 38): ILT 0x5501 -> 0x005A4BF0
// Rva005A4BF0Mouse::clearTooltipIfHidden, ILT 0x4A1EC -> 0x006BC190
// Win32Mouse::setCursor (direct, non-virtual call with the cursor at +0x4DA8).
class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0
	};
};

class Win32Mouse
{
public:
	virtual void setCursor(Mouse::MouseCursor cursor);
};

class Rva005A4BF0Mouse
{
public:
	void clearTooltipIfHidden(unsigned char flag, unsigned char *state);
};

class BfmeThingCDD
{
public:
	void bfmeGoCDD(void *one, void *two);
	unsigned char m_bfmeHead[0x4da8];
	Mouse::MouseCursor m_bfmeVal;
};

void BfmeThingCDD::bfmeGoCDD(void *one, void *two)
{
	reinterpret_cast<Rva005A4BF0Mouse *>(this)->clearTooltipIfHidden((unsigned char)(unsigned long)one, (unsigned char *)two);
	reinterpret_cast<Win32Mouse *>(this)->Win32Mouse::setCursor(m_bfmeVal);
}
