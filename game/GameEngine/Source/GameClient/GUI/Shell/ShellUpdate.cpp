// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME Shell::update at retail 0x0057F980.

#include "StringInline.h"

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern Int g_012F4B5C;
#pragma section(".data", read, write)
extern "C" __declspec(allocate(".data")) Int __identifier("?g_012F4B5C@@3HA") = 0;

class WindowLayout
{
public:
	virtual void runInit(void *unused) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *unused) = 0;
};

class AnimateWindowManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void update();
};

class ShellMenuSchemeManager
{
public:
	void update();
};

class Image;

// retail: the global is a plain ImageCollection* (dir32 0x012F6924); the
// collection class is named ImageCollection, not MappedImageCollection.
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class BfmeThingVMZ
{
public:
	void bfmeGo2VMZ(Int image, Int left, Int top, Int right, Int width, Int height);

	unsigned char m_padding[0x110];
	unsigned char m_imageDrawActive;
};

class GameWindowTransitionsHandler
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void update();
	void reverse(AsciiString groupName);
};

class Rva0051D690Shell
{
public:
	void restore();
};

extern ImageCollection *TheMappedImageCollection;
// Retail 0x012F1270 is EA's `Display *TheDisplay`, defined once in
// game/GameEngine/Source/GameClient/Display.cpp. This TU only drives the
// movie-playback path, so the reference carries the canonical spelling and the
// observed instance layout stays a TU-local view cast at each use.
class Display;
extern Display *TheDisplay;
// Retail 0x012F3330 is EA's GameWindowTransitionsHandler *TheTransitionHandler.
extern GameWindowTransitionsHandler *TheTransitionHandler;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

protected:
	unsigned char m_name[4];
};

class Shell : public SubsystemInterface
{
public:
	virtual void update();

private:
	WindowLayout *m_screenStack[16];
	Int m_screenCount;
	unsigned char m_flags[0x10];
	AnimateWindowManager *m_animateWindowManager;
	ShellMenuSchemeManager *m_schemeManager;
};

void Shell::update()
{
	static Int updateState;
	unsigned long (__stdcall *const nowFunction)() = timeGetTime;
	Shell *self = this;

	if (!(*(unsigned char *)&updateState & 1))
	{
		updateState |= 1;
		g_012F4B5C = nowFunction();
	}

	Int now = nowFunction();
	if (now - g_012F4B5C >= 32.333332f)
	{
		for (Int i = self->m_screenCount - 1; i >= 0; --i)
		{
			WindowLayout *screen = self->m_screenStack[i];
			screen->runUpdate(0);
		}

		AnimateWindowManager *animateWindowManager = self->m_animateWindowManager;
		animateWindowManager->update();
		self->m_schemeManager->update();
		g_012F4B5C = now;
	}

	if (!self->m_flags[3] && self->m_flags[2] && !self->m_flags[13])
	{
		self->m_flags[3] = 1;
		AsciiString imageName("ShellMapLowLOD");
		const Image *image = TheMappedImageCollection->findImageByName(imageName);
		if (image)
		{
			BfmeThingVMZ *display = (BfmeThingVMZ *)TheDisplay;
			display->m_imageDrawActive = 1;
			((BfmeThingVMZ *)TheDisplay)->bfmeGo2VMZ((Int)image, 0, 0, 0, 0x3F800000, 0x3F800000);
			TheTransitionHandler->reverse(AsciiString("FadeInGameMovie"));
			TheTransitionHandler->update();
		}
		reinterpret_cast<Rva0051D690Shell *>(self)->restore();
	}
}
