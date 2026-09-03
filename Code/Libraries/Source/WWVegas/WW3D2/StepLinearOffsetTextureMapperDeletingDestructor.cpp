// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
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
