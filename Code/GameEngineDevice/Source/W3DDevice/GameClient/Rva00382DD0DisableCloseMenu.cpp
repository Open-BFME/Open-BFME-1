// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef void *BfmeWindowHandle;
typedef void *BfmeMenuHandle;

extern BfmeWindowHandle Rva012ED238Global;

extern "C" __declspec(dllimport) BfmeMenuHandle __stdcall GetSystemMenu(
	BfmeWindowHandle window, int revert);
extern "C" __declspec(dllimport) unsigned int __stdcall EnableMenuItem(
	BfmeMenuHandle menu, unsigned int item, unsigned int flags);

void bfmeDisableSystemMenuClose_00382DD0()
{
	BfmeMenuHandle menu = GetSystemMenu(Rva012ED238Global, 0);
	EnableMenuItem(menu, 0xF060, 0);
}
