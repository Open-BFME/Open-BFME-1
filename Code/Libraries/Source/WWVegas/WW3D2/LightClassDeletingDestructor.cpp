// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME5: LightClass's scalar-deleting destructor at retail RVA
// 0x0093BF90 (30 bytes). The LightClass constructors at 0x0093BE90 and
// 0x0093BFB0 install vtable 0x0113CBB8; its slot 1 is this wrapper. The
// complete destructor at 0x0093BE00 re-seats the LightClass and RenderObjClass
// vtables before chaining to the matched base destructor.

class LightClass
{
public:
	__declspec(noinline) virtual ~LightClass();
};

LightClass::~LightClass()
{
}

void Force_LightClass_Deleting_Destructor()
{
	LightClass value;
}
