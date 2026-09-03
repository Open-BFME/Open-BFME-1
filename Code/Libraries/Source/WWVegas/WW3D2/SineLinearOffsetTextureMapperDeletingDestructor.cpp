// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class SineLinearOffsetTextureMapperClass
{
public:
    virtual ~SineLinearOffsetTextureMapperClass();
};

__declspec(noinline) SineLinearOffsetTextureMapperClass::~SineLinearOffsetTextureMapperClass() {}

void Force_SineLinearOffsetTextureMapper_Deleting_Destructor(
    SineLinearOffsetTextureMapperClass *mapper)
{
    delete mapper;
}
