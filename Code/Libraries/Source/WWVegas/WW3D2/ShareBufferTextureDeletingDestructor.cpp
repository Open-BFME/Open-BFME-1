// cl: /DNDEBUG /MD /EHsc

class TextureClass;

template <class T> class ShareBufferClass
{
public:
	virtual ~ShareBufferClass();
};

template <class T> __declspec(noinline) ShareBufferClass<T>::~ShareBufferClass() {}

template class ShareBufferClass<TextureClass *>;

void Force_ShareBufferTexture_Deleting_Destructor(ShareBufferClass<TextureClass *> *buffer)
{
	delete buffer;
}
