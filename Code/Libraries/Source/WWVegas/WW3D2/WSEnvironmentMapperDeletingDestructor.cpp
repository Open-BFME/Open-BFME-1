// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class WSEnvironmentMapperClass
{
public:
	virtual ~WSEnvironmentMapperClass();
};

__declspec(noinline) WSEnvironmentMapperClass::~WSEnvironmentMapperClass() {}

void Force_WSEnvironmentMapper_Deleting_Destructor(WSEnvironmentMapperClass *mapper)
{
	delete mapper;
}
