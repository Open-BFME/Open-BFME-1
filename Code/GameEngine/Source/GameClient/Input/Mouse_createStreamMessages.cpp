// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable BFME body of ?createStreamMessages@Mouse@@UAEXXZ:
// Code/GameEngine/Source/GameClient/Input/Mouse.cpp
// Full1090 code bytes through5A50A1 plus2-byte alignment and three
// four-entry switch tables through5A50D3. Mouse/W3DMouse slot11 via198FD.

typedef int Int;
typedef unsigned int UnsignedInt;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameMessage
{
public:
	void appendPixelArgument(const ICoord2D &position);
	void appendIntegerArgument(Int value);
};

class MessageStream
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual GameMessage *appendMessage(Int type);
};

extern MessageStream *TheMessageStream;

class Keyboard
{
public:
	// BFME's Keyboard stores the modifier mask at +0x08.
	char m_pad0[8];
	unsigned short m_modifiers;
};

extern Keyboard *TheKeyboard;

#define getModifierFlags() m_modifiers

// The resolver pin maps this real Mouse::processMouseEvent declaration to its
// existing retail body; the linker uses its incremental-link thunk at 0x0040673A.

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

struct MouseIO
{
	ICoord2D pos;
	UnsignedInt time;
	Int wheelPos;
	ICoord2D deltaPos;
	Int leftState;
	Int leftEvent;
	Int leftFrame;
	Int rightState;
	Int rightEvent;
	Int rightFrame;
	Int middleState;
	Int middleEvent;
	Int middleFrame;
};

class Mouse
{
public:
	virtual void createStreamMessages();

private:
	void processMouseEvent(Int index);

	char m_pad0[0x4d10 - 4];
	MouseIO m_currMouse;
	char m_pad1[0x4e00 - 0x4d10 - sizeof(MouseIO)];
	Int m_eventsThisFrame;
	// These two BFME slots age the pending left/right click notifications.
	Int m_leftClickAge;
	Int m_rightClickAge;
};

void Mouse::createStreamMessages()
{
	if (TheMessageStream == 0)
		return;

	GameMessage *msg;

	msg = TheMessageStream->appendMessage(3);
	msg->appendPixelArgument(m_currMouse.pos);
	msg->appendIntegerArgument(TheKeyboard->getModifierFlags());

	for (Int i = 0; i < m_eventsThisFrame; ++i)
	{
		processMouseEvent(i);

		switch (m_currMouse.leftEvent)
		{
		case GWM_LEFT_DOWN:
			msg = TheMessageStream->appendMessage(4);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			m_leftClickAge = 0;
			break;

		case GWM_LEFT_DOUBLE_CLICK:
			msg = TheMessageStream->appendMessage(5);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			break;

		case GWM_LEFT_UP:
			msg = TheMessageStream->appendMessage(6);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			m_leftClickAge = -1;
			break;

		case GWM_LEFT_DRAG:
			msg = TheMessageStream->appendMessage(8);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendPixelArgument(m_currMouse.deltaPos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			break;
		}

		switch (m_currMouse.middleEvent)
		{
		case GWM_MIDDLE_DOWN:
			msg = TheMessageStream->appendMessage(10);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			break;

		case GWM_MIDDLE_DOUBLE_CLICK:
			msg = TheMessageStream->appendMessage(11);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			break;

		case GWM_MIDDLE_UP:
			msg = TheMessageStream->appendMessage(12);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			break;

		case GWM_MIDDLE_DRAG:
			msg = TheMessageStream->appendMessage(13);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendPixelArgument(m_currMouse.deltaPos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			break;
		}

		switch (m_currMouse.rightEvent)
		{
		case GWM_RIGHT_DOWN:
			msg = TheMessageStream->appendMessage(14);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			m_rightClickAge = 0;
			break;

		case GWM_RIGHT_DOUBLE_CLICK:
			msg = TheMessageStream->appendMessage(15);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			break;

		case GWM_RIGHT_UP:
			msg = TheMessageStream->appendMessage(16);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			msg->appendIntegerArgument(m_currMouse.time);
			m_rightClickAge = -1;
			break;

		case GWM_RIGHT_DRAG:
			msg = TheMessageStream->appendMessage(18);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendPixelArgument(m_currMouse.deltaPos);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
			break;
		}

		if (m_currMouse.wheelPos != 0)
		{
			msg = TheMessageStream->appendMessage(19);
			msg->appendPixelArgument(m_currMouse.pos);
			msg->appendIntegerArgument(m_currMouse.wheelPos / 120);
			msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
		}
	}

	if (m_leftClickAge != -1 && m_leftClickAge < 5)
		++m_leftClickAge;
	if (m_rightClickAge != -1 && m_rightClickAge < 5)
		++m_rightClickAge;

	if (m_leftClickAge >= 5)
	{
		msg = TheMessageStream->appendMessage(9);
		msg->appendPixelArgument(m_currMouse.pos);
		msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
		msg->appendIntegerArgument(m_currMouse.time);
		m_leftClickAge = -1;
	}

	if (m_rightClickAge >= 5)
	{
		msg = TheMessageStream->appendMessage(17);
		msg->appendPixelArgument(m_currMouse.pos);
		msg->appendIntegerArgument(TheKeyboard->getModifierFlags());
		msg->appendIntegerArgument(m_currMouse.time);
		m_rightClickAge = -1;
	}
}

#undef getModifierFlags
