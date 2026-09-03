// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class RotateTextureMapperClass
{
public:
    virtual ~RotateTextureMapperClass();
};

__declspec(noinline) RotateTextureMapperClass::~RotateTextureMapperClass() {}

void Force_RotateTextureMapper_Deleting_Destructor(RotateTextureMapperClass *mapper)
{
    delete mapper;
}
