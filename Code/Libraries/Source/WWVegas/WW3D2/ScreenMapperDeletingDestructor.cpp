// cl: /DNDEBUG /MD /EHsc

class ScreenMapperClass
{
public:
    virtual ~ScreenMapperClass();
};

__declspec(noinline) ScreenMapperClass::~ScreenMapperClass() {}

void Force_ScreenMapper_Deleting_Destructor(ScreenMapperClass *mapper)
{
    delete mapper;
}
