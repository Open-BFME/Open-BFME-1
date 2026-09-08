// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail RVA 0x0058DA50, 287 bytes.  The generated family labels this entry as
// a free function, but the first live instruction consumes ECX and the body
// reads a byte at this+0x1a0 and a window pointer at this+0x1a4.  No named
// caller or vtable owner has been recovered, so the receiver remains an
// address-derived owner.  The calls below retain the retail ILT boundaries
// and only name the APIs whose receiver, argument widths, and return ABI are
// independently established by their callers and bodies.

typedef bool Bool;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	~StringBase();

	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	bool isNotEmpty() const
	{
		return m_data != 0 && m_data->length != 0;
	}
};

class GameWindow;
class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class HotKeyManager
{
public:
	AsciiString searchHotKey(const AsciiString &label);
	void addHotKey(GameWindow *window, const AsciiString &key, Bool commandKey);
};

class GameWindow
{
public:
	int winEnable(Bool enable);
	int winHide(Bool hide);
};

extern ControlBar *TheControlBar;

// The one anonymous helper below is reached through an existing generated ILT;
// its concrete receiver and return type are recovered at the call site.
extern void j_00045949();

// 0x00564DE0 is a proven plain __cdecl callback body.  The ECX value left by
// the preceding window call is immaterial to that ABI, so this is deliberately
// not expressed as a GameWindow member call.
extern void j_0003e234();

// The retail data slot is independently identified by the GameClient global
// and by the two target loads.  Keep this TU-local until a canonical data
// binding for the exact COFF global is proven.
#define Rva0058DA50HotKeyManager (*(HotKeyManager **)0x012F4C7C)

// The body at RVA 0x0049B010 is called with only the CommandButton receiver
// in ECX and returns an AsciiString reference in EAX.  __fastcall expresses
// exactly that raw register ABI for this zero-stack-argument thunk without
// assigning the anonymous body a new C++ owner.
typedef const AsciiString &(__fastcall *GetCommandLabelCall)(const CommandButton *);

class Rva0058DA50Owner
{
public:
	void update();

private:
	unsigned char m_unmodelled_000[0x1a0];
	unsigned char m_initialized;
	unsigned char m_padding_1a1[3];
	GameWindow *m_window;
};

void Rva0058DA50Owner::update()
{
	if (m_initialized)
		return;

	if (m_window != 0)
	{
		if (Rva0058DA50HotKeyManager != 0)
		{
			static AsciiString selectAllHeroes("NonCommand_SelectAllHeroes");

			const CommandButton *button =
				TheControlBar->findCommandButton(selectAllHeroes);

			if (button != 0)
			{
				const AsciiString &label =
					((GetCommandLabelCall)j_00045949)(button);

				AsciiString hotKey =
					Rva0058DA50HotKeyManager->searchHotKey(label);

				if (hotKey.isNotEmpty())
				{
					Rva0058DA50HotKeyManager->addHotKey(m_window, hotKey, true);
				}
			}
		}

		m_window->winEnable(true);

		m_window->winHide(false);
	}

	j_0003e234();
	m_initialized = 1;
}
