// cl: /DNDEBUG /MD /EHsc

class RotateTextureMapperClass
{
public:
    virtual ~RotateTextureMapperClass();
};

__declspec(noinline) RotateTextureMapperClass::~RotateTextureMapperClass() {}

void Force_RotateTextureMapper_Deleting_Destructor(RotateTextureMapperClass *mapper)
{
    delete mapper;
}
