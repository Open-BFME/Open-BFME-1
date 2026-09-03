// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class LinearOffsetTextureMapperClass
{
public:
    virtual ~LinearOffsetTextureMapperClass();
};

__declspec(noinline) LinearOffsetTextureMapperClass::~LinearOffsetTextureMapperClass() {}

void Force_LinearOffsetTextureMapper_Deleting_Destructor(
    LinearOffsetTextureMapperClass *mapper)
{
    delete mapper;
}
