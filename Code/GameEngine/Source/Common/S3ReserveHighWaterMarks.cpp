// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WW3D2 /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWMath

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer) throw();

class ShaderClass
{
public:
	__forceinline ShaderClass() : m_shaderBits(0x0010441b) {}

	__forceinline ShaderClass &operator=(ShaderClass const &value)
	{
		m_shaderBits = value.m_shaderBits;
		return *this;
	}

	__forceinline bool operator==(ShaderClass const &value) const
	{
		return m_shaderBits == value.m_shaderBits;
	}

	__forceinline bool operator!=(ShaderClass const &value) const
	{
		return m_shaderBits != value.m_shaderBits;
	}

private:
	unsigned int m_shaderBits;
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

class Gen_0094e310
{
public:
	bool bfmeReserve(int first, int second);

private:
	bool bfmeAllocate(int first, int second);			// retail 0x009131E0

	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	char m_bfmeMid[0x10 - 0x0C];
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
	if (bfmeAllocate(first, second))
	{
		if (m_bfme0008 < m_bfme0010)
			m_bfme0010 = m_bfme0008;

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
