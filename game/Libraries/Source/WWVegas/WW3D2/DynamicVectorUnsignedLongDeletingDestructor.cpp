// cl: /DNDEBUG /MD /EHsc

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<unsigned long>;

void Force_DynamicVectorUnsignedLong_Deleting_Destructor(DynamicVectorClass<unsigned long> *vector)
{
	delete vector;
}
