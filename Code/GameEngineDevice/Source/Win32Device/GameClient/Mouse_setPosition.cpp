// cl: /DNDEBUG /MD /EHsc
// readable body of ?setPosition@Mouse@@: Code/GameEngine/Source/GameClient/Input/Mouse.cpp

// Mouse::setPosition, retail 0x005A4500. Two stores and nothing else: the
// current mouse position is the pair of dwords at +0x4D10 and +0x4D14, a long
// way into a class whose front this file says nothing about.

typedef int Int;

class Mouse
{
public:
	virtual void setPosition( Int x, Int y );

private:
	unsigned char m_unmodelled_00[ 0x4D10 - 4 ];
	Int m_currMouseX;						// +0x4D10
	Int m_currMouseY;						// +0x4D14
};

// ?setPosition@Mouse@@UAEXHH@Z
void Mouse::setPosition( Int x, Int y )
{
	m_currMouseX = x;
	m_currMouseY = y;
}
