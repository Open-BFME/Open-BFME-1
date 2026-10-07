// cl: /O2 /Ob0
//
// GameWindow::winGetCursorPosition, retail 0x004781A0 (31 bytes). Identity:
// symbols.csv pins the name to ILT 0x0003FB11, which jumps here, and the body
// is the Zero Hour GameWindow.cpp accessor with BFME's cursor fields at
// +0x24/+0x28.

typedef int Int;

class GameWindow
{
public:
	Int winGetCursorPosition(Int *x, Int *y);

private:
	char pad[0x24];
	Int m_cursorX;
	Int m_cursorY;
};

Int GameWindow::winGetCursorPosition(Int *x, Int *y)
{
	if (x)
		*x = m_cursorX;
	if (y)
		*y = m_cursorY;
	return 0;
}
