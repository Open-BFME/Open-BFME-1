// cl: /DNDEBUG /MD /EHsc

class TexBufferClass
{
public:
	virtual ~TexBufferClass();
};

__declspec(noinline) TexBufferClass::~TexBufferClass() {}

void Force_TexBuffer_Deleting_Destructor(TexBufferClass *buffer)
{
	delete buffer;
}
