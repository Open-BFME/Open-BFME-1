extern "C" void bfmeDtorDAB(void *what);

// Retail's atexit cleanup registers WaterSettings, an array of six WaterSetting
// objects of element size 0x7C at 0x012F1608 (defined by
// Rva00C6B810StaticInit.cpp).  Only the mangled symbol name matters here.
class WaterSetting;
extern WaterSetting WaterSettings[];

void __stdcall bfmeRegisterDAB(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAB()
{
	bfmeRegisterDAB(WaterSettings, 0x7c, 6, bfmeDtorDAB);
}
