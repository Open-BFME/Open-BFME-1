// ?Rva009AA260Scale@@YAHPAURva009AA260Context@@PBEHIIPAEIII@Z
// Retail RVA 009AA260: caller 009AA4F0 pushes nine arguments and cleans 24h.
// Code ends with ret at +253; two 24-byte tables at +254/+26c follow it.
// Callback slots are witnessed by dispatch initialization at RVA009B0FBF.
// The direct-copy callback is the matched 009A91A0 bfmeCopy body; retail
// deliberately invokes it with an ignored fourth cdecl argument. This cast
// preserves that MSVC x86 ABI contract, rather than introducing a wrapper.
// The empty vertical callback address is independently verified as 009A91C0.
// Table destinations (offsets): 52/46/68/3b/68/5e; c7/a5/102/87/102/e6.
// The address-qualified name is intentional: the caller/layout evidence proves
// the scaler family and ABI, but not an original class or public owner.

struct Rva009AA260Context
{
	unsigned char m_pad00[0x58];
	int m_hscale;
	int m_hratio;
	int m_vscale;
	int m_vratio;
};

typedef void (__cdecl *Rva009AA260HorizontalScale)(
	const unsigned char *, unsigned int, unsigned char *, unsigned int);
typedef void (__cdecl *Rva009AA260VerticalScale)(
	unsigned char *, unsigned int, unsigned int);

extern void __cdecl bfmeCopy(const void *, unsigned int, void *);

static void __cdecl Rva009A91C0NullScale(
	unsigned char *, unsigned int, unsigned int)
{
}

static Rva009AA260HorizontalScale rva009AA260Horizontal45(void)
{
	return *reinterpret_cast<Rva009AA260HorizontalScale *>(0x01356DA4);
}

static Rva009AA260HorizontalScale rva009AA260Horizontal35(void)
{
	return *reinterpret_cast<Rva009AA260HorizontalScale *>(0x01356EB0);
}

static Rva009AA260HorizontalScale rva009AA260Horizontal21(void)
{
	return *reinterpret_cast<Rva009AA260HorizontalScale *>(0x01356E80);
}

static Rva009AA260VerticalScale rva009AA260Vertical45(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356E7C);
}

static Rva009AA260VerticalScale rva009AA260Vertical35(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356EA8);
}

static Rva009AA260VerticalScale rva009AA260Vertical21(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356E70);
}

static Rva009AA260VerticalScale rva009AA260LastVertical45(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356E78);
}

static Rva009AA260VerticalScale rva009AA260LastVertical35(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356E90);
}

static Rva009AA260VerticalScale rva009AA260LastVertical21(void)
{
	return *reinterpret_cast<Rva009AA260VerticalScale *>(0x01356EA4);
}

int __cdecl Rva009AA260Scale(
	Rva009AA260Context *context,
	const unsigned char *source,
	int source_pitch,
	unsigned int source_width,
	unsigned int source_height,
	unsigned char *dest,
	unsigned int dest_pitch,
	unsigned int dest_width,
	unsigned int dest_height)
{
	unsigned int i;
	unsigned int k;
	unsigned int source_band_height = 0;
	unsigned int dest_band_height = 0;

	int hscale = context->m_hscale;
	int hratio = context->m_hratio;
	int vscale = context->m_vscale;
	int vratio = context->m_vratio;
	int ratio_scalable = 1;

	Rva009AA260HorizontalScale horizontal_scale = 0;
	Rva009AA260VerticalScale vertical_scale = 0;
	Rva009AA260VerticalScale last_vertical_scale = 0;

	(void)source_height;

	switch (hratio * 10 / hscale)
	{
	case 8:
		horizontal_scale = rva009AA260Horizontal45();
		break;
	case 6:
		horizontal_scale = rva009AA260Horizontal35();
		break;
	case 5:
		horizontal_scale = rva009AA260Horizontal21();
		break;
	case 10:
		horizontal_scale = (Rva009AA260HorizontalScale)bfmeCopy;
		break;
	default:
		ratio_scalable = 0;
		break;
	}

	switch (vratio * 10 / vscale)
	{
	case 8:
		vertical_scale = rva009AA260Vertical45();
		last_vertical_scale = rva009AA260LastVertical45();
		source_band_height = 4;
		dest_band_height = 5;
		break;
	case 6:
		vertical_scale = rva009AA260Vertical35();
		last_vertical_scale = rva009AA260LastVertical35();
		source_band_height = 3;
		dest_band_height = 5;
		break;
	case 5:
		vertical_scale = rva009AA260Vertical21();
		last_vertical_scale = rva009AA260LastVertical21();
		source_band_height = 1;
		dest_band_height = 2;
		break;
	case 10:
		vertical_scale = Rva009A91C0NullScale;
		last_vertical_scale = Rva009A91C0NullScale;
		source_band_height = 4;
		dest_band_height = 4;
		break;
	default:
		ratio_scalable = 0;
		break;
	}

	if (ratio_scalable == 0)
		return ratio_scalable;

	horizontal_scale(source, source_width, dest, dest_width);

	for (k = 0;
		k < (dest_height + dest_band_height - 1) / dest_band_height - 1;
		++k)
	{
		for (i = 1; i < source_band_height; ++i)
		{
			horizontal_scale(
				source + i * source_pitch, source_width,
				dest + i * dest_pitch, dest_width);
		}

		horizontal_scale(
			source + source_band_height * source_pitch, source_width,
			dest + dest_band_height * dest_pitch, dest_width);

		vertical_scale(dest, dest_pitch, dest_width);

		source += source_band_height * source_pitch;
		dest += dest_band_height * dest_pitch;
	}

	for (i = 1; i < source_band_height; ++i)
	{
		horizontal_scale(
			source + i * source_pitch, source_width,
			dest + i * dest_pitch, dest_width);
	}

	last_vertical_scale(dest, dest_pitch, dest_width);
	return ratio_scalable;
}
