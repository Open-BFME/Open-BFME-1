// ?Rva009AA9E0RawDump@@YAXPAX0H@Z
// Codec raw-frame writers recovered from the contiguous retail text section at 0x009AA9E0.

struct Rva009AA9E0Info
{
	unsigned char m_pad[0x1EC];
	unsigned int m_size;
};

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *, const char *, ...);
extern "C" __declspec(dllimport) void *__cdecl fopen(
	const char *, const char *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *, unsigned int, unsigned int, void *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);

void __cdecl Rva009AA9E0RawDump(void *info, void *data, int index)
{
	char name[0x100];
	sprintf(name, "y%d.raw", index);
	void *file = fopen(name, "wb");
	fwrite(data, ((Rva009AA9E0Info *)info)->m_size, 1, file);
	fclose(file);
}
