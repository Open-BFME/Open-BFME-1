// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: Render2DClass scalar-deleting destructor at retail
// 0x006E7C30 (30 bytes).  The matched Render2DClass constructor at
// 0x00937060 and complete destructor at 0x00936E90 establish the identity.

class Render2DClass
{
public:
	~Render2DClass();
};

void forceRender2DClassDeletingDestructor(Render2DClass *value)
{
	delete value;
}
