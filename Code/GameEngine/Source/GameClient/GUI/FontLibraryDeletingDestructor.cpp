// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Open-BFME5: FontLibrary scalar-deleting destructor at retail RVA
// 0x00476AA0 (30 bytes). The matched BFMERetailFontLibrary constructor at
// 0x004769A0 and FontLibrary vtable 0x010F7650 establish the base-class
// identity; the complete destructor at 0x004762D0 deletes the linked font
// list and tears down the two STLport trees before chaining to
// SubsystemInterface.

class FontLibrary
{
public:
	virtual ~FontLibrary();
};

void forceFontLibraryDeletingDestructor()
{
	FontLibrary value;
}
