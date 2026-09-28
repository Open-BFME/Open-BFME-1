// cl: /DNDEBUG /MD /EHsc
// BFME animation catalog prototype loader, retail 0x0090C080, 479 bytes.
//
// Identity: vtable 0x0113A510, installed by the prototype constructor at
// 0x0090BD60 (ledger row Rva0090BD60Proto), holds this body at slot +0x08, so
// it is a virtual member of that prototype class -- the naked lift's
// "W3DAnimationLoader" and its non-virtual `@QAEXXZ` were both wrong.
// Evidence: targets/game/reverse/identity_evidence/0090C080-vtable-slot.md
//
// The member rewrites the registered name's extension to ".w3d", opens that
// file through the shared W3D opener and reads animation chunk 0x200
// (HRawAnimClass, 0x50 bytes) or 0x280 (HCompressedAnimClass, 0x54 bytes) from
// it.  The owned object is released and cleared when Load_W3D reports a
// non-zero error.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" void *__cdecl memcpy(void *dest, const void *source, unsigned int count);
#pragma intrinsic(strlen, memcpy)

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

class StringClass
{
public:
	StringClass(const char *string, bool hint_temporary = false)
		: m_Buffer(m_EmptyString)
	{
		int len = string ? (int)strlen(string) : 0;
		if (hint_temporary || len > 0)
			Get_String(len + 1, hint_temporary);
		*this = string;
	}
	~StringClass() { Free_String(); }
	const StringClass &operator=(const char *string)
	{
		if (string != 0) {
			int len = (int)strlen(string);
			Uninitialised_Grow(len + 1);
			Store_Length(len);
			memcpy(m_Buffer, string, len + 1);
		}
		return *this;
	}
	const StringClass &operator+=(const char *string);
	operator const char *() const { return m_Buffer; }

private:
	struct Header { int allocated_length; int length; };
	static char *m_EmptyString;
	void Get_String(int length, bool is_temp);
	void Uninitialised_Grow(int length);
	void Free_String();
	void Store_Length(int length)
	{
		if (m_Buffer != m_EmptyString)
			((Header *)m_Buffer - 1)->length = length;
	}
	char *m_Buffer;
};

// The shared BFME image stores this exact ".w3d" literal at VA 0x011139E4.
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

class HRawAnimClass
{
public:
	HRawAnimClass();
	int Load_W3D(ChunkLoadClass &cload);
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_ref_count == 0)
			Delete_This();
	}

private:
	int m_ref_count;
	char m_opaque[0x48];
};

class HCompressedAnimClass
{
public:
	HCompressedAnimClass();
	int Load_W3D(ChunkLoadClass &cload);
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_ref_count == 0)
			Delete_This();
	}

private:
	int m_ref_count;
	char m_opaque[0x4c];
};

class GenBase009EB7D0
{
public:
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

// The class whose constructor at 0x0090BD60 installs vtable 0x0113A510; its
// +0x08 slot is this body.  Offsets: owned object +0x14, StringClass name
// +0x18, the two W3D opener arguments +0x1c and +0x20.
class Rva0090BD60Proto : public GenBase009EB7D0
{
public:
	virtual void Load_Animation();

private:
	void *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

extern void *Open_W3D_File(void *filename_arg, void *offset_arg, const char *size_arg);

void Rva0090BD60Proto::Load_Animation()
{
	char *dot = strchr(m_name, '.');

	if (dot != 0) {
		StringClass filename(dot + 1);
		filename += Rva011139E4_W3D_Extension;

		BFMEChunkInput *file = (BFMEChunkInput *)Open_W3D_File(
			(void *)(const char *)filename,
			(void *)(unsigned int)m_first,
			(const char *)(unsigned int)m_second);
		if (file != 0) {
			ChunkLoadClass cload(file);
			if (cload.Open_Chunk()) {
				unsigned long id = cload.Cur_Chunk_ID();
				switch (id) {
				case 0x200:
					m_ptr = new HRawAnimClass;
					if (((HRawAnimClass *)m_ptr)->Load_W3D(cload)) {
						((HRawAnimClass *)m_ptr)->Release_Ref();
						m_ptr = 0;
					}
					break;
				case 0x280:
					m_ptr = new HCompressedAnimClass;
					if (((HCompressedAnimClass *)m_ptr)->Load_W3D(cload)) {
						((HCompressedAnimClass *)m_ptr)->Release_Ref();
						m_ptr = 0;
					}
					break;
				}
			}
			file->slot2();
		}
	}
}
