// cl: /DNDEBUG /MD
//
// Retail 0x004E9CC0: if (this) { layout = winGetLayout(); if (layout)
// { layout->destroyWindows(); delete layout; } }

class WindowLayout
{
public:
	virtual void runInit();
	virtual ~WindowLayout();
	virtual void runUpdate();
	virtual void runShutdown();
	virtual void hide();
	virtual void bringForward();
	virtual void addWindow();
	virtual void removeWindow();
	virtual void destroyWindows();
};

class GameWindow
{
public:
	WindowLayout *winGetLayout();
	void destroyLayout();
};

// ?destroyLayout@GameWindow@@QAEXXZ
void GameWindow::destroyLayout()
{
	if (this)
	{
		WindowLayout *layout = winGetLayout();
		if (layout)
		{
			layout->destroyWindows();
			delete layout;
		}
	}
}
