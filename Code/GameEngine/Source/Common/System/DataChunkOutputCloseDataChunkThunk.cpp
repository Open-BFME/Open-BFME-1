// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the DataChunkOutput::closeDataChunk naked dump to clean C++.
//
// Zero Hour's DataChunk.cpp body, unchanged. Retail confirms every step: record
// the position, seek back to the chunk header, write the size that goes there,
// seek forward again, then pop the chunk off the stack and free it.
//
// The three CRT calls go through the IAT because they are dllimport under /MD,
// and MSVC hoists the fseek slot into ebx since it is used twice. Their stack
// arguments are cleaned up in one `add esp,0x2C` at the end rather than after
// each call, which is why the frame looks larger than any single call needs.
//
// deleteInstance() is a plain `delete`: retail loads the vtable, pushes the
// deleting-destructor flag 1 and calls slot 0, guarded by the null test MSVC
// always emits for delete -- not a second check of m_chunkStack, which the
// early return already settled.
//
// Retail pins the layout: the file handle is at this+0x04 and the chunk stack
// at this+0x18, with the chunk's next pointer at +0x04 and its recorded file
// position at +0x0C. The size written back excludes its own four bytes.

typedef int Int;

extern "C" __declspec(dllimport) long __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size,
															 unsigned int count, void *stream);

enum { SEEK_SET_ = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class OutputChunk
{
public:
	virtual ~OutputChunk();

	// the vtable pointer occupies +0x00
	OutputChunk *next;									///< retail this+0x04
	unsigned char m_unreconstructed_08[4];
	Int filepos;										///< retail this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void closeDataChunk(void);

private:
	unsigned char m_unreconstructed_00[4];
	void *m_tmp_file;									///< retail this+0x04
	unsigned char m_unreconstructed_08[0x10];
	OutputChunk *m_chunkStack;							///< retail this+0x18
};

// ?closeDataChunk@DataChunkOutput@@QAEXXZ
void DataChunkOutput::closeDataChunk(void)
{
	if (m_chunkStack == 0)
	{
		// TODO: Throw exception
		return;
	}

	// remember where we are
	Int here = ftell(m_tmp_file);

	// rewind to store the data size
	fseek(m_tmp_file, m_chunkStack->filepos, SEEK_SET_);

	// compute data size (not including the actual data size itself)
	Int size = here - m_chunkStack->filepos - sizeof(Int);

	// store the data size
	fwrite((const char *)&size, sizeof(Int), 1, m_tmp_file);

	// go back to where we were
	fseek(m_tmp_file, here, SEEK_SET_);

	// pop the chunk off the stack
	OutputChunk *c = m_chunkStack;
	m_chunkStack = m_chunkStack->next;
	delete c;
}
