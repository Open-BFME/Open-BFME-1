// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the DirectInputMouse::init naked dump to clean C++.
//
// Verbatim Zero Hour Win32DIMouse.cpp: chain to the base init, open the mouse,
// then push the window cursor to the position the system already holds. Retail
// pins what ZH leaves symbolic -- m_currMouse.pos.x/y sit at this+0x4D10 and
// this+0x4D14, and ApplicationHWnd is the global at 0x012ED238.
//
// ClientToScreen and SetCursorPos are declared dllimport so the calls stay
// indirect through the import table, which is how retail reaches them.

struct POINT
{
	long x;
	long y;
};

typedef void *HWND;

extern "C" __declspec(dllimport) int __stdcall ClientToScreen(HWND, POINT *);
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int, int);

extern HWND ApplicationHWnd;								///< retail [0x012ED238]

class Mouse
{
public:
	virtual void init(void);								///< ILT thunk at 0x0000245A

protected:
	unsigned char m_unreconstructed_04[0x4D10 - 4];
	long m_currMousePosX;									///< retail this+0x4D10
	long m_currMousePosY;									///< retail this+0x4D14
};

class DirectInputMouse : public Mouse
{
public:
	virtual void init(void);

private:
	void openMouse(void);									///< ILT thunk at 0x00042A7D
};

// ?init@DirectInputMouse@@UAEXXZ
void DirectInputMouse::init(void)
{
	POINT p;

	// extending functionality from our base class
	Mouse::init();

	// open the mouse and create the direct input interfaces we need
	openMouse();

	// move the window mouse to the location we have initialized in our system
	p.x = m_currMousePosX;
	p.y = m_currMousePosY;
	ClientToScreen(ApplicationHWnd, &p);
	SetCursorPos(p.x, p.y);
}
