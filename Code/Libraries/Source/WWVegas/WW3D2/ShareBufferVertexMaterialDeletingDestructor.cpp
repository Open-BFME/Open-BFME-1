// cl: /DNDEBUG /MD /EHsc

class VertexMaterialClass;

template <class T> class ShareBufferClass
{
public:
	virtual ~ShareBufferClass();
};

template <class T> __declspec(noinline) ShareBufferClass<T>::~ShareBufferClass() {}

template class ShareBufferClass<VertexMaterialClass *>;

void Force_ShareBufferVertexMaterial_Deleting_Destructor(ShareBufferClass<VertexMaterialClass *> *buffer)
{
	delete buffer;
}
