// cl: /DNDEBUG
// Near-twin of DynamicVectorClass<TextureStatisticsStruct>'s VectorClass
// base constructor (0x009374A0, 194B,
// Code/Libraries/Source/WWVegas/WW3D2/TextureStatisticsVector.cpp) at
// 0x0093DA80 (194B). Byte-identical except the element type is 0x24 (36)
// bytes instead of 0xC (12): a fresh, wider payload with the same
// non-trivial-ctor/dtor shape (a single RefCountPtr-like sub-object) so the
// compiler still emits the array-constructor-iterator call. Fresh tags per
// NEAR-TWIN policy; identity of the owning vector/class is NOT recovered.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

class TextureBaseClassWide
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClassWide : public TextureBaseClassWide
{
};

void TextureBaseClassWide::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
class RefCountPtrWide
{
public:
	RefCountPtrWide() : Referent(0) {}
	RefCountPtrWide(RefCountPtrWide const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	~RefCountPtrWide()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	RefCountPtrWide const &operator=(RefCountPtrWide const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	void Clear()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	bool operator==(RefCountPtrWide const &other) const { return Referent == other.Referent; }
	bool operator!=(RefCountPtrWide const &other) const { return Referent != other.Referent; }

private:
	T *Referent;
};

struct TextureStatisticsStructWide
{
	RefCountPtrWide<TextureClassWide> tex;
	int usage_count;
	int change_count;
	int unmodelled[6];

	bool operator==(TextureStatisticsStructWide const &other) const
	{
		return tex == other.tex;
	}
	bool operator!=(TextureStatisticsStructWide const &other) const
	{
		return tex != other.tex;
	}
};

template<class T>
class VectorClassWide
{
public:
	VectorClassWide(unsigned size, T const *array);
	VectorClassWide(VectorClassWide const &);
	virtual ~VectorClassWide();
	VectorClassWide &operator=(VectorClassWide const &);
	virtual bool operator==(VectorClassWide const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClassWide : public VectorClassWide<T>
{
public:
	DynamicVectorClassWide(unsigned size = 0, T const *array = 0);
	virtual ~DynamicVectorClassWide();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	bool Add(T const &object);

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
VectorClassWide<T>::VectorClassWide(unsigned size, T const *array)
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
bool VectorClassWide<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;
		IsValid = false;
		if (!array)
		{
			newptr = new T[newsize];
		}
		else
		{
			newptr = new ((void *)array) T[newsize];
		}
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

template<class T>
VectorClassWide<T>::~VectorClassWide()
{
	VectorClassWide<T>::Clear();
}

template<class T>
int VectorClassWide<T>::ID(T const &object)
{
	if (!IsValid)
		return 0;

	for (int index = 0; index < VectorMax; ++index)
	{
		if ((*this)[index] == object)
			return index;
	}
	return -1;
}

template<class T>
void VectorClassWide<T>::Clear()
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
void DynamicVectorClassWide<T>::Clear()
{
	ActiveCount = 0;
	VectorClassWide<T>::Clear();
}

template<class T>
bool DynamicVectorClassWide<T>::Resize(int newsize, T const *array)
{
	if (VectorClassWide<T>::Resize(newsize, array))
	{
		if (this->Length() < ActiveCount)
			ActiveCount = this->Length();
		return true;
	}
	return false;
}

template<class T>
bool DynamicVectorClassWide<T>::Add(T const &object)
{
	if (ActiveCount >= this->Length())
	{
		if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0)
		{
			if (!Resize(this->Length() + GrowthStep))
				return false;
		}
		else
		{
			return false;
		}
	}
	(*this)[ActiveCount++] = object;
	return true;
}

template<class T>
DynamicVectorClassWide<T>::DynamicVectorClassWide(unsigned size, T const *array)
	: VectorClassWide<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

template DynamicVectorClassWide<TextureStatisticsStructWide>::DynamicVectorClassWide(
	unsigned, TextureStatisticsStructWide const *);
template VectorClassWide<TextureStatisticsStructWide>::VectorClassWide(
	unsigned, TextureStatisticsStructWide const *);
template bool VectorClassWide<TextureStatisticsStructWide>::Resize(
	int, TextureStatisticsStructWide const *);
template int VectorClassWide<TextureStatisticsStructWide>::ID(
	TextureStatisticsStructWide const &);
template void DynamicVectorClassWide<TextureStatisticsStructWide>::Clear();
template bool DynamicVectorClassWide<TextureStatisticsStructWide>::Add(
	TextureStatisticsStructWide const &);
template VectorClassWide<TextureStatisticsStructWide>::~VectorClassWide();

static DynamicVectorClassWide<TextureStatisticsStructWide> texture_statistics_wide;

void Record_Texture_Wide_Begin()
{
	texture_statistics_wide.Resize(0);
}
