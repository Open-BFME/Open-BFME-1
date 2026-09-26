// cl: /DNDEBUG /MD /EHsc
// BFME HLOD catalog prototype loader — retail 0x00970AA0, 288 bytes.
//
// The constructor at 0x00970880 establishes the common BFME prototype
// layout: the base subobject ends at +0x14, the owned prototype at +0x14,
// StringClass name at +0x18, and the two file-open arguments at +0x1c/+0x20.
// The vtable containing this slot is the HLOD catalog entry: it carries the
// HLOD type and the adjacent name/delete slots, while the body below opens
// the named file and constructs an HLodDefClass for chunk 0x700.

class StringClass
{
public:
	StringClass(const StringClass &string, bool hint_temporary = false);
	~StringClass();
	const StringClass &operator+=(const char *string);
	operator const char *() const { return m_buffer; }

private:
	char *m_buffer;
};

extern "C" const char Rva011139E4_W3D_Extension[];

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

private:
	char m_opaque[0xc18];
};

class HLodDefClass
{
public:
	HLodDefClass();
	~HLodDefClass();
	bool Load_W3D(ChunkLoadClass &cload);

private:
	char m_opaque[0x24];
};

class GenBase009EB7D0
{
public:
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00970880Proto : public GenBase009EB7D0
{
public:
	virtual void Load_HLOD();

private:
	HLodDefClass *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

extern void *Open_W3D_File(void *a, void *b, const char *filename);

void Rva00970880Proto::Load_HLOD()
{
	StringClass filename(m_name, false);
	filename += Rva011139E4_W3D_Extension;

	BFMEChunkInput *file = (BFMEChunkInput *)Open_W3D_File(
		(void *)(const char *)filename,
		(void *)(unsigned int)m_first,
		(const char *)(unsigned int)m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x700) {
			m_ptr = new HLodDefClass;
			if (!m_ptr->Load_W3D(cload)) {
				delete m_ptr;
				m_ptr = 0;
			}
		}
		file->slot2();
	}
}
