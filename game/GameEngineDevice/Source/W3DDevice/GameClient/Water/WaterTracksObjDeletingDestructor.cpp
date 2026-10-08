// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: WaterTracksObj scalar-deleting destructor at retail RVA
// 0x007ABA70 (30 bytes). The exact constructor at 0x007AB180, matched complete
// destructor at 0x007AB150, and recovered water-track allocation, binding, and
// shutdown paths establish the object. The wrapper calls the non-virtual
// destructor through ILT 0x0003DD2F before conditionally invoking delete.

//
// The complete destructor at retail 0x007AB150 (19 bytes) restores the
// WaterTracksObj vftable at +0 (0x00D2824C) and releases the stage-zero
// texture at +4 through TextureBaseClass::Release_Ref (0x009EB7A0).
// WaterTracksRenderSystem::shutdown reaches it through ILT 0x0003DD2F.

// The three-slot table at retail 0x00D2824C holds the ILTs of the one-byte
// slot 0 body 0x007AB170, Get_Obj_Space_Bounding_Sphere (0x007AB240) and
// Get_Obj_Space_Bounding_Box (0x007AB270).
void j_00040b1f();
void j_000156a9();
void j_000299a6();

extern "C" void (* const bfmeVftSH[3])() = { j_00040b1f, j_000156a9, j_000299a6 };

class TextureBaseClass
{
public:
	void Release_Ref();
};

class WaterTracksObj
{
public:
	~WaterTracksObj();

	void *m_vftable;
	TextureBaseClass *m_stageZeroTexture;
};

__declspec(noinline) WaterTracksObj::~WaterTracksObj()
{
	m_vftable = (void *)bfmeVftSH;
	TextureBaseClass *texture = m_stageZeroTexture;
	if (texture != 0)
		texture->Release_Ref();
}

void forceWaterTracksObjDelete(WaterTracksObj *object)
{
	delete object;
}
