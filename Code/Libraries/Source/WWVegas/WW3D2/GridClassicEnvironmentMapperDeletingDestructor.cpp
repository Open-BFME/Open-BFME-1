// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridClassicEnvironmentMapperClass
{
public:
    virtual ~GridClassicEnvironmentMapperClass();
};

__declspec(noinline) GridClassicEnvironmentMapperClass::~GridClassicEnvironmentMapperClass() {}

void Force_GridClassicEnvironmentMapper_Deleting_Destructor(
    GridClassicEnvironmentMapperClass *mapper)
{
    delete mapper;
}
