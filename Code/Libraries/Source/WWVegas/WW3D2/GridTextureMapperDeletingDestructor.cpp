// cl: /DNDEBUG /MD /EHsc

class GridTextureMapperClass
{
public:
    virtual ~GridTextureMapperClass();
};

__declspec(noinline) GridTextureMapperClass::~GridTextureMapperClass() {}

void Force_GridTextureMapper_Deleting_Destructor(GridTextureMapperClass *mapper)
{
    delete mapper;
}
