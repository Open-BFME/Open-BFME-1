// cl: /DNDEBUG /MD /EHsc

class RandomTextureMapperClass
{
public:
    virtual ~RandomTextureMapperClass();
};

__declspec(noinline) RandomTextureMapperClass::~RandomTextureMapperClass() {}

void Force_RandomTextureMapper_Deleting_Destructor(RandomTextureMapperClass *mapper)
{
    delete mapper;
}
