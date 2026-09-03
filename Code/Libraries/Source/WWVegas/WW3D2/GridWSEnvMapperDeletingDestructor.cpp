// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class GridWSEnvMapperClass
{
public:
    virtual ~GridWSEnvMapperClass();
};

__declspec(noinline) GridWSEnvMapperClass::~GridWSEnvMapperClass() {}

void Force_GridWSEnvMapper_Deleting_Destructor(GridWSEnvMapperClass *mapper)
{
    delete mapper;
}
