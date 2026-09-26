// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail 0x0046ED80, 108 bytes. The callback maps the three background
// commands used by the scripted UI to WindowManager operations.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class WindowManager
{
public:
	void bfme_hideBackground(bool hide);
	void bfme_showBackground(int kind);
};

extern WindowManager *g_theWindowManager;

// ?Rva0046ED80@@YAXPBD@Z
void Rva0046ED80(const char *command)
{
	if (!command)
		return;

	int (__cdecl *compare)(const char *, const char *) = _strcmpi;
	if (compare(command, "fadein") == 0)
	{
		g_theWindowManager->bfme_showBackground(1);
		return;
	}

	if (compare(command, "fadeout") == 0)
	{
		g_theWindowManager->bfme_hideBackground(false);
		return;
	}

	if (compare(command, "off") == 0)
		g_theWindowManager->bfme_hideBackground(true);
}
