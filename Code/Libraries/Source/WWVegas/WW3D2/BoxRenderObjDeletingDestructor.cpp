// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/boxrobj.h
class BoxRenderObjClass
{
public:
	virtual ~BoxRenderObjClass();
};

__declspec(noinline) BoxRenderObjClass::~BoxRenderObjClass() {}

void Force_BoxRenderObj_Deleting_Destructor(BoxRenderObjClass *box)
{
	delete box;
}
