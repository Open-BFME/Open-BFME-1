// cl: /DNDEBUG /MD /EHsc
// Retail 0x00904BE0 creates a D3D texture for the 0x0090C2F0 texture object.
// The caller supplies the D3D pool and usage values after normalizing its
// public mode flags.  The error report uses the BFME index-buffer debug stream.

struct Rva00904BE0Device;
struct Rva00904BE0Texture;

extern "C" long __stdcall D3DXCreateTexture(
	Rva00904BE0Device *device,
	unsigned width,
	unsigned height,
	unsigned mip_levels,
	unsigned usage,
	unsigned format,
	unsigned pool,
	Rva00904BE0Texture **texture);

extern Rva00904BE0Device *Rva01340534Device;
extern void _bfme_debugRecordCallsite(int kind);

class Rva00904BE0Message
{
public:
	virtual Rva00904BE0Message *slot00(void *value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual Rva00904BE0Message *slot38(const void *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(int value);
};

class Rva00904BE0Debug
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual Rva00904BE0Message *slot6c(int first, int second);
};

extern Rva00904BE0Debug *g_BFMEIndexBufferDebug;

static __forceinline void Rva00904BE0Report(long result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->slot60();
		g_BFMEIndexBufferDebug->slot6c(0, 0)
			->slot38((const void *)0x111d770)
			->slot00((void *)result)
			->slot4c(1);
	}
}

Rva00904BE0Texture *Rva00904BE0CreateTexture(
	unsigned width,
	unsigned height,
	unsigned format,
	unsigned mip_levels,
	unsigned pool,
	unsigned usage)
{
	Rva00904BE0Texture *texture = 0;

	if (usage == 1)
	{
		long result = D3DXCreateTexture(
			Rva01340534Device,
			width,
			height,
			mip_levels,
			1,
			format,
			pool,
			&texture);
		if (result < 0)
			return 0;
		if (result == 0)
			return texture;
		Rva00904BE0Report(result);
	}
	else
	{
		if (pool == 1 && usage == 0x200)
			usage = 0;

		long result = D3DXCreateTexture(
			Rva01340534Device,
			width,
			height,
			mip_levels,
			usage,
			format,
			pool,
			&texture);
		if (result == 0)
			return texture;
		Rva00904BE0Report(result);
	}

	return texture;
}
