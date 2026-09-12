// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// Combined scratch TU for the two MeshGeometry Slot64 ShareBuffer members
// emitted from the same local class definition.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include <string.h>

inline void *operator new(unsigned int, void *place)
{
	return place;
}

struct MeshGeometrySlot64Element_00923F70
{
	uint8 Data[16];
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment);
	__declspec(noinline) void Resize(int newsize);

protected:
	T *RawBuffer;
	T *Array;
	int Count;
	int Alignment;
};

template <>
__declspec(noinline)
ShareBufferClass<MeshGeometrySlot64Element_00923F70>::ShareBufferClass(
	int count, const char *msg, int alignment) :
	Count(count),
	Alignment(alignment)
{
	if (Alignment == 0) {
		RawBuffer = (MeshGeometrySlot64Element_00923F70 *)MSGW3DNEWARRAY(msg)
			char[Count * sizeof(MeshGeometrySlot64Element_00923F70)];
		Array = RawBuffer;
	} else {
		RawBuffer = (MeshGeometrySlot64Element_00923F70 *)MSGW3DNEWARRAY(msg)
			char[Count * sizeof(MeshGeometrySlot64Element_00923F70) + Alignment];
		Array = (MeshGeometrySlot64Element_00923F70 *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
}

template <class T>
void ShareBufferClass<T>::Resize(int newsize)
{
	if (newsize < 0 || newsize == Count) {
		return;
	}

	T *new_raw;
	T *new_array;
	if (Alignment == 0) {
		new_raw = (T *)new char[newsize * sizeof(T)];
		new_array = new_raw;
	} else {
		new_raw = (T *)new char[newsize * sizeof(T) + Alignment];
		new_array = (T *)(((unsigned int)new_raw + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}

	if (Count > 0 && newsize > 0) {
		int copycount = (Count < newsize) ? Count : newsize;
		memcpy(new_raw, RawBuffer, copycount * sizeof(T));
	}

	delete[] RawBuffer;
	RawBuffer = new_raw;
	Array = new_array;
	Count = newsize;
}

template void ShareBufferClass<MeshGeometrySlot64Element_00923F70>::Resize(int);
