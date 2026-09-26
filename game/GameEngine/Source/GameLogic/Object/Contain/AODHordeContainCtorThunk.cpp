// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: AODHordeContain constructor.  Factory/destructor evidence fixes
// the HordeContain base, vector, and both compiler-managed element arrays.

#include <vector>

class Thing;
class ModuleData;

class OpenContainPrimaryBase { public: virtual ~OpenContainPrimaryBase() {} private: unsigned char m_pad[8]; };
template <int Number> class OpenContainSecondaryBase { public: virtual ~OpenContainSecondaryBase() {} };
class OpenContainWideSecondaryBase { public: virtual ~OpenContainWideSecondaryBase() {} private: unsigned char m_pad[12]; };

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase, public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase, public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>, public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>, public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public: virtual ~OpenContain() {}
private: unsigned char m_pad[0x9c];
};

class SiegeEngineContainTenthBase { public: virtual ~SiegeEngineContainTenthBase() {} };
class HordeContainEleventhBase { public: virtual void slot(); };

class __declspec(novtable) SiegeEngineContainBase
	: public OpenContain, public SiegeEngineContainTenthBase
{
public: virtual ~SiegeEngineContainBase();
private: unsigned char m_pad[0x0c];
};

class __declspec(novtable) HorseHordeContainBase
	: public SiegeEngineContainBase, public HordeContainEleventhBase
{
public:
	HorseHordeContainBase(Thing *, const ModuleData *);
	virtual ~HorseHordeContainBase();
private:
	unsigned char m_pad[0x13c];
};

struct Gen_p24pod { int a[6]; };

class AODHordeContainFields230
{
public:
	AODHordeContainFields230()
	{
		m_values[0] = 0;
		m_values[1] = 0;
		m_values[2] = 0;
		m_values[3] = 0;
		m_values[4] = 0;
	}
private:
	unsigned int m_values[5];
};

class AODHordeContainFields244
{
public:
	AODHordeContainFields244()
	{
		m_values[0] = 0;
		m_values[1] = 0;
		m_values[2] = 0;
	}
private:
	unsigned int m_values[3];
};

class AODHordeContainElement16
{
public:
	AODHordeContainElement16();
	~AODHordeContainElement16();
	void clear() { m_words[0] = 0; m_words[1] = 0; m_words[2] = 0; m_words[3] = 0; }
private:
	unsigned int m_words[4];
};

class AODHordeContainElement24
{
public:
	AODHordeContainElement24();
	~AODHordeContainElement24();
private:
	unsigned char m_bytes[0x18];
};

class AODHordeContain : public HorseHordeContainBase
{
public:
	AODHordeContain(Thing *, const ModuleData *);
	virtual ~AODHordeContain();
private:
	_STL::vector<Gen_p24pod> m_vector;
	AODHordeContainFields230 m_fields230;
	AODHordeContainFields244 m_fields244;
	AODHordeContainElement16 m_arrayA[0x3c];
	unsigned int m_610;
	AODHordeContainElement24 m_arrayB[0x14];
	unsigned int m_7f4;
};

// ??0AODHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z
AODHordeContain::AODHordeContain(Thing *thing, const ModuleData *data)
	: HorseHordeContainBase(thing, data), m_610(0)
{
	m_7f4 = 0;
	for (int j = 0; j != 0x3c; ++j)
		m_arrayA[j].clear();
}
