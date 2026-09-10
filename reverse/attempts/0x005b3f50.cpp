// ?translateGameMessage@HotKeyTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.99 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

union GameMessageArgumentType
{
	Int integer;
	Int pixel[2];
};

class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_KEY_UP = 22
	};

	Type getType() const
	{
		return (Type)m_type;
	}

	const GameMessageArgumentType *getArgument(Int index) const;

private:
	char m_pad[0x10];
	Int m_type;
};

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class Keyboard
{
public:
	WideChar getPrintableKey(UnsignedByte key, Int state);
};

#define TheKeyboard (*(Keyboard **)0x012F4C50)

template <typename T>
class StringBase
{
friend class UnicodeString;
friend class AsciiString;

public:
	StringBase() : m_data(0) {}
	void set(const T *text, Int length);

private:
	~StringBase();
	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	~UnicodeString() {}
	void set(const WideChar *text, Int length);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}
	void translate(const UnicodeString &text);
};

class BfmeTransitionMD
{
public:
	Bool dispatch(AsciiString *key, Bool shiftOnly);
};

#define g_bfmeTransitionMD (*(BfmeTransitionMD **)0x012F4C7C)

class HotKeyTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

GameMessageDisposition HotKeyTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	GameMessage::Type t = msg->getType();

	if (t == GameMessage::MSG_RAW_KEY_UP)
	{
		Int keyState = msg->getArgument(1)->integer;
		Int newModState = 0;
		Bool shiftOnly = false;

		if (keyState & 0x430)
		{
			newModState = 0x10;
			shiftOnly = true;
		}

		if (keyState & 0x0C)
		{
			newModState |= 0x04;
			shiftOnly = false;
		}

		if (keyState & 0xC0)
		{
			newModState |= 0x40;
			shiftOnly = false;
		}

		if (newModState != 0)
		{
			if (!shiftOnly)
				return disp;
		}

		WideChar key = TheKeyboard->getPrintableKey(
			(UnsignedByte)msg->getArgument(0)->integer, 0);
		UnicodeString uKey;
		((StringBase<WideChar> *)&uKey)->set(&key, sizeof(key) / sizeof(key));
		AsciiString aKey;
		aKey.translate(uKey);
		if (g_bfmeTransitionMD && g_bfmeTransitionMD->dispatch(&aKey, shiftOnly))
			disp = DESTROY_MESSAGE;
	}

	return disp;
}
