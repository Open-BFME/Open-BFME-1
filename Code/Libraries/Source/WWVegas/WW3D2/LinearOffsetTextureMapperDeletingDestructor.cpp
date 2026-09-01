// cl: /DNDEBUG /MD /EHsc

class LinearOffsetTextureMapperClass
{
public:
    virtual ~LinearOffsetTextureMapperClass();
};

__declspec(noinline) LinearOffsetTextureMapperClass::~LinearOffsetTextureMapperClass() {}

void Force_LinearOffsetTextureMapper_Deleting_Destructor(
    LinearOffsetTextureMapperClass *mapper)
{
    delete mapper;
}
