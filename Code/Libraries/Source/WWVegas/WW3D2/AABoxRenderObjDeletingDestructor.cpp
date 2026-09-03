// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/boxrobj.h
class AABoxRenderObjClass
{
public:
	virtual ~AABoxRenderObjClass();
};

__declspec(noinline) AABoxRenderObjClass::~AABoxRenderObjClass() {}

void Force_AABoxRenderObj_Deleting_Destructor(AABoxRenderObjClass *box)
{
	delete box;
}
