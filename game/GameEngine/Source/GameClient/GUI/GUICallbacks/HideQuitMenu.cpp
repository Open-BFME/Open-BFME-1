// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WindowManager
{
public:
	void hideQuitMenu();
};

// Globals filled by DIR32 from retail.
extern WindowManager *g_rva012F19E8WindowManager;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;

// ?HideQuitMenu@@YAXXZ
void HideQuitMenu()
{
	if (reinterpret_cast<void * &>(g_obj12F4AD4))
		g_rva012F19E8WindowManager->hideQuitMenu();
}