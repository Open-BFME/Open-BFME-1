// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversions.
// ghidra: FUN_00b23cf0 retail @ 0x00723CF0 size 108
// Sibling of BfmeA1137 (BfmeConv1137.cpp): stamp this+0x98 and this+0x3d,
// then copy three dwords out of the walked override of the singleton at
// 0x012F15F8.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class WeatherSetting : public Overridable
{
public:
	char m_unmodelled_08[0x5c - 8];
	int m_5c;
	int m_60;
	int m_64;
};

template <class T> class OVERRIDE
{
public:
	T *ptr;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class BfmeA1137
{
public:
	void copyFromOverride();

private:
	char m_unmodelled_00[0x3d];
	char m_flag3d;
	char m_unmodelled_3e[0x4c - 0x3e];
	int m_4c;
	int m_50;
	int m_54;
	char m_unmodelled_58[0x98 - 0x58];
	int m_98;
};

static const WeatherSetting *walk(const WeatherSetting *d)
{
	const WeatherSetting *f = d;
	if (d && d->m_nextOverride)
		f = (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	return f;
}

void BfmeA1137::copyFromOverride()
{
	const WeatherSetting *d;
	const WeatherSetting *f;

	m_98 = 1;
	m_flag3d = 1;

	f = walk(TheWeatherSetting.ptr);
	m_4c = f->m_5c;

	f = walk(TheWeatherSetting.ptr);
	m_50 = f->m_60;

	d = TheWeatherSetting.ptr;
	f = d;
	if (!TheWeatherSetting.ptr)
	{
		m_54 = f->m_64;
		return;
	}
	if (d->m_nextOverride)
		d = (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	m_54 = d->m_64;
}
