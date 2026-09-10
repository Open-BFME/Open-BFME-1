// ??1W3DDisplay@@UAE@XZ
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

// This is the complete 566-byte BFME W3DDisplay destructor at 0x006EFC20.
// The W3DDisplay vtable store at 0x0111EDD0, the matching constructor body at
// 0x006EF850, and the named deleting-destructor caller at 0x006F02D0 establish
// the owner.  The shipped GeneralsMD header is not this object's ABI: the
// retail destructor proves the inherited debug pointer at +0x28, the two
// four-entry light arrays at +0x144/+0x154, the native display at +0x180, and
// the STL vector at +0x29C.  Those offsets are kept in this TU-local view.

class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface(void);
};

class Display
{
public:
	virtual void init(void);
	virtual void postProcessLoad(void);
	virtual bool loadIniFilesFromLegend(void);
	virtual void reset(void);

protected:
	virtual void deleteViews(void);
	unsigned char m_unmodelled_004[0x24];
	DebugDisplayInterface *m_debugDisplay;
};

class CameraShakeSystemClass
{
public:
	~CameraShakeSystemClass(void);
};

// 0x012F7FEC is the BFME pointer form of CameraShakerSystem.  Its destructor
// is reached through the existing ILT 0x0001B6A8, whose first retail target is
// the matched CameraShakeSystemClass destructor.
extern CameraShakeSystemClass *CameraShakerSystem;
extern void j_0001b6a8(void);

class UpdateSubsystem
{
public:
	virtual ~UpdateSubsystem(void);
};

// GameEngineUpdate.cpp proves this first update-subsystem slot at 0x0134FAA0.
#define FirstUpdateSubsystem (*(UpdateSubsystem **)0x0134FAA0)

class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

class Render2DClass
{
public:
	~Render2DClass(void);
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	int m_numRefs;
};

class RTS3DScene : public RefCountClass
{
};

class RTS2DScene : public RefCountClass
{
};

class RTS3DInterfaceScene : public RefCountClass
{
};

class LightClass : public RefCountClass
{
};

class W3DDebugDisplay
{
public:
	virtual ~W3DDebugDisplay(void);
};

class W3DFileSystem
{
public:
	virtual ~W3DFileSystem(void);
};

class WW3D
{
public:
	static bool Shutdown(void);
};

class WWMath
{
public:
	static void Shutdown(void);
};

extern void bfmeForward_009372E0(void);
extern void j_0004a07f(void);
extern void j_0001a5f0(void);

class W3DDisplayTail
{
public:
	~W3DDisplayTail(void)
	{
		j_0001a5f0();
	}

private:
	unsigned char m_unmodelled[0x118];
};

class W3DDisplay : public Display
{
public:
	virtual ~W3DDisplay(void);

	static RTS3DScene *m_3DScene;
	static RTS2DScene *m_2DScene;
	static RTS3DInterfaceScene *m_3DInterfaceScene;

private:
	unsigned char m_unmodelled_02C[0x144 - 0x02C];
	LightClass *m_myLight[4];
	LightClass *m_secondaryLight[4];
	Render2DClass *m_2DRender;
	unsigned char m_unmodelled_168[0x180 - 0x168];
	W3DDebugDisplay *m_nativeDebugDisplay;
	W3DDisplayTail m_tail;
	std::vector<int> m_textureCategories;
};

typedef char W3DDisplaySizeCheck[(sizeof(W3DDisplay) == 0x2A8) ? 1 : -1];

// ??1W3DDisplay@@UAE@XZ
W3DDisplay::~W3DDisplay(void)
{
	if (CameraShakerSystem != 0)
	{
		j_0001b6a8();
		::operator delete(CameraShakerSystem);
	}

	UpdateSubsystem *updateSubsystem = FirstUpdateSubsystem;
	CameraShakerSystem = 0;
	if (updateSubsystem != 0)
		delete updateSubsystem;
	FirstUpdateSubsystem = 0;

	delete m_debugDisplay;

	for (int i = 0; i < 15; ++i)
		TheDisplayStringManager->freeDisplayString(
			reinterpret_cast<DisplayString **>(reinterpret_cast<unsigned char *>(this) + 0x18C)[i]);
	for (int i = 0; i < 25; ++i)
		TheDisplayStringManager->freeDisplayString(
			reinterpret_cast<DisplayString **>(reinterpret_cast<unsigned char *>(this) + 0x1C8)[i]);
	for (int i = 0; i < 17; ++i)
		TheDisplayStringManager->freeDisplayString(
			reinterpret_cast<DisplayString **>(reinterpret_cast<unsigned char *>(this) + 0x22C)[i]);

	if (m_2DRender != 0)
	{
		delete m_2DRender;
		m_2DRender = 0;
	}

	Display::deleteViews();

	RTS3DScene *scene3D = m_3DScene;
	if (scene3D != 0)
		scene3D->Release_Ref();
	m_3DScene = 0;

	RTS2DScene *scene2D = m_2DScene;
	if (scene2D != 0)
		scene2D->Release_Ref();
	m_2DScene = 0;

	RTS3DInterfaceScene *interfaceScene = m_3DInterfaceScene;
	if (interfaceScene != 0)
		interfaceScene->Release_Ref();
	m_3DInterfaceScene = 0;

	for (int j = 0; j < 4; ++j)
	{
		LightClass *light = m_myLight[j];
		if (light != 0)
			light->Release_Ref();
		m_myLight[j] = 0;

		light = m_secondaryLight[j];
		if (light != 0)
			light->Release_Ref();
		m_secondaryLight[j] = 0;
	}

	delete m_nativeDebugDisplay;
	m_nativeDebugDisplay = 0;

	bfmeForward_009372E0();
	j_0004a07f();
	WW3D::Shutdown();
	WWMath::Shutdown();
	delete reinterpret_cast<W3DFileSystem **>(0x012F8228)[0];
	reinterpret_cast<W3DFileSystem **>(0x012F8228)[0] = 0;
}

#undef FirstUpdateSubsystem
