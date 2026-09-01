// cl: /DNDEBUG /MD /EHsc

class ScaleTextureMapperClass
{
public:
    virtual ~ScaleTextureMapperClass();
};

__declspec(noinline) ScaleTextureMapperClass::~ScaleTextureMapperClass() {}

void Force_ScaleTextureMapper_Deleting_Destructor(ScaleTextureMapperClass *mapper)
{
    delete mapper;
}
