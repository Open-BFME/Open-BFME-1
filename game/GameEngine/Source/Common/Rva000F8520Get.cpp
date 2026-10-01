// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// TU-local VIEW of the real GlobalData, kept only for its offsets.
struct Rva000F8520Obj
{
	char m_pad[0xB60];
	int m_value;
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`.  Only
// Common/GlobalData.cpp may DEFINE it; this TU is a second reader of it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

int rva000F8520Get()
{
	return ((Rva000F8520Obj *)TheWritableGlobalData)->m_value;
}
