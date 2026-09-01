// cl: /DNDEBUG /MD /EHsc

class ShaderClass;

template <class T> class VectorClass
{
public:
	virtual ~VectorClass();
};

template <class T> __declspec(noinline) VectorClass<T>::~VectorClass() {}

template class VectorClass<ShaderClass>;

void Force_VectorShader_Deleting_Destructor(VectorClass<ShaderClass> *vector)
{
	delete vector;
}
