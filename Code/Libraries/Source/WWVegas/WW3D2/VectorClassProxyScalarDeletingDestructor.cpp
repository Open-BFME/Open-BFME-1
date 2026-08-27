// BFME's ProxyClass vector specialization is emitted in a translation unit
// whose original source is unavailable.  These declarations preserve the
// retail object sizes and virtual ordering needed by the compiler-generated
// scalar-deleting destructor at 0x00936DE0.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

class StringClass
{
public:
	char *m_Buffer;
};

class Matrix3D
{
public:
	float Row[3][4];
};

class ProxyClass
{
public:
	ProxyClass();
	~ProxyClass();
	ProxyClass &operator=(ProxyClass const &);

	StringClass Name;
	Matrix3D Transform;
	unsigned char UnreconstructedTail[0x74 - 0x34];
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClass<T>::VectorClass(int size, T const *array)
	: Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
}

template<class T>
VectorClass<T>::~VectorClass()
{
	if (Vector != 0 && IsAllocated)
	{
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template class VectorClass<ProxyClass>;

void ForceProxyVectorVtable()
{
	VectorClass<ProxyClass> value;
}
