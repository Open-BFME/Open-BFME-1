// cl: /DNDEBUG /MD /EHsc

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
