// cl: /DNDEBUG

// The retail BFME statistics implementation uses DynamicVectorClass here,
// while the later Zero Hour source uses SimpleDynVecClass.  Keep the template
// declarations local so the original out-of-line VectorClass constructor call
// is preserved by the compiler.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	bool operator==(RefCountPtr const &other) const { return Referent == other.Referent; }
	bool operator!=(RefCountPtr const &other) const { return Referent != other.Referent; }

private:
	T *Referent;
};

struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;

	bool operator==(TextureStatisticsStruct const &other) const
	{
		return tex == other.tex;
	}
	bool operator!=(TextureStatisticsStruct const &other) const
	{
		return tex != other.tex;
	}
};

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	VectorClass(VectorClass const &);
	virtual ~VectorClass();
	VectorClass &operator=(VectorClass const &);
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
VectorClass<T>::VectorClass(unsigned size, T const *array)
	: Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	if (size)
	{
		if (array)
		{
			Vector = new ((void *)array) T[size];
		}
		else
		{
			Vector = new T[size];
			IsAllocated = true;
		}
	}
}

template<class T>
VectorClass<T>::~VectorClass()
{
	VectorClass<T>::Clear();
}

template<class T>
void VectorClass<T>::Clear()
{
	if (Vector != 0 && IsAllocated)
	{
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template<class T>
void DynamicVectorClass<T>::Clear()
{
	ActiveCount = 0;
	VectorClass<T>::Clear();
}

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
	: VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

template DynamicVectorClass<TextureStatisticsStruct>::DynamicVectorClass(
	unsigned, TextureStatisticsStruct const *);
template VectorClass<TextureStatisticsStruct>::VectorClass(
	unsigned, TextureStatisticsStruct const *);
template void DynamicVectorClass<TextureStatisticsStruct>::Clear();
template VectorClass<TextureStatisticsStruct>::~VectorClass();
