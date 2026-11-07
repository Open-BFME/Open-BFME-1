// cl: /DNDEBUG /MD /EHsc
// TextureFilterClass::_Init_Filters (retail 0x00920D10, 446 bytes).
// Identity: the matched caller DX8Wrapper::Do_Onetime_Device_Dependent_Inits
// calls this address as TextureFilterClass::_Init_Filters, as in Zero Hour's
// WW3D2/texturefilter.cpp. The table owners are shared with the setters and
// the texture-stage handler.

// BFME texture-filter table initialiser at retail 0x00920D10.  Retail widened
// each per-stage table to five ints (NONE FAST BEST spare DEFAULT) over eight
// stages; the three tables are Min (0x01346BB0), Mag (0x01346C50) and Mip
// (0x01346CF0), the same Slot arrays the 0x00920BC0 handler reads.
struct IDirect3DDevice8
{
#define GEN_DEVICE_SLOT(n) virtual void __stdcall slot##n(void);
	GEN_DEVICE_SLOT(0) GEN_DEVICE_SLOT(1) GEN_DEVICE_SLOT(2)
	GEN_DEVICE_SLOT(3) GEN_DEVICE_SLOT(4) GEN_DEVICE_SLOT(5)
	GEN_DEVICE_SLOT(6) GEN_DEVICE_SLOT(7) GEN_DEVICE_SLOT(8)
	GEN_DEVICE_SLOT(9) GEN_DEVICE_SLOT(10) GEN_DEVICE_SLOT(11)
	GEN_DEVICE_SLOT(12) GEN_DEVICE_SLOT(13) GEN_DEVICE_SLOT(14)
	GEN_DEVICE_SLOT(15) GEN_DEVICE_SLOT(16) GEN_DEVICE_SLOT(17)
	GEN_DEVICE_SLOT(18) GEN_DEVICE_SLOT(19) GEN_DEVICE_SLOT(20)
	GEN_DEVICE_SLOT(21) GEN_DEVICE_SLOT(22) GEN_DEVICE_SLOT(23)
	GEN_DEVICE_SLOT(24) GEN_DEVICE_SLOT(25) GEN_DEVICE_SLOT(26)
	GEN_DEVICE_SLOT(27) GEN_DEVICE_SLOT(28) GEN_DEVICE_SLOT(29)
	GEN_DEVICE_SLOT(30) GEN_DEVICE_SLOT(31) GEN_DEVICE_SLOT(32)
	GEN_DEVICE_SLOT(33) GEN_DEVICE_SLOT(34) GEN_DEVICE_SLOT(35)
	GEN_DEVICE_SLOT(36) GEN_DEVICE_SLOT(37) GEN_DEVICE_SLOT(38)
	GEN_DEVICE_SLOT(39) GEN_DEVICE_SLOT(40) GEN_DEVICE_SLOT(41)
	GEN_DEVICE_SLOT(42) GEN_DEVICE_SLOT(43) GEN_DEVICE_SLOT(44)
	GEN_DEVICE_SLOT(45) GEN_DEVICE_SLOT(46) GEN_DEVICE_SLOT(47)
	GEN_DEVICE_SLOT(48) GEN_DEVICE_SLOT(49) GEN_DEVICE_SLOT(50)
	GEN_DEVICE_SLOT(51) GEN_DEVICE_SLOT(52) GEN_DEVICE_SLOT(53)
	GEN_DEVICE_SLOT(54) GEN_DEVICE_SLOT(55) GEN_DEVICE_SLOT(56)
	GEN_DEVICE_SLOT(57) GEN_DEVICE_SLOT(58) GEN_DEVICE_SLOT(59)
	GEN_DEVICE_SLOT(60) GEN_DEVICE_SLOT(61) GEN_DEVICE_SLOT(62)
	GEN_DEVICE_SLOT(63) GEN_DEVICE_SLOT(64) GEN_DEVICE_SLOT(65)
	GEN_DEVICE_SLOT(66) GEN_DEVICE_SLOT(67) GEN_DEVICE_SLOT(68)
	virtual long __stdcall SetTextureStageState(
		unsigned int, unsigned int, unsigned int);
#undef GEN_DEVICE_SLOT
};

struct Rva00920AE0Slot
{
	int m_options[4];
	int m_selected;
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *D3DDevice;
};

extern unsigned int number_of_DX8_calls;
extern unsigned int Rva01340568StageChanges;
extern unsigned char *BfmeCurrentCaps;
extern Rva00920AE0Slot g_bfmeOptionSlots0[8];  // retail 0x01346BB0, defined in texturefilter.cpp
extern Rva00920AE0Slot g_bfmeOptionSlotsA[8];
extern Rva00920AE0Slot g_bfmeOptionSlotsB[8];

struct BfmeTextureCaps
{
	unsigned char m_pad[0x48];
	unsigned int m_textureFilterCaps;
};

class TextureFilterClass
{
public:
	enum TextureFilterMode
	{
		TEXTURE_FILTER_BILINEAR,
		TEXTURE_FILTER_TRILINEAR,
		TEXTURE_FILTER_ANISOTROPIC
	};
	static void _Init_Filters(TextureFilterMode filter_type);
};

#define CAPS ((struct BfmeTextureCaps *)BfmeCurrentCaps)
void TextureFilterClass::_Init_Filters(TextureFilterMode filter_type)
{

	g_bfmeOptionSlots0[0].m_options[0] = 1;
	g_bfmeOptionSlotsA[0].m_options[0] = 1;
	g_bfmeOptionSlotsB[0].m_options[0] = 0;
	g_bfmeOptionSlots0[0].m_options[1] = 2;
	g_bfmeOptionSlotsA[0].m_options[1] = 2;
	g_bfmeOptionSlotsB[0].m_options[1] = 1;
	g_bfmeOptionSlotsA[0].m_options[2] = 1;
	g_bfmeOptionSlots0[0].m_options[2] = 1;
	g_bfmeOptionSlotsB[0].m_options[2] = 1;
	g_bfmeOptionSlots0[0].m_options[3] = 1;
	g_bfmeOptionSlotsA[0].m_options[3] = 1;
	g_bfmeOptionSlotsB[0].m_options[3] = 0;

	if (CAPS->m_textureFilterCaps & 0x2000000) g_bfmeOptionSlotsA[0].m_options[2] = 2;
	if (CAPS->m_textureFilterCaps & 0x200) g_bfmeOptionSlots0[0].m_options[2] = 2;

	if (filter_type == TextureFilterClass::TEXTURE_FILTER_ANISOTROPIC) {
		if (CAPS->m_textureFilterCaps & 0x4000000) g_bfmeOptionSlotsA[0].m_options[2] = 3;
		if (CAPS->m_textureFilterCaps & 0x400) g_bfmeOptionSlots0[0].m_options[2] = 3;
	}
	if (filter_type == TextureFilterClass::TEXTURE_FILTER_ANISOTROPIC || filter_type == TextureFilterClass::TEXTURE_FILTER_TRILINEAR) {
		if (CAPS->m_textureFilterCaps & 0x20000) g_bfmeOptionSlotsB[0].m_options[2] = 2;
	}

	unsigned int i;
	for (i = 1; i < 8; ++i) {
		g_bfmeOptionSlots0[i].m_options[0] = g_bfmeOptionSlots0[i - 1].m_options[0];
		g_bfmeOptionSlotsA[i].m_options[0] = g_bfmeOptionSlotsA[i - 1].m_options[0];
		g_bfmeOptionSlotsB[i].m_options[0] = g_bfmeOptionSlotsB[i - 1].m_options[0];
		g_bfmeOptionSlots0[i].m_options[1] = g_bfmeOptionSlots0[i - 1].m_options[1];
		g_bfmeOptionSlotsA[i].m_options[1] = g_bfmeOptionSlotsA[i - 1].m_options[1];
		g_bfmeOptionSlotsB[i].m_options[1] = g_bfmeOptionSlotsB[i - 1].m_options[1];
		if (g_bfmeOptionSlotsA[i - 1].m_options[2] == 3) g_bfmeOptionSlotsA[i].m_options[2] = 2;
		else g_bfmeOptionSlotsA[i].m_options[2] = g_bfmeOptionSlotsA[i - 1].m_options[2];
		if (g_bfmeOptionSlots0[i - 1].m_options[2] == 3) g_bfmeOptionSlots0[i].m_options[2] = 2;
		else g_bfmeOptionSlots0[i].m_options[2] = g_bfmeOptionSlots0[i - 1].m_options[2];
		g_bfmeOptionSlotsB[i].m_options[2] = g_bfmeOptionSlotsB[i - 1].m_options[2];
	}

	for (i = 0; i < 8; ++i) {
		g_bfmeOptionSlots0[i].m_selected = g_bfmeOptionSlots0[i].m_options[2];
		g_bfmeOptionSlotsA[i].m_selected = g_bfmeOptionSlotsA[i].m_options[2];
		g_bfmeOptionSlotsB[i].m_selected = g_bfmeOptionSlotsB[i].m_options[2];
		DX8Wrapper::D3DDevice->SetTextureStageState(i, 10, 2);
		number_of_DX8_calls++;
		Rva01340568StageChanges++;
	}
}
