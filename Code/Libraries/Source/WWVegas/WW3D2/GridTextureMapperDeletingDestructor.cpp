// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridTextureMapperClass
{
public:
    virtual ~GridTextureMapperClass();
};

__declspec(noinline) GridTextureMapperClass::~GridTextureMapperClass() {}

void Force_GridTextureMapper_Deleting_Destructor(GridTextureMapperClass *mapper)
{
    delete mapper;
}
