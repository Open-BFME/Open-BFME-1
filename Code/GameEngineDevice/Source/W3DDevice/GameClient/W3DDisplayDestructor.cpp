// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// W3DDisplay destructor 0x006EFC20: vtable 0x0111EDD0, constructor 0x006EF850.

#include <vector>

// BFME stores NULL inside the if (upstream stores it unconditionally).
#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); (x) = 0; } }

class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface(void);
};

// Display base under its ledger name: destructor 0x0040F6D0 (reached through ILT
// 0x0001A5F0 and the state-0 unwind funclet) and deleteViews 0x0040D970.
class BfmeObjEE
{
public:
	virtual ~BfmeObjEE(void);
	void bfmeDelViews(void);

protected:
	unsigned char m_unmodelled_004[0x24];
	DebugDisplayInterface *m_debugDisplay;
};

class CameraShakeSystemClass
{
public:
	~CameraShakeSystemClass(void);
};

// Declared as an object by camerashakesystem.cpp; BFME holds a pointer at 0x012F7FEC.
extern CameraShakeSystemClass CameraShakerSystem;
#define CameraShakerSystemPtr (*(CameraShakeSystemClass **)&CameraShakerSystem)

class UpdateSubsystem
{
public:
	virtual ~UpdateSubsystem(void);
};

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
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
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

#define TheW3DFileSystemPtr (*(W3DFileSystem **)0x012F8228)

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

class W3DShaderManager
{
public:
	static void shutdown(void);
};

extern void bfmeForward_009372E0(void);

class W3DDisplay : public BfmeObjEE
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
	unsigned char m_unmodelled_184[0x29C - 0x184];
	std::vector<int> m_textureCategories;
};

typedef char W3DDisplaySizeCheck[(sizeof(W3DDisplay) == 0x2A8) ? 1 : -1];

// ??1W3DDisplay@@UAE@XZ
W3DDisplay::~W3DDisplay(void)
{
	delete CameraShakerSystemPtr;

	UpdateSubsystem *updateSubsystem = FirstUpdateSubsystem;
	CameraShakerSystemPtr = 0;
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

	delete m_2DRender;
	m_2DRender = 0;

	bfmeDelViews();

	REF_PTR_RELEASE(m_3DScene);
	REF_PTR_RELEASE(m_2DScene);
	REF_PTR_RELEASE(m_3DInterfaceScene);

	for (int j = 0; j < 4; ++j)
	{
		REF_PTR_RELEASE(m_myLight[j]);
		REF_PTR_RELEASE(m_secondaryLight[j]);
	}

	delete m_nativeDebugDisplay;
	m_nativeDebugDisplay = 0;

	bfmeForward_009372E0();
	W3DShaderManager::shutdown();
	WW3D::Shutdown();
	WWMath::Shutdown();
	delete TheW3DFileSystemPtr;
	TheW3DFileSystemPtr = 0;
}
