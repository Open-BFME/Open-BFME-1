// ?Rva009AA970DumpRaw@@YAXPAURva009AA970Info@@PAXH@Z
struct Rva009AA970Info
{
	char m_pad[0x208];
	int m_lenLo;
	int m_lenHi;
};

__declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, ...);
__declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, void *stream);
__declspec(dllimport) void *__cdecl bfmeFopenVIF(const char *name, const char *mode);
__declspec(dllimport) void __cdecl bfmeFreeUXB(void *p);

void Rva009AA970DumpRaw(Rva009AA970Info *info, void *buf, int index)
{
	char name[0x100];
	sprintf(name, "y%04d.raw", index);
	void *fp = bfmeFopenVIF(name, "wb");
	unsigned int size = info->m_lenLo + info->m_lenHi * 2;
	fwrite(buf, size, 1, fp);
	bfmeFreeUXB(fp);
}

struct Rva009AA9E0Info
{
	char m_pad[0x1ec];
	unsigned int m_length;
};

// ?Rva009AA9E0DumpRaw@@YAXPBURva009AA9E0Info@@PBXH@Z
void Rva009AA9E0DumpRaw(const Rva009AA9E0Info *info, const void *bytes, int index)
{
	char name[0x100];
	sprintf(name, "y%d.raw", index);
	void *fp = bfmeFopenVIF(name, "wb");
	fwrite(bytes, info->m_length, 1, fp);
	bfmeFreeUXB(fp);
}
