// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: retail aligned ShareBufferClass<Vector3> copy constructor.

void *operator new[](unsigned int size);
void operator delete[](void *block);
inline void *operator new(unsigned int, void *place) { return place; }

#include "../WWMath/vector3.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

template <class Type>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);
	~ShareBufferClass(void);

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
	Count(that.Count)
{
	Alignment = that.Alignment;
	if (Alignment == 0) {
		RawBuffer = new Type[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (Type *)new char[Count * sizeof(Type) + Alignment];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for (int index = 0; index < Count; ++index) {
		Array[index] = that.Array[index];
	}
}

// sharebuf.h's BFME destructor, so this TU's COMDAT copy is the shared one.
template <class Type>
ShareBufferClass<Type>::~ShareBufferClass(void)
{
	if (RawBuffer) {
		delete[] RawBuffer;
		RawBuffer = 0;
		Array = 0;
	}
}

template ShareBufferClass<Vector3>::ShareBufferClass(
	const ShareBufferClass<Vector3> &);
