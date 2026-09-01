// cl: /DNDEBUG /MD /EHsc

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
