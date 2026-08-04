// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the ScreenBWFilter::init naked dump to clean C++.
//
// BFME-only filter, so the shape comes from the call sites: bail unless the
// device and pixel-shader globals are both live, unless the chipset is known,
// and unless it is at least the pixel-shader tier; then load the monochrome
// pixel shader into the handle at this+0x04 and publish the filter pointer.
//
// W3DShaderManager::getChipset was already pinned by other work. The shader
// loader at 0x0001FC99 is an unidentified cdecl body, so it is declared under
// an address-derived name and the symbols.csv note says so.
//
// The string literal is proven by the build's verify_string_refs gate: it has
// to byte-equal "shaders\\monochrome.pso" at the referenced address.

typedef int Int;

enum ChipsetType
{
	DC_UNKNOWN = 0
};

class W3DShaderManager
{
public:
	static ChipsetType getChipset(void);					///< ILT thunk at 0x000162A7
};

// Unidentified cdecl loader at 0x0001FC99: (filename, handle-out) -> negative on failure.
Int unidentified_0001FC99(const char *filename, unsigned int *handle);

extern void *g_deviceGlobal;								///< retail [0x012F9D04]
extern void *g_pixelShaderGlobal;							///< retail [0x012F9D0C]
extern Int g_filterFrameGlobal;								///< retail [0x013071B4]
extern void *g_activeFilterGlobal;							///< retail [0x012F9CD0]
extern Int g_filterState;									///< retail [0x012BC100]

class ScreenBWFilter
{
public:
	virtual Int init(void);

private:
	unsigned int m_shader;									///< retail this+0x04
};

// ?init@ScreenBWFilter@@UAEHXZ
Int ScreenBWFilter::init(void)
{
	m_shader = 0;
	g_filterFrameGlobal = 0;

	if (g_deviceGlobal != 0 && g_pixelShaderGlobal != 0)
	{
		ChipsetType chipset = W3DShaderManager::getChipset();
		if (chipset != DC_UNKNOWN && chipset >= 3)
		{
			if (unidentified_0001FC99("shaders\\monochrome.pso", &m_shader) >= 0)
			{
				g_activeFilterGlobal = &g_filterState;
				return 1;
			}
		}
	}

	return 0;
}
