// cl: /DNDEBUG /MD /EHsc

class Vector4;

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<Vector4>;

void Force_DynamicVectorVector4_Deleting_Destructor(DynamicVectorClass<Vector4> *vector)
{
	delete vector;
}
