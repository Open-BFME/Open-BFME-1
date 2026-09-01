// cl: /DNDEBUG /MD /EHsc

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
