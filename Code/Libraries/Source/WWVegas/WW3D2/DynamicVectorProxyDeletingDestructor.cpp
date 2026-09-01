// cl: /DNDEBUG /MD /EHsc

class ProxyClass;

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<ProxyClass>;

void Force_DynamicVectorProxy_Deleting_Destructor(DynamicVectorClass<ProxyClass> *vector)
{
	delete vector;
}
