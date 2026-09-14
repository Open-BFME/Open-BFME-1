// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SceneClass scalar-deleting destructor at retail RVA 0x009436A0.
// The matched constructor/destructor at 0x00942F30/0x00942F90 install vtable
// 0x0113CECC, whose Add/Remove_Render_Object and other SceneClass virtuals
// establish the base-scene identity independently of SimpleSceneClass.

class SceneClass
{
public:
	virtual ~SceneClass();
};

void forceSceneClassDeletingDestructor()
{
	SceneClass value;
}
