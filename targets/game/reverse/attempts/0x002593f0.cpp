// ?finish@Rva00259670Primary@@QAEXPAVRva0025D7E0Subject@@@Z
// partial score=0.9274 date=2026-10-31
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x002593F0/512B: the finish step matched caller 0x00259670
// (Rva00259670Dispatch::run) reaches through ILT 0x00041A4C on this-0x10.
// It switches the weather to 4, plays the module data's FXList (+0x214) at
// the terrain extent centre, then scatters the template named at +0x218 on
// a grid of spacing +0x21C over the extent. Owner identity is unproven, so
// the caller-backed address-derived names stay.
#include "ascii_string.h"
#include <bitset>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class Matrix3D;
class Team;
class ThingTemplate;

template <unsigned N> class BitFlags
{
	std::bitset<N> m_bits;
public:
	BitFlags() {}
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
	virtual void slot07();
	virtual void getExtentIncludingBorder(Region3D *extent);
};

extern TerrainLogic *TheTerrainLogic;

struct RetailGlobalWeatherSystem;
extern RetailGlobalWeatherSystem *TheGlobalWeatherSystem;

class GlobalWeatherSystem
{
public:
	void setWeather(int weather);
};

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, Real speed, const Coord3D *other) const;
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const BitFlags<86> &status, unsigned flags);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

extern const Real g_rva0107533C;
extern Real g_bfmeDefaultBU;

struct Rva00259670PrimaryData
{
	unsigned char m_prefix000[0x214];
	FXList *m_fx;
	AsciiString m_templateName;
	Real m_spacing;
};

class Rva0025D7E0Subject;

class Rva00259670Primary
{
public:
	void finish(Rva0025D7E0Subject *subject);

private:
	void *m_prefix000;
	const Rva00259670PrimaryData *m_data;
};

void Rva00259670Primary::finish(Rva0025D7E0Subject *)
{
	((GlobalWeatherSystem *)TheGlobalWeatherSystem)->setWeather(4);
	Region3D extent;
	Coord3D pos;
	const Rva00259670PrimaryData *data = m_data;
	TheTerrainLogic->getExtentIncludingBorder(&extent);
	if (data->m_fx)
	{
		pos.x = (extent.lo.x + extent.hi.x) * g_rva0107533C;
		pos.y = (extent.lo.y + extent.hi.y) * g_rva0107533C;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
		FXList *fx = data->m_fx;
		if (fx && !fx->bfmeIsBlocked())
			fx->doFXPos(&pos, 0, 0, 0);
	}
	Real spacing = data->m_spacing;
	if (spacing > g_bfmeDefaultBU)
	{
		volatile Real y;
		for (y = (Real)(int)(spacing + extent.lo.y); *(Real *)&y < extent.hi.y - spacing; y = (Real)(int)(*(Real *)&y + spacing))
		{
			volatile Real x;
			for (x = (Real)(int)(spacing + extent.lo.x); *(Real *)&x < extent.hi.x - spacing; x = (Real)(int)(*(Real *)&x + spacing))
			{
				pos.x = x;
				pos.y = y;
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
				const ThingTemplate *tmpl = ((BfmeThingFactory *)TheThingFactory)->findTemplate(data->m_templateName);
				if (tmpl)
				{
					BitFlags<86> status;
					Object *obj = TheThingFactory->newObject(tmpl, 0, status, 0);
					if (obj)
						obj->setPosition(&pos);
				}
			}
		}
	}
}
