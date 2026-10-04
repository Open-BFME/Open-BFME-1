// cl: /O2 /MD
// 5-byte ILT at 0x000309CC; its sole target is the W3DSmudgeManager
// ReleaseResources body at 0x00722190, pinned as the shim member below.

class FontLibraryDeleteAllFontsShim
{
public:
	void deleteAllFonts();
};

void j_000309cc()
{
	typedef void (FontLibraryDeleteAllFontsShim::*Call)();
	union { void (*fn)(); Call call; } u;
	u.call = &FontLibraryDeleteAllFontsShim::deleteAllFonts;
	u.fn();
}