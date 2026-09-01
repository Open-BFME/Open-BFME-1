// cl: /DNDEBUG /MD /EHsc

class StepLinearOffsetTextureMapperClass
{
public:
    virtual ~StepLinearOffsetTextureMapperClass();
};

__declspec(noinline) StepLinearOffsetTextureMapperClass::~StepLinearOffsetTextureMapperClass() {}

void Force_StepLinearOffsetTextureMapper_Deleting_Destructor(
    StepLinearOffsetTextureMapperClass *mapper)
{
    delete mapper;
}
