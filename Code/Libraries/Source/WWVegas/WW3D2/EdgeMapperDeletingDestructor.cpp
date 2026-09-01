// cl: /DNDEBUG /MD /EHsc

class EdgeMapperClass
{
public:
    virtual ~EdgeMapperClass();
};

__declspec(noinline) EdgeMapperClass::~EdgeMapperClass() {}

void Force_EdgeMapper_Deleting_Destructor(EdgeMapperClass *mapper)
{
    delete mapper;
}
