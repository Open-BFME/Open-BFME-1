// cl: /DNDEBUG /MD /EHsc

class BumpEnvTextureMapperClass
{
public:
    virtual ~BumpEnvTextureMapperClass();
};

__declspec(noinline) BumpEnvTextureMapperClass::~BumpEnvTextureMapperClass() {}

void Force_BumpEnvTextureMapper_Deleting_Destructor(BumpEnvTextureMapperClass *mapper)
{
    delete mapper;
}
