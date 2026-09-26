// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// (c) 2001-2003 Electronic Arts Inc.
// Readable BFME body of ?processMouseEvent@Mouse@@AAEXH@Z.
//
// The retail body is 647 bytes from 0x005A46B0 through the ret 4 at
// 0x005A4934.  Its MouseIO records begin at this+0x1110 with a 0x3c stride;
// the current and previous records are at this+0x4d10 and this+0x4d4c.
// The byte at this+0x108c is written by each active-button path, so it is
// represented explicitly here rather than silently losing that retail store.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

struct ICoord2D
{
	Int x;
	Int y;
};

enum MouseButtonState
{
	MBS_Up = 0,
	MBS_Down = 1,
	MBS_DoubleClick = 2
};

enum GameWindowMessage
{
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DOUBLE_CLICK = 7,
	GWM_LEFT_DRAG = 8,
	GWM_MIDDLE_DOWN = 9,
	GWM_MIDDLE_UP = 10,
	GWM_MIDDLE_DOUBLE_CLICK = 11,
	GWM_MIDDLE_DRAG = 12,
	GWM_RIGHT_DOWN = 13,
	GWM_RIGHT_UP = 14,
	GWM_RIGHT_DOUBLE_CLICK = 15,
	GWM_RIGHT_DRAG = 16
};

static const Int MOUSE_EVENT_NONE = 0;
static const Int MOUSE_MOVE_RELATIVE = 0;
static const Int MOUSE_MOVE_ABSOLUTE = 1;

struct MouseIO
{
	ICoord2D pos;
	UnsignedInt time;
	Int wheelPos;
	ICoord2D deltaPos;
	MouseButtonState leftState;
	Int leftEvent;
	Int leftFrame;
	MouseButtonState rightState;
	Int rightEvent;
	Int rightFrame;
	MouseButtonState middleState;
	Int middleEvent;
	Int middleFrame;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Int loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();
};

class Mouse : public SubsystemInterface
{
protected:
	void checkForDrag( void );
	void moveMouse( Int x, Int y, Int relOrAbs );

private:
	void processMouseEvent( Int index );

	char m_pad0[0x108c - 4];
	UnsignedByte m_buttonActivity;
	char m_pad1[0x1110 - 0x108d];
	MouseIO m_mouseEvents[256];
	MouseIO m_currMouse;
	MouseIO m_prevMouse;
	char m_pad2[0x4d98 - 0x4d88];
	UnsignedInt m_inputFrame;
	char m_pad3[0x4da0 - 0x4d9c];
	UnsignedByte m_inputMovesAbsolute;
};

// Local definition of the already-identified moveMouse ABI keeps the compiler
// aware that this helper preserves ecx in its compiled body. The helper's
// own retail row remains owned by Mouse.cpp; this TU only supplies its layout
// shim while compiling processMouseEvent.
struct BfmeMousePositionLayout
{
	UnsignedByte pad0[0x4d10];
	ICoord2D currPos;
	UnsignedByte pad1[0x4d88 - 0x4d18];
	Int minX;
	Int maxX;
	Int minY;
	Int maxY;
};

void Mouse::moveMouse( Int x, Int y, Int relOrAbs )
{
	BfmeMousePositionLayout *self = (BfmeMousePositionLayout *)this;

	if( relOrAbs == MOUSE_MOVE_RELATIVE )
	{
		self->currPos.x += x;
		self->currPos.y += y;
	}
	else
	{
		self->currPos.x = x;
		self->currPos.y = y;
	}

	if( self->currPos.x > self->maxX )
		self->currPos.x = self->maxX;
	else if( self->currPos.x < self->minX )
		self->currPos.x = self->minX;

	if( self->currPos.y > self->maxY )
		self->currPos.y = self->maxY;
	else if( self->currPos.y < self->minY )
		self->currPos.y = self->minY;
}

// ?checkForDrag@Mouse@@ present-unmatched
// This local body is an ABI/codegen shim for the existing retail helper route;
// the helper itself is intentionally not claimed by this conversion row.
void Mouse::checkForDrag( void )
{
	if( m_currMouse.leftState &&
			( (m_prevMouse.leftEvent == GWM_LEFT_DOWN) ||
			  (m_prevMouse.leftEvent == GWM_LEFT_DRAG) ) )
		m_currMouse.leftEvent = GWM_LEFT_DRAG;

	if( m_currMouse.rightState &&
			( (m_prevMouse.rightEvent == GWM_RIGHT_DOWN) ||
			  (m_prevMouse.rightEvent == GWM_RIGHT_DRAG) ) )
		m_currMouse.rightEvent = GWM_RIGHT_DRAG;

	if( m_currMouse.middleState &&
			( (m_prevMouse.middleEvent == GWM_MIDDLE_DOWN) ||
			  (m_prevMouse.middleEvent == GWM_MIDDLE_DRAG) ) )
		m_currMouse.middleEvent = GWM_MIDDLE_DRAG;
}

void Mouse::processMouseEvent( Int index )
{
	Int movementType;

	m_currMouse.leftEvent = MOUSE_EVENT_NONE;
	m_currMouse.rightEvent = MOUSE_EVENT_NONE;
	m_currMouse.middleEvent = MOUSE_EVENT_NONE;
	m_currMouse.wheelPos = 0;

	if( m_inputMovesAbsolute == 1 )
		movementType = MOUSE_MOVE_ABSOLUTE;
	else
		movementType = MOUSE_MOVE_RELATIVE;

	m_currMouse.time = m_mouseEvents[ index ].time;

	if( index == 0 )
		checkForDrag();

	moveMouse( m_mouseEvents[ index ].pos.x,
					 m_mouseEvents[ index ].pos.y,
					 movementType );

	m_currMouse.wheelPos += m_mouseEvents[ index ].wheelPos;

	if( m_mouseEvents[ index ].leftFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.leftState != m_mouseEvents[ index ].leftState )
		{
			if( m_mouseEvents[ index ].leftState == MBS_Down )
			{
				m_currMouse.leftEvent = GWM_LEFT_DOWN;
				m_currMouse.leftState = MBS_Down;
				m_currMouse.leftFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].leftState == MBS_DoubleClick )
			{
				m_currMouse.leftEvent = GWM_LEFT_DOUBLE_CLICK;
				m_currMouse.leftState = MBS_DoubleClick;
				m_currMouse.leftFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.leftEvent = GWM_LEFT_UP;
				m_currMouse.leftState = MBS_Up;
				m_currMouse.leftFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.leftState != MBS_Up &&
				 ( (m_prevMouse.leftEvent == GWM_LEFT_DOWN) ||
				   (m_prevMouse.leftEvent == GWM_LEFT_DRAG) ) )
	{
		m_currMouse.leftEvent = GWM_LEFT_DRAG;
	}

	if( m_mouseEvents[ index ].rightFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.rightState != m_mouseEvents[ index ].rightState )
		{
			if( m_mouseEvents[ index ].rightState == MBS_Down )
			{
				m_currMouse.rightEvent = GWM_RIGHT_DOWN;
				m_currMouse.rightState = MBS_Down;
				m_currMouse.rightFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].rightState == MBS_DoubleClick )
			{
				m_currMouse.rightEvent = GWM_RIGHT_DOUBLE_CLICK;
				m_currMouse.rightState = MBS_DoubleClick;
				m_currMouse.rightFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.rightEvent = GWM_RIGHT_UP;
				m_currMouse.rightState = MBS_Up;
				m_currMouse.rightFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.rightState != MBS_Up &&
				 ( (m_prevMouse.rightEvent == GWM_RIGHT_DOWN) ||
				   (m_prevMouse.rightEvent == GWM_RIGHT_DRAG) ) )
	{
		m_currMouse.rightEvent = GWM_RIGHT_DRAG;
	}

	if( m_mouseEvents[ index ].middleFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.middleState != m_mouseEvents[ index ].middleState )
		{
			if( m_mouseEvents[ index ].middleState == MBS_Down )
			{
				m_currMouse.middleEvent = GWM_MIDDLE_DOWN;
				m_currMouse.middleState = MBS_Down;
				m_currMouse.middleFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].middleState == MBS_DoubleClick )
			{
				m_currMouse.middleEvent = GWM_MIDDLE_DOUBLE_CLICK;
				m_currMouse.middleState = MBS_DoubleClick;
				m_currMouse.middleFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.middleEvent = GWM_MIDDLE_UP;
				m_currMouse.middleState = MBS_Up;
				m_currMouse.middleFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.middleState != MBS_Up &&
				 ( (m_prevMouse.middleEvent == GWM_MIDDLE_DOWN) ||
				   (m_prevMouse.middleEvent == GWM_MIDDLE_DRAG) ) )
	{
		m_currMouse.middleEvent = GWM_MIDDLE_DRAG;
	}

	m_currMouse.deltaPos.x = m_currMouse.pos.x - m_prevMouse.pos.x;
	m_currMouse.deltaPos.y = m_currMouse.pos.y - m_prevMouse.pos.y;
	m_prevMouse = m_currMouse;
}
