// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridWSClassicEnvironmentMapperClass
{
public:
    virtual ~GridWSClassicEnvironmentMapperClass();
};

__declspec(noinline) GridWSClassicEnvironmentMapperClass::~GridWSClassicEnvironmentMapperClass() {}

void Force_GridWSClassicEnvironmentMapper_Deleting_Destructor(
    GridWSClassicEnvironmentMapperClass *mapper)
{
    delete mapper;
}
