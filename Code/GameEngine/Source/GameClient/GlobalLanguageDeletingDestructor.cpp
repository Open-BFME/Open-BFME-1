// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Open-BFME: GlobalLanguage scalar-deleting destructor at retail RVA
// 0x0043A4B0 (30 bytes).  The exact constructor at 0x00439E70 installs the
// GlobalLanguage vtable 0x010F4124, and the matched complete virtual
// destructor at 0x0043A130 owns the subsystem's language and font state.

class GlobalLanguage
{
public:
	virtual ~GlobalLanguage();
};

void forceGlobalLanguageDeletingDestructor()
{
	GlobalLanguage value;
}
