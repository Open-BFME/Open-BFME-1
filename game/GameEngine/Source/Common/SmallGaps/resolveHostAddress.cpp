// ?resolveHostAddress@@YGHPBD@Z
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)
struct Rva00885430Hostent { char* h_name; char** h_aliases; short h_addrtype; short h_length; char** h_addr_list; };
extern "C" Rva00885430Hostent* __stdcall gethostbyname(const char* name);
extern int Rva00885430Resolved;
extern char Rva00885430Address[];
int __stdcall resolveHostAddress(const char* name)
{
	Rva00885430Hostent* host = gethostbyname(name);
	Rva00885430Resolved = 1;
	if (host)
		memcpy(Rva00885430Address, host->h_addr_list[0], host->h_length);
	else
		Rva00885430Address[0] = 0;
	return 0;
}
