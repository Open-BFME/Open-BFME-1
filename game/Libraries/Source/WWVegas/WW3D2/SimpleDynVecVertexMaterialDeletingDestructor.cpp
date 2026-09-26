// cl: /DNDEBUG /MD /EHsc

class VertexMaterialClass;

template <class T> class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
};

template <class T> __declspec(noinline) SimpleDynVecClass<T>::~SimpleDynVecClass() {}

template class SimpleDynVecClass<VertexMaterialClass *>;

void Force_SimpleDynVecVertexMaterial_Deleting_Destructor(SimpleDynVecClass<VertexMaterialClass *> *vector)
{
	delete vector;
}
