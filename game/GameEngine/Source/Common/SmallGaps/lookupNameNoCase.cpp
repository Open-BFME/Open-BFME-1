// ?lookupNameNoCase@@YAHPBURva006A16B0String@@@Z
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
struct Rva006A16B0StringData { int m_refs; unsigned short m_length; unsigned short m_alloc; char m_chars[1]; };
struct Rva006A16B0String { Rva006A16B0StringData* m_data; };
struct Rva006A16B0Entry { const char* m_name; int m_value; };
extern Rva006A16B0Entry Rva006A16B0Table[0x1a];
extern char Rva006A16B0Empty[];
static inline int Rva006A16B0Compare(const Rva006A16B0String* s, const char* name)
{
	int nameLen = name ? strlen(name) : 0;
	Rva006A16B0StringData* data = s->m_data;
	int len = data ? data->m_length : 0;
	const char* chars = data->m_chars;
	if (!data)
		chars = Rva006A16B0Empty;
	int r = _memicmp(chars, name, len < nameLen ? len : nameLen);
	if (r != 0)
		return r;
	return len - nameLen;
}
int lookupNameNoCase(const Rva006A16B0String* s)
{
	for (unsigned int i = 0; i < 0x1a; ++i) {
		if (Rva006A16B0Compare(s, Rva006A16B0Table[i].m_name) == 0)
			return Rva006A16B0Table[i].m_value;
	}
	return -1;
}
