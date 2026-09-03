// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
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
