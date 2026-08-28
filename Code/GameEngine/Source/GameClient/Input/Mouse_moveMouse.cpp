// cl: /DNDEBUG /MD /EHsc
// readable body of ?moveMouse@Mouse@@: Code/GameEngine/Source/GameClient/Input/Mouse.cpp
// Open-BFME: Mouse::moveMouse, retail 0x005A4230, 129 bytes.
//
// The reference's body unchanged, and it pins six offsets on the way past:
// m_currMouse.pos is at this+0x4D10 and the clamp bounds are the four ints
// from +0x4D88, in the reference's order, min then max for x and then for y.
//
// MOUSE_MOVE_RELATIVE is 0 -- the third argument is tested rather than
// compared -- and each axis shares one store between the two clamp arms, which
// is the if/else-if the reference writes rather than two separate tests.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MOUSE_MOVE_RELATIVE = 0, MOUSE_MOVE_ABSOLUTE };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Mouse.h
struct MouseIO
{
	ICoord2D pos;
};

class Mouse
{
protected:
	void moveMouse(Int x, Int y, Int relOrAbs);

	char m_slice_padA[0x4D10];			// retail this+0x00 .. +0x4D0F, untouched
	MouseIO m_currMouse;				// this+0x4D10
	char m_slice_padB[0x4D88 - 0x4D18];		// this+0x4D18 .. +0x4D87, untouched
	Int m_minX;					// this+0x4D88
	Int m_maxX;					// this+0x4D8C
	Int m_minY;					// this+0x4D90
	Int m_maxY;					// this+0x4D94
};

void Mouse::moveMouse( Int x, Int y, Int relOrAbs )
{

	if( relOrAbs == MOUSE_MOVE_RELATIVE )
	{
		m_currMouse.pos.x += x;
		m_currMouse.pos.y += y;
	}
	else
	{
		m_currMouse.pos.x = x;
		m_currMouse.pos.y = y;
	}

	if( m_currMouse.pos.x > m_maxX )
		m_currMouse.pos.x = m_maxX;
	else if( m_currMouse.pos.x < m_minX )
		m_currMouse.pos.x = m_minX;

	if( m_currMouse.pos.y > m_maxY )
		m_currMouse.pos.y = m_maxY;
	else if( m_currMouse.pos.y < m_minY )
		m_currMouse.pos.y = m_minY;

}  // end moveMouse
