// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridEnvironmentMapperClass
{
public:
    virtual ~GridEnvironmentMapperClass();
};

__declspec(noinline) GridEnvironmentMapperClass::~GridEnvironmentMapperClass() {}

void Force_GridEnvironmentMapper_Deleting_Destructor(GridEnvironmentMapperClass *mapper)
{
    delete mapper;
}
