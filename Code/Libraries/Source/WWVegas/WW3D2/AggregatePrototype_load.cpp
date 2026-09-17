// cl: /DNDEBUG /MD /EHsc
// BFME aggregate catalog prototype loader, retail 0x00972060, 275 bytes.
//
// The constructor at 0x00971CE0 and Register_Aggregate_Prototype identify this
// vtable as the aggregate catalog entry. The method opens the named .w3d file,
// reads aggregate chunk 0x600, and stores its AggregateDefClass definition.

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

class AggregateDefClass
{
public:
	AggregateDefClass();
	virtual ~AggregateDefClass();
	virtual bool Load_W3D(ChunkLoadClass &cload);

private:
	char m_opaque[0x58];
};

class GenBase009EB7D0
{
public:
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00971CE0AggregatePrototype : public GenBase009EB7D0
{
public:
	virtual void Load_Aggregate();

private:
	AggregateDefClass *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

extern void *Open_W3D_File(void *a, void *b, const char *filename);

void Rva00971CE0AggregatePrototype::Load_Aggregate()
{
	StringClass filename(m_name, false);
	filename += Rva011139E4_W3D_Extension;

	BFMEChunkInput *file = (BFMEChunkInput *)Open_W3D_File(
		(void *)(const char *)filename,
		(void *)(unsigned int)m_first,
		(const char *)(unsigned int)m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x600) {
			m_ptr = new AggregateDefClass;
			if (!m_ptr->Load_W3D(cload)) {
				delete m_ptr;
				m_ptr = 0;
			}
		}
		file->slot2();
	}
}
