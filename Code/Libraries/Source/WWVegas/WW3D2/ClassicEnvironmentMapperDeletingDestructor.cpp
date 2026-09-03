// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class ClassicEnvironmentMapperClass
{
public:
	virtual ~ClassicEnvironmentMapperClass();
};

__declspec(noinline) ClassicEnvironmentMapperClass::~ClassicEnvironmentMapperClass() {}

void Force_ClassicEnvironmentMapper_Deleting_Destructor(
	ClassicEnvironmentMapperClass *mapper)
{
	delete mapper;
}
