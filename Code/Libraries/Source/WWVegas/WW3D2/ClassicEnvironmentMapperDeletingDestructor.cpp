// cl: /DNDEBUG /MD /EHsc

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
