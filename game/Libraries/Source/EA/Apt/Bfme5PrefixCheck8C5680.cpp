// Compare a string against the current command prefix.
const char *rva012D5A08Prefix = "FSCommand:";
extern "C" unsigned __cdecl strlen(const char *);
extern "C" int __cdecl strncmp(const char *, const char *, unsigned);

unsigned char __stdcall bfmeHasPrefix8C5680(const char *text)
{
	const char *prefix = rva012D5A08Prefix;
	return strncmp(text, prefix, strlen(prefix)) == 0;
}
