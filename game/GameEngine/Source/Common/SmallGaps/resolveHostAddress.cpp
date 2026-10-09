// ?resolveHostAddress@@YGHPBD@Z
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)
struct Rva00885430Hostent { char* h_name; char** h_aliases; short h_addrtype; short h_length; char** h_addr_list; };
extern "C" Rva00885430Hostent* __stdcall gethostbyname(const char* name);
// Retail .bss VA 0x01336D00: set once a lookup ran. Address-derived name.
int g_Va01336D00;
// Retail .bss VA 0x01336CF4: the resolved IPv4 address bytes. Address-derived name.
char g_Va01336CF4[4];
int __stdcall resolveHostAddress(const char* name)
{
	Rva00885430Hostent* host = gethostbyname(name);
	g_Va01336D00 = 1;
	if (host)
		memcpy(g_Va01336CF4, host->h_addr_list[0], host->h_length);
	else
		g_Va01336CF4[0] = 0;
	return 0;
}
