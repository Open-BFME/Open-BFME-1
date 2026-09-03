// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class ZigZagLinearOffsetTextureMapperClass
{
public:
    virtual ~ZigZagLinearOffsetTextureMapperClass();
};

__declspec(noinline) ZigZagLinearOffsetTextureMapperClass::~ZigZagLinearOffsetTextureMapperClass() {}

void Force_ZigZagLinearOffsetTextureMapper_Deleting_Destructor(
    ZigZagLinearOffsetTextureMapperClass *mapper)
{
    delete mapper;
}
