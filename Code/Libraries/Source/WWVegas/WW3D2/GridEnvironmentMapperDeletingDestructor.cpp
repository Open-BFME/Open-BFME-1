// cl: /DNDEBUG /MD /EHsc

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
