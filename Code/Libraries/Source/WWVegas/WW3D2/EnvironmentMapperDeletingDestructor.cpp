// cl: /DNDEBUG /MD /EHsc

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
