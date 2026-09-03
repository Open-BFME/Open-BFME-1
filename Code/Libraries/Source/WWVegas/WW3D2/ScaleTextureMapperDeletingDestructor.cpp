// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class ScaleTextureMapperClass
{
public:
    virtual ~ScaleTextureMapperClass();
};

__declspec(noinline) ScaleTextureMapperClass::~ScaleTextureMapperClass() {}

void Force_ScaleTextureMapper_Deleting_Destructor(ScaleTextureMapperClass *mapper)
{
    delete mapper;
}
