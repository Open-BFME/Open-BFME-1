// cl: /DNDEBUG /MD /EHsc
// BFME ABI-slice reconstruction of the slot-2 loader at retail 0x00970CD0.
//
// The matched constructor at 0x00970EC0 establishes a GenBase009EB7D0
// subobject followed by m_ptr at +0x14, a one-word StringClass at +0x18 and
// two integer file-open arguments at +0x1c/+0x20.  The class identity of this
// BFME-only vtable entry is not recovered; the address-derived class name is
// intentional.  The method opens the derived .w3d name, accepts chunk zero,
// builds a 0x318-byte MeshClass and stores it at +0x14.

#include <string.h>

extern "C" volatile unsigned int Rva011139E4_W3D_Extension;

class BFMEChunkInput
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int Read(void *buffer, int size);
	virtual void slot4();
	virtual int Seek(int pos, int dir);
};

class ChunkLoadClass
{
public:
	ChunkLoadClass(BFMEChunkInput *input);
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();

private:
	char m_opaque[0xc18];
};

class MeshClass
{
public:
	MeshClass();
	bool Load_W3D(ChunkLoadClass &cload);
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_ref_count == 0)
			Delete_This();
	}

private:
	int m_ref_count;
	char m_opaque[0x310];
};

class GenBase009EB7D0
{
public:
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00970EC0Proto : public GenBase009EB7D0
{
public:
	virtual void Load_Mesh();

private:
	MeshClass *m_ptr;
	char *m_name;
	int m_first;
	int m_second;
};

extern void *Open_W3D_File(void *a, void *b, const char *filename);

void Rva00970EC0Proto::Load_Mesh()
{
	BFMEChunkInput *file;
	char filename[260];

	strcpy(filename, m_name);
	char *dot = strchr(filename, '.');
	if (dot != 0) {
		*reinterpret_cast<volatile unsigned int *>(dot) = Rva011139E4_W3D_Extension;
		*(reinterpret_cast<volatile unsigned char *>(dot) + 4) =
			*(reinterpret_cast<volatile unsigned char *>(&Rva011139E4_W3D_Extension) + 4);
	} else {
		strcat(filename, ".w3d");
	}

	file = (BFMEChunkInput *)Open_W3D_File(
		(void *)filename,
		(void *)(unsigned int)m_first,
		(const char *)(unsigned int)m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0) {
			m_ptr = new MeshClass;
			if (!m_ptr->Load_W3D(cload)) {
				m_ptr->Release_Ref();
				m_ptr = 0;
			}
		}
		file->slot2();
	}
}
