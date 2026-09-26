// cl: /DNDEBUG /MD /EHsc

class ShaderClass;

template <class T> class ShareBufferClass
{
public:
	virtual ~ShareBufferClass();
};

template <class T> __declspec(noinline) ShareBufferClass<T>::~ShareBufferClass() {}

template class ShareBufferClass<ShaderClass>;

void Force_ShareBufferShader_Deleting_Destructor(ShareBufferClass<ShaderClass> *buffer)
{
	delete buffer;
}
