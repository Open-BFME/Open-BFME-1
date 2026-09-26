// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// readable body of ??0Buffer@@: game/Libraries/Source/WWVegas/WW3D2/bw_render.cpp
// readable body of ??1Buffer@@: game/Libraries/Source/WWVegas/WW3D2/bw_render.cpp


#include	"always.h"
#define BFME_BUFFER_DTOR_OUT_OF_LINE
#include	"buff.h"
#undef BFME_BUFFER_DTOR_OUT_OF_LINE



Buffer::Buffer(void * buffer, long size) :
	BufferPtr(buffer),
	Size(size),
	IsAllocated(false)
{
	if (buffer == NULL && size > 0) {
		BufferPtr = W3DNEWARRAY char[size];
		IsAllocated = true;
	}
}


// Alternate constructor for char * pointer.
Buffer::Buffer(char * buffer, long size) :
	BufferPtr(buffer),
	Size(size),
	IsAllocated(false)
{
	if (buffer == NULL && size > 0) {
		BufferPtr = W3DNEWARRAY char[size];
		IsAllocated = true;
	}
}


// Alternate constructor for void const * pointer.
Buffer::Buffer(void const * buffer, long size) :
	BufferPtr((void*)buffer),
	Size(size),
	IsAllocated(false)
{
	if (buffer == NULL && size > 0) {
		BufferPtr = W3DNEWARRAY char[size];
		IsAllocated = true;
	}
}


Buffer::Buffer(long size) :
	BufferPtr(NULL),
	Size(size),
	IsAllocated(false)
{
	if (size > 0) {
		BufferPtr = W3DNEWARRAY char[size];
		IsAllocated = true;
	}
}


Buffer::Buffer(Buffer const & buffer) :
	IsAllocated(false)
{
	BufferPtr = buffer.BufferPtr;
	Size = buffer.Size;
}


Buffer & Buffer::operator = (Buffer const & buffer)
{
	if (&buffer != this) {
		if (IsAllocated) {
			delete [] BufferPtr;
		}
		IsAllocated = false;
		BufferPtr = buffer.BufferPtr;
		Size = buffer.Size;
	}
	return(*this);
}


Buffer::~Buffer(void)
{
	Reset();
}


void Buffer::Reset(void)
{
	if (IsAllocated) {
		delete [] BufferPtr;
	}
	BufferPtr = NULL;
	Size = 0;
	IsAllocated = false;
}
