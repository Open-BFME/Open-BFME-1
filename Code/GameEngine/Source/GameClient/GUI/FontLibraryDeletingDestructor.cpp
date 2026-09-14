// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Open-BFME5: FontLibrary scalar-deleting destructor at retail RVA
// 0x00476AA0 (30 bytes). The matched constructor at 0x0008A430 and vtable
// 0x00CF7650 establish the class identity; the complete destructor at
// 0x004762D0 deletes the linked font list and tears down the two STLport
// trees before chaining to SubsystemInterface.

class FontLibrary
{
public:
	virtual ~FontLibrary();
};

void forceFontLibraryDeletingDestructor()
{
	FontLibrary value;
}
