// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// TU-local VIEW of the real GlobalData, kept only for its offsets.
struct Rva00336860Obj
{
	char m_pad[0xB8C];
	int m_value;
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`.  Only
// Common/GlobalData.cpp may DEFINE it; this TU is a second reader of it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

int rva00336860Get()
{
	return ((Rva00336860Obj *)TheWritableGlobalData)->m_value;
}
