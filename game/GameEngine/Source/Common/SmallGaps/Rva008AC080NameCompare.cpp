// ?nameDiffers@Rva008AC080Owner@@QAE_NPBD@Z
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
struct Rva008AC080StringData { int m_refs; int m_len; char m_chars[1]; };
struct Rva008AC080Owner {
	Rva008AC080StringData* m_data;
	bool nameDiffers(const char* text);
};
bool Rva008AC080Owner::nameDiffers(const char* text)
{
	return strcmp(m_data->m_chars, text) != 0;
}
