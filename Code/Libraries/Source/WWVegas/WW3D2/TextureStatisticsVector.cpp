// cl: /DNDEBUG

// The retail BFME statistics implementation uses DynamicVectorClass here,
// while the later Zero Hour source uses SimpleDynVecClass.  Keep the template
// declarations local so the original out-of-line VectorClass constructor call
// is preserved by the compiler.

class TextureClass;

struct TextureStatisticsStruct
{
	TextureClass *tex;
	int usage_count;
	int change_count;

	bool operator==(TextureStatisticsStruct const &other) const
	{
		return tex == other.tex;
	}
};

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	virtual ~VectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
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
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
	: VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

template DynamicVectorClass<TextureStatisticsStruct>::DynamicVectorClass(
	unsigned, TextureStatisticsStruct const *);
