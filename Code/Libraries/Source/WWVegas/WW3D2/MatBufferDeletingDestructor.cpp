// cl: /DNDEBUG /MD /EHsc

class MatBufferClass
{
public:
	virtual ~MatBufferClass();
};

__declspec(noinline) MatBufferClass::~MatBufferClass() {}

void Force_MatBuffer_Deleting_Destructor(MatBufferClass *buffer)
{
	delete buffer;
}
