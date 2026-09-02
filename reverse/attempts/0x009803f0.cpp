// ?read@Rva009803F0Owner@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.6 date=2026-09-02
// cl: /DNDEBUG /MD /O2 /EHs-c-

__declspec(dllimport) unsigned char * __cdecl _mbsdup(const unsigned char *);

class ChunkLoadClass
{
public:
	unsigned int Read(void *buf, unsigned int nbytes);
};

struct Rva009803F0Buf
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int e;
};

class Rva009803F0Owner
{
public:
	bool read(ChunkLoadClass &cload);

private:
	void *m_vft;
	unsigned int m_first;
	char m_pad[0x50];
	unsigned char *m_dup;
};

bool Rva009803F0Owner::read(ChunkLoadClass &cload)
{
	Rva009803F0Buf buf;
	buf.a = 0;
	buf.b = 0;
	buf.c = 0;
	buf.d = 0;
	buf.e = 0;

	if (cload.Read(&buf, 0x14) != 0x14)
		return false;

	m_dup = _mbsdup((const unsigned char *)&buf);
	m_first = buf.a;
	return true;
}
