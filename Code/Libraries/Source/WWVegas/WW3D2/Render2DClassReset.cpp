// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME's Render2D layout predates the later vendored class. Keep the retail
// layout and nonvirtual Reset ABI local to this translation unit.

class TextureBaseClass
{
public:
	void Add_Ref() { ++RefCount; }
	void Release_Ref();

	int Unknown00;
	unsigned short RefCount;
	unsigned short Unknown06;
};

class Render2DRawArray
{
public:
	void Reset_Active() { Count = 0; }

	void *Data;
	int Size;
	int Count;
	int GrowthStep;
};

class ProxyClass
{
public:
	__forceinline ProxyClass();
	__forceinline void Initialize();
	__forceinline ~ProxyClass()
	{
		if (Texture)
			Texture->Release_Ref();
	}
	ProxyClass &operator=(ProxyClass const &other);

	TextureBaseClass *Texture;
	int Field04;
	int Field08;
	int Field0C;
	int Field10;
	int Field14;
	int Field18;
	int Field1C;
	int Field20;
	int Field24;
	int Field28;
	int Field2C;
	int Field30;
	int Field34;
	int Field38;
	int Field3C;
	int Field40;
	int Field44;
	int Field48;
	int Field4C;
	int Field50;
	int Field54;
	int Field58;
	int Field5C;
	int Field60;
	int Field64;
	int Field68;
	int Field6C;
	int Field70;
};

__forceinline ProxyClass::ProxyClass()
{
	Texture = 0;
}

__forceinline void ProxyClass::Initialize()
{
	Field20 = -1;
	Field3C = -1;
	Field04 = -1;
	Field24 = -1;
	Field40 = -1;
	Field08 = -1;
	Field28 = -1;
	Field44 = -1;
	Field0C = -1;
	Field2C = -1;
	Field48 = -1;
	Field10 = -1;
	Field30 = -1;
	Field4C = -1;
	Field14 = -1;
	Field34 = -1;
	Field50 = -1;
	Field18 = -1;
	Field38 = -1;
	Field54 = -1;
	Field1C = -1;
	Field58 = 0;
	Field5C = 0;
	Field60 = 0;
	Field64 = 0;
	Field68 = 0;
	Field6C = 0;
	Field70 = 0;
}

ProxyClass &ProxyClass::operator=(ProxyClass const &other)
{
	if (other.Texture)
		other.Texture->Add_Ref();
	if (Texture)
		Texture->Release_Ref();

	Texture = other.Texture;
	Field04 = other.Field04;
	Field08 = other.Field08;
	Field0C = other.Field0C;
	Field10 = other.Field10;
	Field14 = other.Field14;
	Field18 = other.Field18;
	Field1C = other.Field1C;
	Field20 = other.Field20;
	Field24 = other.Field24;
	Field28 = other.Field28;
	Field2C = other.Field2C;
	Field30 = other.Field30;
	Field34 = other.Field34;
	Field38 = other.Field38;
	Field3C = other.Field3C;
	Field40 = other.Field40;
	Field44 = other.Field44;
	Field48 = other.Field48;
	Field4C = other.Field4C;
	Field50 = other.Field50;
	Field54 = other.Field54;
	Field58 = other.Field58;
	Field5C = other.Field5C;
	Field60 = other.Field60;
	Field64 = other.Field64;
	Field68 = other.Field68;
	Field6C = other.Field6C;
	Field70 = other.Field70;
	return *this;
}

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

public:
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

	__forceinline bool Add(T const &object, int count)
	{
		if (count >= Length())
		{
			if ((IsAllocated || !VectorMax) && GrowthStep > 0)
			{
				if (!Resize(Length() + GrowthStep))
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

	int Count() const { return ActiveCount; }

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DClass
{
public:
	void Reset();

private:
	int Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	DynamicVectorClass<ProxyClass> Batches;
	TextureBaseClass *Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char Tail[3];
};

void Render2DClass::Reset()
{
	ArrayA.Reset_Active();
	ArrayB.Reset_Active();
	Batches.Clear();
	ProxyClass batch;
	DynamicVectorClass<ProxyClass> *batches = &Batches;
	int count = batches->Count();
	batch.Initialize();
	batches->Add(batch, count);
	CurrentBatch = Texture ? -1 : 0;
}
