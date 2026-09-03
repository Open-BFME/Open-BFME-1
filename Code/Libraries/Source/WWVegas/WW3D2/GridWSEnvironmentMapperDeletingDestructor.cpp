// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridWSEnvironmentMapperClass
{
public:
    virtual ~GridWSEnvironmentMapperClass();
};

__declspec(noinline) GridWSEnvironmentMapperClass::~GridWSEnvironmentMapperClass() {}

void Force_GridWSEnvironmentMapper_Deleting_Destructor(
    GridWSEnvironmentMapperClass *mapper)
{
    delete mapper;
}
