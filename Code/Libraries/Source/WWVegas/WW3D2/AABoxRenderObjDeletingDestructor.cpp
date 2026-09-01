// cl: /DNDEBUG /MD /EHsc

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
