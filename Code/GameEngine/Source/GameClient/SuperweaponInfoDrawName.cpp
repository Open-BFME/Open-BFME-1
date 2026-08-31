// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef int Color;

// BFME's DisplayString renderer stages the colors before issuing the draw.
// This TU-scoped view records the retail vtable slots used by drawName.
class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColors(Color color, Color dropColor) = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void drawAtOffsets(Int x, Int y, Int xDrop, Int yDrop) = 0;
	virtual void slot3C() = 0;
	virtual Int getWidth(Int charPos) = 0;
};

class SuperweaponInfo
{
private:
	void *m_vtable;
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
	Color m_color;

public:
	void drawName(Int x, Int y, Color color, Color dropColor);
};

void SuperweaponInfo::drawName(Int x, Int y, Color color, Color dropColor)
{
	if (color == 0)
		color = m_color;

	m_nameDisplayString->setColors(color, dropColor);
	m_nameDisplayString->drawAtOffsets(x - m_nameDisplayString->getWidth(-1), y, 1, 1);
}
