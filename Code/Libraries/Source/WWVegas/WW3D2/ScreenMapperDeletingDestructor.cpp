// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
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
