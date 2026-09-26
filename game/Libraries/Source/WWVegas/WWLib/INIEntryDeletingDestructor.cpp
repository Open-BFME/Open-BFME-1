// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: INIEntry scalar-deleting destructor at retail
// 0x009E35B0 (30 bytes).  The matched INIEntry constructor at 0x009E3580
// and complete virtual destructor at 0x009E31C0 establish the identity.

class INIEntry
{
public:
	virtual ~INIEntry();
};

void forceINIEntryDeletingDestructor()
{
	INIEntry value;
}
