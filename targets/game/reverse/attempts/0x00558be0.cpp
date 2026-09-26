// ?setup@OnlineQuickMatchColorSetup@@QAEXXZ
// partial score=0.98 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Image;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
private:
	void *m_data;
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

#define g_whiteBoxImage (*(const Image **)0x012F4AC4)

#define g_imageSetupFlags (*(unsigned int *)0x012F4AC8)

class MultiplayerColorDefinition
{
public:
	int getColor() const
	{
		return *(const int *)((const char *)this + 0x10);
	}
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = *(int *)((char *)this + 0x34);
		return m_numColors;
	}

private:
	unsigned char m_padding[0x3c];
	int m_numColors;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class GlobalData
{
private:
	unsigned char m_padding[0x2c];

public:
	int m_colorWidth;
};

extern GlobalData *TheWritableGlobalData;

class GameWindow
{
public:
	void winGetSize(int *width, int *height);
};

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getColor();

private:
	unsigned char m_padding[0x10];
};

class OnlineQuickMatchGadgetState
{
public:
	void init();
	int add(void *image, int width, int height, int color);
	void addColor(void *row, void *index);
	void setColorCount(int value);
	void applyColor(void *value);
};

#pragma comment(linker, "/alternatename:?add@OnlineQuickMatchGadgetState@@QAEHPAXHHH@Z=?d_004b5aa0@@YAXXZ")
#pragma comment(linker, "/alternatename:?init@OnlineQuickMatchGadgetState@@QAEXXZ=?j_00046a01@@YAXXZ")
#pragma comment(linker, "/alternatename:?setColorCount@OnlineQuickMatchGadgetState@@QAEXH@Z=?j_00036f34@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyColor@OnlineQuickMatchGadgetState@@QAEXPAX@Z=?j_00046dbc@@YAXXZ")
#pragma comment(linker, "/alternatename:?addColor@OnlineQuickMatchGadgetState@@QAEXPAX0@Z=?j_00035b02@@YAXXZ")

class BfmeAptGameWindow
{
public:
	virtual void slot00();

private:
	unsigned char m_padding[0x3c];
};

class OnlineQuickMatchColorSetup : public BfmeAptGameWindow
{
public:
	void setup();

private:
	QuickMatchPreferences m_preferences;
	unsigned char m_betweenPreferencesAndGadget[0x08];
	OnlineQuickMatchGadgetState m_gadget;
};

void OnlineQuickMatchColorSetup::setup()
{
	MultiplayerColorDefinition *color;
	GameWindow *window;
	int width;
	int height;
	int colorCount;

	colorCount = TheMultiplayerSettings->getNumColors();

	m_gadget.init();
	window = *(GameWindow **)&m_gadget;
	window->winGetSize(&width, &height);

	int scale = TheWritableGlobalData->m_colorWidth;
	int colorWidth = (width - (scale * 0x20 / 0x400)) * 0x400 / scale;

	for (int i = 0; i < colorCount; ++i)
	{
		color = TheMultiplayerSettings->getColor(i);
		if (color != 0)
		{
			if ((g_imageSetupFlags & 1) == 0)
			{
				g_imageSetupFlags |= 1;
				BFMERetailAsciiString imageName("AptWhiteBox");
				g_whiteBoxImage = TheMappedImageCollection->findImageByName(
					*(const AsciiString *)&imageName);
			}

			int row = m_gadget.add(
				(void *)g_whiteBoxImage, colorWidth, 0x14, color->getColor());
			m_gadget.addColor((void *)row, (void *)i);
		}
	}

	m_gadget.setColorCount(colorCount * 0x1e);
	m_gadget.applyColor((void *)m_preferences.getColor());
}
