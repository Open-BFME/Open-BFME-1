// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h
class WSEnvMapperClass
{
public:
    virtual ~WSEnvMapperClass();
};

__declspec(noinline) WSEnvMapperClass::~WSEnvMapperClass() {}

void Force_WSEnvMapper_Deleting_Destructor(WSEnvMapperClass *mapper)
{
    delete mapper;
}
