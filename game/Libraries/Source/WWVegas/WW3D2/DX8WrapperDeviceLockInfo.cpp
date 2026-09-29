// cl: /DNDEBUG /MD /EHsc
// Retail 0x00903170 (48 B): after taking the DX8 device lock (0x00903090),
// record when, by whom and from where it was taken. BFME-only bookkeeping
// between the matched Try_Acquire_Device_Lock and Owns_Device_Lock; nothing
// references it, so the name keeps the address.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
void W3DRadarResetLock(void);

extern unsigned long g_013405D4;
extern const char *g_013405D8;
extern int g_013405DC;
extern unsigned long g_013405E0;

class DX8Wrapper
{
public:
	static void rva00903170(const char *file, int line);

private:
	static volatile unsigned long OwnerThreadId;
};

void DX8Wrapper::rva00903170(const char *file, int line)
{
	W3DRadarResetLock();
	g_013405D4 = timeGetTime();
	g_013405D8 = file;
	g_013405DC = line;
	g_013405E0 = OwnerThreadId;
}
