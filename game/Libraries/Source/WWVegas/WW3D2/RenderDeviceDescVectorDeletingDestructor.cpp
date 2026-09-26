// cl: /DNDEBUG /MD /EHsc

class RenderDeviceDescClass;

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T> __declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass() {}

template class DynamicVectorClass<RenderDeviceDescClass>;

void Force_RenderDeviceDesc_Vector_Deleting_Destructor(DynamicVectorClass<RenderDeviceDescClass> *vector)
{
	delete vector;
}
