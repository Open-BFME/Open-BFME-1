// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WindowManager
{
public:
	void hideQuitMenu();
};

// Globals filled by DIR32 from retail.
extern WindowManager *g_theWindowManager;
extern void *g_quitMenuLayout;

// ?HideQuitMenu@@YAXXZ
void HideQuitMenu()
{
	if (g_quitMenuLayout)
		g_theWindowManager->hideQuitMenu();
}