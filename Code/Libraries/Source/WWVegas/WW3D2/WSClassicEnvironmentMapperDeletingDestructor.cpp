// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class WSClassicEnvironmentMapperClass
{
public:
	virtual ~WSClassicEnvironmentMapperClass();
};

__declspec(noinline) WSClassicEnvironmentMapperClass::~WSClassicEnvironmentMapperClass() {}

void Force_WSClassicEnvironmentMapper_Deleting_Destructor(
	WSClassicEnvironmentMapperClass *mapper)
{
	delete mapper;
}
