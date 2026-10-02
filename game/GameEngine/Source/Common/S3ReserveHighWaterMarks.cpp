// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WW3D2 /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWMath

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer) throw();

class ShaderClass
{
public:
	__forceinline ShaderClass() : ShaderBits(0x0010441b) {}

	__forceinline ShaderClass &operator=(ShaderClass const &value)
	{
		ShaderBits = value.ShaderBits;
		return *this;
	}

	__forceinline bool operator==(ShaderClass const &value) const
	{
		return ShaderBits == value.ShaderBits;
	}

	__forceinline bool operator!=(ShaderClass const &value) const
	{
		return ShaderBits != value.ShaderBits;
	}

private:
	unsigned int ShaderBits;
};

template <class T> class VectorClass
{
public:
	virtual ~VectorClass();
	virtual bool operator==(VectorClass<T> const &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;

		IsValid = false;
		if (!array)
			newptr = new T[newsize];
		else
			newptr = new ((void *)array) T[newsize];
		IsValid = true;
		if (!newptr)
			return false;

		if (Vector != 0)
		{
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; ++index)
				newptr[index] = Vector[index];

			if (IsAllocated)
			{
				delete [] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);
	}
	else
	{
		Clear();
	}

	return true;
}

	template bool VectorClass<ShaderClass>::Resize(int, ShaderClass const *);

// WWMath Vector4, forward declaration only: the element type is never
// dereferenced here, it only has to carry its own name into the mangling.
// The real class is declared in game/Libraries/Source/WWVegas/WWMath/vector4.h;
// this header is not included because the TU's own VectorClass<T> (above)
// already occupies the name.

// Declared, never defined here: retail 0x009131E0 (550 bytes) is
// ?Resize@?$VectorClass@VVector4@@@@UAE_NHPBVVector4@@@Z, the already-matched
// body carried by
// game/Libraries/Source/WWVegas/WWLib/VectorClassResizeNothrowDelete.cpp.
// An explicit specialization declaration keeps this TU from emitting a second
// copy of it and binds every call below to that retail body.
class Vector4;
template <> bool VectorClass<Vector4>::Resize(int newsize, Vector4 const *array);

// Six 47-byte bodies with one shape:
//
//     if (!allocate(a, b)) return false;
//     if (m_0008 < m_0010) m_0010 = m_0008;
//     return true;
//
// The callee takes both arguments back in the order they arrived and runs with
// ecx untouched, so it is a member of the same class. test al,al says it hands
// back a byte, and the two exits set al alone, so these return a byte-wide
// bool as well. The compare is jge-skips, which is a less-than that lowers a
// high-water mark at +0x10 to the value at +0x08.
//
// The success path has to be written inside the if, with the plain return
// false last. Written the other way round -- an early return on failure --
// MSVC notices the callee already left zero in al, drops the xor entirely and
// puts the exit inline, which is two bytes short.
//
// One of the six callees is named: 0x0003FC7E is ShadowPool::allocate(int, int)
// returning bool, which fixes the argument types for all of them. The other
// five are known only by address and are pinned here.

class Gen_007b9e80
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x0003FC7E

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_009073d0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x00905DC0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

class Gen_00930d00 : public VectorClass<ShaderClass>
{
public:
	bool bfmeReserve(int first, int second);
	int m_bfme0010;							// +0x10
};

class Gen_009408d0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x00940450

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

// Retail 0x0094E310 lowers a high-water mark held at +0x10 to the element
// count at +0x08 once the vector has been resized. That offset pair is the
// VectorClass<T> layout itself (VectorMax at +0x08, the base ends at 0x10),
// and the call it makes goes to retail 0x009131E0 --
// ?Resize@?$VectorClass@VVector4@@@@UAE_NHPBVVector4@@@Z -- so this is a
// VectorClass<Vector4> whose member resizes itself in place. Same shape as
// Gen_00930d00 below, with VVector4 in place of VShaderClass.
class Gen_0094e310 : public VectorClass<Vector4>
{
public:
	bool bfmeReserve(int first, int second);

	int m_bfme0010;							// +0x10
};

class Gen_0097c8e0
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x0097ADF0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	int m_bfme0010;							// +0x10
};

// ?bfmeReserve@Gen_007b9e80@@QAE_NHH@Z
bool Gen_007b9e80::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_009073d0@@QAE_NHH@Z
bool Gen_009073d0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_00930d00@@QAE_NHH@Z
bool Gen_00930d00::bfmeReserve(int first, int second)
{
	if (VectorClass<ShaderClass>::Resize(first, (ShaderClass const *)second))
	{
		if (VectorMax < m_bfme0010)
			m_bfme0010 = VectorMax;

		return true;
	}

	return false;
}
// ?bfmeReserve@Gen_009408d0@@QAE_NHH@Z
bool Gen_009408d0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_0094e310@@QAE_NHH@Z
bool Gen_0094e310::bfmeReserve(int first, int second)
{
	if (VectorClass<Vector4>::Resize(first, (Vector4 const *)second))
	{
		if (VectorMax < m_bfme0010)
			m_bfme0010 = VectorMax;

		return true;
	}

	return false;
}

// ?bfmeReserve@Gen_0097c8e0@@QAE_NHH@Z
bool Gen_0097c8e0::bfmeReserve(int first, int second)
{
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

		return true;
	}

	return false;
}
