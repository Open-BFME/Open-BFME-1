// cl: /DNDEBUG /MD /EHsc

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
};

__declspec(noinline) SimpleSceneClass::~SimpleSceneClass() {}

void Force_SimpleScene_Deleting_Destructor(SimpleSceneClass *scene)
{
	delete scene;
}
