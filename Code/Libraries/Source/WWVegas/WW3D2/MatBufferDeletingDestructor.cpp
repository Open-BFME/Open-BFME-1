// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
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
