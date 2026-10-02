// cl: /DNDEBUG /MD /EHsc
// BFME ABI-slice reconstruction of the box loader at retail 0x00972480,
// slot 9 of the prototype vtable at 0x0113E814 (deleting destructor
// 0x00971D80; slot 7 returns the +0x18 name).
//
// Same layout as the mesh prototype loader at 0x00970CD0: m_ptr at +0x14, a
// one-word name at +0x18 and the two Open_W3D_File arguments at +0x1c/+0x20.
// This variant only swaps an existing extension for ".w3d", accepts
// W3D_CHUNK_BOX (0x740) and reads the 0x44-byte W3dBoxStruct into a fresh
// allocation at +0x14. The class identity is not recovered; the
// address-derived class name is intentional.

#include <string.h>

class BFMEChunkInput
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

class ChunkLoadClass
{
public:
	ChunkLoadClass(BFMEChunkInput *input);
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();
	unsigned long Read(void *buffer, unsigned long nbytes);

private:
	char m_opaque[0xc18];
};

struct W3dBoxStruct
{
	char m_data[0x44];
};

class Rva00972480Proto
{
public:
	void Load_Box();

private:
	char m_pad00[0x14];
	W3dBoxStruct *m_box;
	char *m_name;
	int m_first;
	int m_second;
};

extern void *Open_W3D_File(void *a, void *b, const char *filename);

void Rva00972480Proto::Load_Box()
{
	BFMEChunkInput *file;
	char filename[260];

	strcpy(filename, m_name);
	char *dot = strchr(filename, '.');
	if (dot != 0) {
		*reinterpret_cast<volatile unsigned int *>(dot) =
			*reinterpret_cast<const volatile unsigned int *>(".w3d");
		*(reinterpret_cast<volatile unsigned char *>(dot) + 4) =
			*(reinterpret_cast<const volatile unsigned char *>(".w3d") + 4);
	}

	file = (BFMEChunkInput *)Open_W3D_File(
		(void *)filename,
		(void *)(unsigned int)m_first,
		(const char *)(unsigned int)m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x740) {
			m_box = new W3dBoxStruct;
			cload.Read(m_box, sizeof(W3dBoxStruct));
		}
		file->slot2();
	}
}
