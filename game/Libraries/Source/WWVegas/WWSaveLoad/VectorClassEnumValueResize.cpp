// cl: /DNDEBUG /MD /EHsc
//
// Named DynamicVectorClass<EnumParameterClass::_ENUM_VALUE>::Resize at
// 0x0093E700 is a byte-true call to this VectorClass::Resize. The copy loop
// addRef/releases the record's second word, which is why the element is not
// spelled from parameter.h's StringClass+int layout.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

class Rva0093E4D0SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class Rva0093E4D0Surface
{
public:
	Rva0093E4D0Surface() : m_surface(0) {}
	~Rva0093E4D0Surface();

	Rva0093E4D0Surface &operator=(const Rva0093E4D0Surface &that)
	{
		if (that.m_surface)
			that.m_surface->addRef();
		if (m_surface)
			m_surface->release();
		m_surface = that.m_surface;
		return *this;
	}

private:
	Rva0093E4D0SurfaceResource *m_surface;
};

class EnumParameterClass
{
public:
	struct _ENUM_VALUE
	{
		_ENUM_VALUE();
		~_ENUM_VALUE();

		_ENUM_VALUE &operator=(const _ENUM_VALUE &that)
		{
			m_first = that.m_first;
			m_surface = that.m_surface;
			return *this;
		}

		void *m_first;
		Rva0093E4D0Surface m_surface;
	};
};

template <class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass(void);
	virtual bool equal(const VectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int id(T const *ptr);
	virtual int id(T const &ptr);

protected:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_padding[2];
};

template <class T>
VectorClass<T>::VectorClass(int size, T const *array)
	: m_vector(0), m_vectorMax(size), m_isValid(true), m_isAllocated(false)
{
	if (size)
	{
		if (array)
			m_vector = new ((void *)array) T[size];
		else
		{
			m_vector = new T[size];
			m_isAllocated = true;
		}
	}
}

template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;

		m_isValid = false;
		if (!array)
			newptr = new T[newsize];
		else
			newptr = new ((void *)array) T[newsize];
		m_isValid = true;
		if (!newptr)
			return false;

		if (m_vector != 0)
		{
			int copycount = (newsize < m_vectorMax) ? newsize : m_vectorMax;
			for (int index = 0; index < copycount; ++index)
				newptr[index] = m_vector[index];

			if (m_isAllocated)
			{
				delete[] m_vector;
				m_vector = 0;
			}
		}

		m_vector = newptr;
		m_vectorMax = newsize;
		m_isAllocated = (m_vector && !array);
	}
	else
		Clear();

	return true;
}

template bool VectorClass<EnumParameterClass::_ENUM_VALUE>::Resize(
	int, EnumParameterClass::_ENUM_VALUE const *);
