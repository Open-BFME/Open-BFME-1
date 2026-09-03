// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/boxrobj.h
class OBBoxRenderObjClass
{
public:
	virtual ~OBBoxRenderObjClass();
};

__declspec(noinline) OBBoxRenderObjClass::~OBBoxRenderObjClass() {}

void Force_OBBoxRenderObj_Deleting_Destructor(OBBoxRenderObjClass *box)
{
	delete box;
}
