// cl: /DNDEBUG /MD /EHsc

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0
	};

	virtual void setCursor(MouseCursor cursor);
};

extern "C" __declspec(dllimport) void *__stdcall SetCursor(void *cursor);
extern "C" void *g_cursorResources[];

class Win32Mouse
{
public:
	virtual void setCursor(Mouse::MouseCursor cursor);
	bool isCursorVisible();

private:
	char m_fields[0x4da8 - 4];
	Mouse::MouseCursor m_currentCursor;
	char m_win32Fields[0x1070];
	Mouse::MouseCursor m_currentWin32Cursor;
	int m_directionFrame;
	bool m_lostFocus;
};

void Win32Mouse::setCursor(Mouse::MouseCursor cursor)
{
	reinterpret_cast<Mouse *>(this)->Mouse::setCursor(cursor);

	if (m_lostFocus)
		return;

	if (cursor != Mouse::NONE && isCursorVisible())
		SetCursor(g_cursorResources[m_directionFrame + cursor * 8]);
	else
		SetCursor(0);

	m_currentCursor = cursor;
	m_currentWin32Cursor = cursor;
}
