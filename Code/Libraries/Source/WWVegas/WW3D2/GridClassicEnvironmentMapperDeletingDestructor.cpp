// cl: /DNDEBUG /MD /EHsc

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
