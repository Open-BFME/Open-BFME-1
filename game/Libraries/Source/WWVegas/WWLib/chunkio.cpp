// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// WWLib chunk file writer, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWLib/chunkio.cpp). Compiled with NDEBUG because
// the retail binary strips the asserts. Only the ChunkSaveClass side is here:
// BFME's ChunkLoadClass drifted from this reference (it carries an extra pointer
// member and reads through a two-way virtual dispatch), so none of its methods
// match these verbatim bodies. The ChunkHeader/MicroChunkHeader inline accessors
// still emit out-of-line copies that match.
#include "chunkio.h"
#include <string.h>
#include <assert.h>

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

struct BFMEChunkLoadLayout
{
	FileClass *File;
	BFMEChunkInput *Input;
	int StackIndex;
	int PositionStack[256];
	ChunkHeader HeaderStack[256];
	bool InMicroChunk;
	char Padding[3];
	int MicroChunkPosition;
	MicroChunkHeader MCHeader;
};


bool ChunkLoadClass::Open_Chunk()
{
	BFMEChunkLoadLayout *layout = (BFMEChunkLoadLayout *)this;
	if (layout->StackIndex > 0) {
		if (layout->PositionStack[layout->StackIndex - 1] ==
			(layout->HeaderStack[layout->StackIndex - 1].ChunkSize & 0x7FFFFFFF)) {
			return false;
		}
	}

	if (layout->File) {
		if (layout->File->Read(&layout->HeaderStack[layout->StackIndex], sizeof(ChunkHeader)) != sizeof(ChunkHeader)) {
			return false;
		}
	} else if (layout->Input->Read(&layout->HeaderStack[layout->StackIndex], sizeof(ChunkHeader)) != sizeof(ChunkHeader)) {
		return false;
	}

	layout->PositionStack[layout->StackIndex] = 0;
	layout->StackIndex++;
	return true;
}


bool ChunkLoadClass::Close_Chunk()
{
	BFMEChunkLoadLayout *layout = (BFMEChunkLoadLayout *)this;
	int size = layout->HeaderStack[layout->StackIndex - 1].ChunkSize & 0x7FFFFFFF;
	int position = layout->PositionStack[layout->StackIndex - 1];

	if (position < size) {
		if (layout->File) {
			layout->File->Seek(size - position, SEEK_CUR);
		} else {
			layout->Input->Seek(size - position, SEEK_CUR);
		}
	}

	layout->StackIndex--;
	if (layout->StackIndex > 0) {
		layout->PositionStack[layout->StackIndex - 1] += size + sizeof(ChunkHeader);
	}

	return true;
}


uint32 ChunkLoadClass::Read(void *buffer, uint32 byte_count)
{
	BFMEChunkLoadLayout *layout = (BFMEChunkLoadLayout *)this;
	if (layout->PositionStack[layout->StackIndex - 1] + byte_count >
		(layout->HeaderStack[layout->StackIndex - 1].ChunkSize & 0x7FFFFFFF)) {
		return 0;
	}

	if (layout->InMicroChunk && layout->MicroChunkPosition + byte_count > layout->MCHeader.ChunkSize) {
		return 0;
	}

	if (layout->File) {
		if (layout->File->Read(buffer, byte_count) != (int)byte_count) {
			return 0;
		}
	} else if (layout->Input->Read(buffer, byte_count) != (int)byte_count) {
		return 0;
	}

	layout->PositionStack[layout->StackIndex - 1] += byte_count;
	if (layout->InMicroChunk) {
		layout->MicroChunkPosition += byte_count;
	}

	return byte_count;
}


// Read's twin, skipping instead of copying. The bounds checks are the same; the
// difference is how the skip is proven to have happened, since neither Seek
// interface reports a byte count -- both branches take a position before and
// after and require the delta to be exactly what was asked for.
uint32 ChunkLoadClass::Seek(uint32 byte_count)
{
	BFMEChunkLoadLayout *layout = (BFMEChunkLoadLayout *)this;
	if (layout->PositionStack[layout->StackIndex - 1] + byte_count >
		(layout->HeaderStack[layout->StackIndex - 1].ChunkSize & 0x7FFFFFFF)) {
		return 0;
	}

	if (layout->InMicroChunk && layout->MicroChunkPosition + byte_count > layout->MCHeader.ChunkSize) {
		return 0;
	}

	if (layout->File) {
		int before = layout->File->Tell();
		if (layout->File->Seek(byte_count, SEEK_CUR) - before != (int)byte_count) {
			return 0;
		}
	} else {
		int before = layout->Input->Seek(0, SEEK_CUR);
		if (layout->Input->Seek(byte_count, SEEK_CUR) - before != (int)byte_count) {
			return 0;
		}
	}

	layout->PositionStack[layout->StackIndex - 1] += byte_count;
	if (layout->InMicroChunk) {
		layout->MicroChunkPosition += byte_count;
	}

	return byte_count;
}


uint32 ChunkLoadClass::Cur_Chunk_ID()
{
	int index = *(int *)((char *)this + 0x08);
	return *(uint32 *)((char *)this + 0x404 + index * 8);
}


uint32 ChunkLoadClass::Cur_Chunk_Length()
{
	int index = *(int *)((char *)this + 0x08);
	return *(uint32 *)((char *)this + 0x408 + index * 8) & 0x7FFFFFFF;
}


int ChunkLoadClass::Cur_Chunk_Depth()
{
	return *(int *)((char *)this + 0x08);
}


// The high bit of a chunk's size word is the "this chunk holds sub-chunks"
// flag, so the test is the raw masked word rather than a bool.
int ChunkLoadClass::Contains_Chunks()
{
	int index = *(int *)((char *)this + 0x08);
	return *(uint32 *)((char *)this + 0x408 + index * 8) & 0x80000000;
}


uint32 ChunkLoadClass::Cur_Micro_Chunk_ID()
{
	return *(unsigned char *)((char *)this + 0xC14);
}


uint32 ChunkLoadClass::Cur_Micro_Chunk_Length()
{
	return *(unsigned char *)((char *)this + 0xC15);
}


bool ChunkLoadClass::Open_Micro_Chunk()
{
	if (Read((char *)this + 0xC14, 2) != 2) {
		return false;
	}

	*(bool *)((char *)this + 0xC0C) = true;
	*(int *)((char *)this + 0xC10) = 0;
	return true;
}


bool ChunkLoadClass::Close_Micro_Chunk()
{
	int pos = *(int *)((char *)this + 0xC10);
	int size = *(unsigned char *)((char *)this + 0xC15);
	*(bool *)((char *)this + 0xC0C) = false;

	if (pos < size) {
		FileClass *file = *(FileClass **)this;
		if (file) {
			file->Seek(size - pos, SEEK_CUR);
		} else {
			(*(BFMEChunkInput **)((char *)this + 4))->Seek(size - pos, SEEK_CUR);
		}

		int stack_index = *(int *)((char *)this + 8);
		if (stack_index > 0) {
			*(int *)((char *)this + 8 + stack_index * 4) += size - pos;
		}
	}

	return true;
}


ChunkSaveClass::ChunkSaveClass(FileClass * file) :
	File(file),
	StackIndex(0),
	InMicroChunk(false),
	MicroChunkPosition(0)
{
	memset(PositionStack,0,sizeof(PositionStack));
	memset(HeaderStack,0,sizeof(HeaderStack));
	memset(&MCHeader,0,sizeof(MCHeader));
}


bool ChunkSaveClass::Begin_Chunk(uint32 id)
{
	ChunkHeader	chunkh;
	int 			filepos;

	// If we have a parent chunk, set its 'Contains_Chunks' flag
	if (StackIndex > 0) {
		HeaderStack[StackIndex-1].Set_Sub_Chunk_Flag(true);
	}

	// Save the current file position and chunk header
	// for the call to End_Chunk.
	chunkh.Set_Type(id);
	chunkh.Set_Size(0);
	filepos = File->Seek(0);

	PositionStack[StackIndex] = filepos;
	HeaderStack[StackIndex] = chunkh;
	StackIndex++;

	// write a temporary chunk header (size = 0)
	if (File->Write(&chunkh,sizeof(chunkh)) != sizeof(chunkh)) {
		return false;
	}
	return true;
}


bool ChunkSaveClass::End_Chunk(void)
{
	// If the user didn't close his micro chunks bad things are gonna happen
	assert(!InMicroChunk);

	// Save the current position
	int curpos = File->Seek(0);

	// Pop the position and chunk header off the stacks
	StackIndex--;
	int chunkpos = PositionStack[StackIndex];
	ChunkHeader chunkh = HeaderStack[StackIndex];

	// write the completed header
	File->Seek(chunkpos,SEEK_SET);
	if (File->Write(&chunkh,sizeof(chunkh)) != sizeof(chunkh)) {
		return false;
	}

	// Add the total bytes written to any encompasing chunk
	if (StackIndex != 0) {
		HeaderStack[StackIndex-1].Add_Size(chunkh.Get_Size() + sizeof(chunkh));
	}

	// Go back to the end of the file
	File->Seek(curpos,SEEK_SET);

	return true;
}


bool ChunkSaveClass::Begin_Micro_Chunk(uint32 id)
{
	assert(id < 256);
	assert(!InMicroChunk);

	// Save the current file position and chunk header
	// for the call to End_Micro_Chunk.
	MCHeader.Set_Type(id);
	MCHeader.Set_Size(0);
	MicroChunkPosition = File->Seek(0);

	// Write a temporary chunk header
	// NOTE: I'm calling the ChunkSaveClass::Write method so that the bytes for
	// this header are tracked in the wrapping chunk.  This is because micro-chunks
	// are simply data inside the normal chunks...
	if (Write(&MCHeader,sizeof(MCHeader)) != sizeof(MCHeader)) {
		return false;
	}

	InMicroChunk = true;
	return true;
}


bool ChunkSaveClass::End_Micro_Chunk(void)
{
	assert(InMicroChunk);

	// Save the current position
	int curpos = File->Seek(0);

	// Seek back and write the micro chunk header
	File->Seek(MicroChunkPosition,SEEK_SET);
	if (File->Write(&MCHeader,sizeof(MCHeader)) != sizeof(MCHeader)) {
		return false;
	}

	// Go back to the end of the file
	File->Seek(curpos,SEEK_SET);
	InMicroChunk = false;
	return true;
}


uint32 ChunkSaveClass::Write(const void * buf, uint32 nbytes)
{
	// If this assert hits, you mixed data and chunks within the same chunk NO NO!
	assert(HeaderStack[StackIndex-1].Get_Sub_Chunk_Flag() == 0);

	// If this assert hits, you didnt open any chunks yet
	assert(StackIndex > 0);

	// write the bytes into the file
	if (File->Write(buf,nbytes) != (int)nbytes) return 0;

	// track them in the wrapping chunk
	HeaderStack[StackIndex-1].Add_Size(nbytes);

	// track them if you are using a micro-chunk too.
	if (InMicroChunk) {
		assert(MCHeader.Get_Size() < 255 - nbytes);	// micro chunks can only be 255 bytes
		MCHeader.Add_Size(nbytes);
	}

	return nbytes;
}


uint32 ChunkSaveClass::Write(const IOVector2Struct & v)
{
	return Write(&v,sizeof(v));
}


uint32 ChunkSaveClass::Write(const IOVector3Struct & v)
{
	return Write(&v,sizeof(v));
}


uint32 ChunkSaveClass::Write(const IOVector4Struct & v)
{
	return Write(&v,sizeof(v));
}


uint32 ChunkSaveClass::Write(const IOQuaternionStruct & q)
{
	return Write(&q,sizeof(q));
}
