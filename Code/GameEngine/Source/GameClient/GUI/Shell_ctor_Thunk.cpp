// cl: /DNDEBUG /MD /EHsc
// readable body of ??0Shell@@QAE@XZ: Code/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp
// Open-BFME5: clean C++ reconstruction of Shell::Shell.

typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const char *text, int length);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	AsciiString m_name;
};

class WindowLayout;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
class AnimateWindowManager
{
public:
	AnimateWindowManager();
	virtual ~AnimateWindowManager();

private:
	char m_unreconstructed[0x30];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeManager
{
public:
	ShellMenuSchemeManager();
	~ShellMenuSchemeManager();

private:
	char m_unreconstructed[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell : public SubsystemInterface
{
public:
	Shell();
	virtual ~Shell();
	virtual void init();
	virtual Bool loadIniFilesFromLegend();
	virtual void reset();
	virtual void update();
	virtual void draw();

private:
	WindowLayout *m_screenStack[16];
	int m_screenCount;
	Bool m_bfmeState4c;
	Bool m_bfmeState4d;
	Bool m_pendingPush;
	Bool m_pendingPop;
	Bool m_clearBackground;
	char m_unreconstructed[3];
	AsciiString m_pendingPushName;
	Bool m_isShellActive;
	Bool m_shellMapOn;
	AnimateWindowManager *m_animateWindowManager;
	ShellMenuSchemeManager *m_schemeManager;
	UnsignedInt m_musicHandle;
	WindowLayout *m_saveLoadMenuLayout;
	WindowLayout *m_popupReplayLayout;
};

Shell::Shell()
{
	int i;

	m_screenCount = 0;
	for (i = 0; i < 16; ++i)
		m_screenStack[i] = 0;

	m_pendingPush = false;
	m_pendingPop = false;
	m_bfmeState4c = false;
	m_bfmeState4d = false;
	m_clearBackground = false;
	m_pendingPushName.set("", 0);
	m_isShellActive = true;
	m_shellMapOn = false;
	m_animateWindowManager = new AnimateWindowManager;
	m_schemeManager = new ShellMenuSchemeManager;
	m_musicHandle = 1;
	m_saveLoadMenuLayout = 0;
	m_popupReplayLayout = 0;
	m_screenCount = 0;
}
