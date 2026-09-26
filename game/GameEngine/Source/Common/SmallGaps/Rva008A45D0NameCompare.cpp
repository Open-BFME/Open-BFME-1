// ?nameEquals@Rva008A45D0Owner@@QAE_NPBD@Z
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
struct Rva008A45D0StringData { int m_refs; int m_len; char m_chars[1]; };
struct Rva008A45D0Owner {
	Rva008A45D0StringData* m_data;
	bool nameEquals(const char* text);
};
bool Rva008A45D0Owner::nameEquals(const char* text)
{
	return strcmp(m_data->m_chars, text) == 0;
}
