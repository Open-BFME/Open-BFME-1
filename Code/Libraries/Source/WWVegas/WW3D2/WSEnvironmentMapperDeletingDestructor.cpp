// cl: /DNDEBUG /MD /EHsc

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
