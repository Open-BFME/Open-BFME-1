// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00C715DE (10 B) is the address-only CRT callback that the initializer at
// 0x00C6E34D registers with atexit. It moves the object at VA 0x0134FB48 into ECX and
// tail-jumps to the critical-section and array cleanup at 0x009F69D3 (BfmeThingDXB).

class Rva009F6ADBObject
{
public:
	unsigned char storage[60];
};

extern Rva009F6ADBObject g_rva0134FB48;

class BfmeThingDXB
{
public:
	void bfmeGoDXB(void);
};

void Rva00C715DERelease(void)
{
	((BfmeThingDXB *)(void *)&g_rva0134FB48)->bfmeGoDXB();
}
