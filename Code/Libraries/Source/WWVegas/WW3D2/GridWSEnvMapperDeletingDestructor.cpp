// cl: /DNDEBUG /MD /EHsc

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
