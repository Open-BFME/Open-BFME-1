// cl: /DNDEBUG /MD /EHsc

class WSEnvMapperClass
{
public:
    virtual ~WSEnvMapperClass();
};

__declspec(noinline) WSEnvMapperClass::~WSEnvMapperClass() {}

void Force_WSEnvMapper_Deleting_Destructor(WSEnvMapperClass *mapper)
{
    delete mapper;
}
