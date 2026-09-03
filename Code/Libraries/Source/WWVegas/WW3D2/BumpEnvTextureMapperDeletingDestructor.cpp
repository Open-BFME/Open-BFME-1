// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
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
