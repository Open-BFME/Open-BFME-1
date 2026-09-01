// cl: /DNDEBUG /MD /EHsc

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
