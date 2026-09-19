// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: ContestableContain constructor.  The named module factory and
// matched destructor fix the owner and the four STLport members at +0x9bc.

#include <list>
#include <map>

class Thing;
class ModuleData;

class OpenContainPrimaryBase { public: virtual ~OpenContainPrimaryBase() {} private: unsigned char m_pad[8]; };
template <int Number> class OpenContainSecondaryBase { public: virtual ~OpenContainSecondaryBase() {} };
class OpenContainWideSecondaryBase { public: virtual ~OpenContainWideSecondaryBase() {} private: unsigned char m_pad[12]; };

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	virtual ~OpenContain() {}
private:
	unsigned char m_pad[0x384];
};

class Coord3D { public: ~Coord3D() {} private: float m_value[3]; };

class __declspec(novtable) HordeGarrisonContain : public OpenContain
{
public:
	HordeGarrisonContain(Thing *, const ModuleData *);
	virtual ~HordeGarrisonContain();
private:
	Coord3D m_garrisonPoint[3][40];
};

struct Gen_t_0021b400_p8cd { int a[2]; Gen_t_0021b400_p8cd(); Gen_t_0021b400_p8cd(const Gen_t_0021b400_p8cd&); ~Gen_t_0021b400_p8cd(); Gen_t_0021b400_p8cd& operator=(const Gen_t_0021b400_p8cd&); };
bool operator==(const Gen_t_0021b400_p8cd&, const Gen_t_0021b400_p8cd&);
bool operator<(const Gen_t_0021b400_p8cd&, const Gen_t_0021b400_p8cd&);

struct Gen_p8pod { int a[2]; };
bool operator==(const Gen_p8pod&, const Gen_p8pod&);
bool operator<(const Gen_p8pod&, const Gen_p8pod&);

class ContestableContain : public HordeGarrisonContain
{
public:
	ContestableContain(Thing *, const ModuleData *);
	virtual ~ContestableContain();
private:
	unsigned char m_unreconstructed_99c[0x20];
	bool m_flag47c;
	bool m_flag47d;
	unsigned char m_pad47e[0x3e];
	_STL::list<int> m_listA;
	_STL::list<int> m_listB;
	_STL::map<int, Gen_t_0021b400_p8cd> m_map;
	_STL::list<Gen_p8pod> m_listC;
	unsigned int m_lastContestUpdateFrame;
	bool m_flag9d8;
};

// ??0ContestableContain@@QAE@PAVThing@@PBVModuleData@@@Z
ContestableContain::ContestableContain(Thing *thing, const ModuleData *data)
	: HordeGarrisonContain(thing, data)
{
	m_flag9d8 = false;
	m_lastContestUpdateFrame = 0;
}
