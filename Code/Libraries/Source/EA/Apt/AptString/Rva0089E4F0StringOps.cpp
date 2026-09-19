// ?equalsChars@Rva0089E4F0String@@QAE_NPBD@Z
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" int __cdecl memcmp(const void*, const void*, unsigned int);
extern "C" char* __cdecl strchr(const char*, int);
#pragma intrinsic(strlen, memcmp)
int __cdecl bfmeCompareVSC(const char* a, const char* b);
struct BfmeStringPool3AF0 { void* (__cdecl* m_alloc)(unsigned int bytes); };
extern BfmeStringPool3AF0* g_bfmeStringPool1284;
struct Rva0089E4F0Data { unsigned short m_refs; unsigned short m_len; unsigned short m_cap; unsigned short m_hash; char m_chars[1]; };
struct Rva0089E4F0String {
	Rva0089E4F0Data* m_data;
	bool equalsChars(const char* s);
	void* replaceChar(char from, char to);
	bool equalsHashed(const Rva0089E4F0String* other);
	void allocate(int length);
};
bool Rva0089E4F0String::equalsChars(const char* s)
{
	unsigned int len = strlen(s);
	if (m_data->m_len < len)
		return false;
	if (memcmp(m_data->m_chars, s, len))
		return false;
	return true;
}
// ?replaceChar@Rva0089E4F0String@@QAEPAXDD@Z
void* Rva0089E4F0String::replaceChar(char from, char to)
{
	for (char* p = strchr(m_data->m_chars, from); p; p = strchr(p + 1, from))
		*p = to;
	return 0;
}
// ?equalsHashed@Rva0089E4F0String@@QAE_NPBU1@@Z
bool Rva0089E4F0String::equalsHashed(const Rva0089E4F0String* other)
{
	if (m_data == other->m_data)
		return true;
	if (m_data->m_hash != other->m_data->m_hash)
		return false;
	return bfmeCompareVSC(m_data->m_chars, other->m_data->m_chars) == 0;
}
// ?allocate@Rva0089E4F0String@@QAEXH@Z
void Rva0089E4F0String::allocate(int length)
{
	unsigned int size = (length + 0xc) & ~3;
	m_data = (Rva0089E4F0Data*)g_bfmeStringPool1284->m_alloc(size);
	m_data->m_refs = 1;
	m_data->m_cap = (unsigned short)(size - 9);
}
