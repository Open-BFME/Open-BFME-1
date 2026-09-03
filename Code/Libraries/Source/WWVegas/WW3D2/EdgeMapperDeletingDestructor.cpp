// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
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
