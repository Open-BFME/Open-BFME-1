// cl: /DNDEBUG /MD /EHsc

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
