// cl: /DNDEBUG /MD /EHsc

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
