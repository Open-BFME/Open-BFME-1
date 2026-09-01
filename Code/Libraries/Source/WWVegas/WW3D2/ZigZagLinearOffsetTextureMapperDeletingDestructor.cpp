// cl: /DNDEBUG /MD /EHsc

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
