// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Vtable 0x01120468 dispatches this body at slot 12. The GameClient layout
// witness places m_drawableList at +0x10, after the inherited +0x0c prefix.
class Drawable;

class GameClient
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
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Drawable *firstDrawable();

private:
	char m_inheritedLayout[ 0x0c ];
	Drawable *m_drawableList;
};

Drawable *GameClient::firstDrawable()
{
	return m_drawableList;
}
