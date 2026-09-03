// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
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
