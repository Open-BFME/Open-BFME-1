// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WindowManager
{
public:
	void hideQuitMenu();
};

// Globals filled by DIR32 from retail.
extern WindowManager *g_rva012F19E8WindowManager;
extern void *g_quitMenuLayout;

// ?HideQuitMenu@@YAXXZ
void HideQuitMenu()
{
	if (g_quitMenuLayout)
		g_rva012F19E8WindowManager->hideQuitMenu();
}