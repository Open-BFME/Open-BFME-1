// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete 403-byte loader at RVA 0x00971990; address-qualified owner.
// ABI slice keeps the BFME prototype layout (owned HTree at +0x14, StringClass
// at +0x18, file args at +0x1c/+0x20) and the exact hierarchy chunk path.

#include <string.h>
#pragma intrinsic(strlen, memcpy)

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

// The shared BFME image stores this exact ".w3d" literal at VA 0x011139E4;
// the HLOD and aggregate loader recoveries use the same verified symbol.
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

class HTreeClass
{
public:
	HTreeClass();
	~HTreeClass();
	int Load_W3D(ChunkLoadClass &cload);

private:
	char m_opaque[0x1c];
};

class GenBase009EB7D0
{
public:
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

// ABI overlay for the HIER catalog prototype constructed by the matched
// constructor at RVA 0x00971670.  The owner is named by that address; no
// historical source class name is asserted.
class Rva00971670Proto : public GenBase009EB7D0
{
public:
	void LoadHierarchy();

private:
	HTreeClass *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

// Keep the exact decorated helper ABI.  The three words are semantically
// filename, offset, and size, but the retail row is void*(void*,void*,const char*).
extern void *Open_W3D_File(void *filename_arg, void *offset_arg, const char *size_arg);

// The constructor at RVA 0x00971670 installs vtable VA 0x0113E7B0;
// its load slot reaches this body and its type slot returns HIER.
void Rva00971670Proto::LoadHierarchy()
{
	if (m_ptr != 0)
		return;

	StringClass filename((const char *)m_name + 2);
	filename += Rva011139E4_W3D_Extension;

	BFMEChunkInput *file = (BFMEChunkInput *)Open_W3D_File(
		(void *)(const char *)filename,
		(void *)(unsigned int)m_first,
		(const char *)(unsigned int)m_second);
	if (file != 0) {
		ChunkLoadClass cload(file);
		if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x100) {
			m_ptr = new HTreeClass;
			// Load_W3D returns OK (0); retail retains the HTree on zero and
			// destroys/deletes/clears it only for a nonzero load error.  The
			// target calls through even when operator new returned null.
			if (m_ptr->Load_W3D(cload)) {
				delete m_ptr;
				m_ptr = 0;
			}
		}
		file->slot2();
	}
}
