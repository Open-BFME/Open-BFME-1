// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class EnvironmentMapperClass
{
public:
	virtual ~EnvironmentMapperClass();
};

__declspec(noinline) EnvironmentMapperClass::~EnvironmentMapperClass() {}

void Force_EnvironmentMapper_Deleting_Destructor(EnvironmentMapperClass *mapper)
{
	delete mapper;
}
