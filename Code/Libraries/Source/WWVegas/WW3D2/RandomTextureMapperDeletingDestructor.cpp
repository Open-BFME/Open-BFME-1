// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
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
