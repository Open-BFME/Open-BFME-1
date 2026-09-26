// cl: /DNDEBUG /MD /EHsc

struct TextureStatisticsStruct;

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<TextureStatisticsStruct>;

void Force_DynamicVectorTextureStatistics_Deleting_Destructor(DynamicVectorClass<TextureStatisticsStruct> *vector)
{
	delete vector;
}
