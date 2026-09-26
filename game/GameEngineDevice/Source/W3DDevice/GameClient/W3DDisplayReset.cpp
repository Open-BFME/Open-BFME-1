// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DDisplay::reset, retail 0x006E8210.
//
// The body follows the GeneralsMD W3DDisplay reset, with BFME's two additions:
// replay fast-forward is cancelled and the native debug display is reset.  The
// retail W3DDisplay vtable at 0x0111EDD0 places this body in the reset slot and
// the matched setWidth/setHeight bodies in the same table.  Its direct base
// call reaches the matched Display::reset body at 0x0040FD90.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled_000[0x180];
	float m_drawSkyBox;                                   // +0x180
	unsigned char m_unmodelled_184[0xC59 - 0x184];
	bool m_tivoFastMode;                                  // +0xC59
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref(void) { ++m_numRefs; }
	void Release_Ref(void)
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void);
	int m_numRefs;
};

class RenderObjClass : public RefCountClass
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SceneIterator
{
public:
	virtual ~SceneIterator(void);
	virtual void First(void) = 0;
	virtual void Next(void) = 0;
	virtual bool Is_Done(void) = 0;
	virtual RenderObjClass *Current_Item(void) = 0;
};

class SceneClass : public RefCountClass
{
public:
	virtual ~SceneClass(void);
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);

	// BFME's iterator ABI has no only-visible argument.  The independently
	// matched SimpleSceneClass::Create_Iterator body uses the same signature.
	virtual SceneIterator *Create_Iterator(void) = 0;
	virtual void Destroy_Iterator(SceneIterator *iterator) = 0;
};

class RTS3DScene : public SceneClass
{
};

// W3DDebugDisplay construction in W3DDisplay::init stores the object at +0x180
// and calls init at vtable +4; this reset dispatches the following +8 slot.
class W3DDebugDisplay
{
public:
	virtual ~W3DDebugDisplay(void);
	virtual void init(void);
	virtual void reset(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual ~Display(void);
	virtual void init(void);
	virtual void postProcessLoad(void);
	virtual bool loadIniFilesFromLegend(void);
	virtual void reset(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay : public Display
{
public:
	virtual void reset(void);
	static RTS3DScene *m_3DScene;

private:
	unsigned char m_unmodelled_004[0x178 - 0x004];
	bool m_isClippedEnabled;                               // +0x178
	unsigned char m_unmodelled_179[0x180 - 0x179];
	W3DDebugDisplay *m_nativeDebugDisplay;                 // +0x180
};

// ?reset@W3DDisplay@@UAEXXZ
void W3DDisplay::reset(void)
{
	Display::reset();

	TheWritableGlobalData->m_tivoFastMode = false;

	if (m_nativeDebugDisplay)
		m_nativeDebugDisplay->reset();

	SceneIterator *sceneIter = m_3DScene->Create_Iterator();
	sceneIter->First();
	while (!sceneIter->Is_Done())
	{
		RenderObjClass *robj = sceneIter->Current_Item();
		if (robj)
		{
			robj->Add_Ref();
			m_3DScene->Remove_Render_Object(robj);
			robj->Release_Ref();
		}
		sceneIter->Next();
	}
	m_3DScene->Destroy_Iterator(sceneIter);

	m_isClippedEnabled = false;

	if (TheWritableGlobalData)
		TheWritableGlobalData->m_drawSkyBox = 0.0f;
}
