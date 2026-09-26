// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) int __stdcall AIL_get_preference(
	unsigned int preference);

extern "C" __declspec(dllimport) void __stdcall AIL_set_preference(
	unsigned int preference, int value);

extern "C" __declspec(dllimport) void __stdcall AIL_serve(void);

struct Rva00696220Sub
{
	char m_pad48[0x48];
	unsigned int m_field48;
	unsigned int m_field4C;
};

class Rva00696220AudioClass
{
	char m_pad0C[0x0C];
	Rva00696220Sub *m_sub;

public:
	void bfmeMilesUpdate4C_00696220();
	void bfmeMilesUpdate48_00696250();
};

void Rva00696220AudioClass::bfmeMilesUpdate4C_00696220()
{
	int pref = AIL_get_preference(0x22);
	AIL_set_preference(0x2A, m_sub->m_field4C / pref);
	AIL_serve();
}

void Rva00696220AudioClass::bfmeMilesUpdate48_00696250()
{
	int pref = AIL_get_preference(0x22);
	AIL_set_preference(0x2A, m_sub->m_field48 / pref);
}


void bfmeMilesServe_00696280()
{
	AIL_serve();
}

int bfmeMilesPreferenceProduct_006962A0()
{
	return AIL_get_preference(0x2A) * AIL_get_preference(0x22);
}

struct Point2D
{
	int x;
	int y;
};

class GloTacticalView00696040
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2C() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual void v38() = 0;
	virtual void v3C() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual void v4C() = 0;
	virtual void v50() = 0;
	virtual void v54() = 0;
	virtual void v58() = 0;
	virtual void v5C() = 0;
	virtual void v60() = 0;
	virtual void v64() = 0;
	virtual void v68() = 0;
	virtual void v6C() = 0;
	virtual void v70() = 0;
	virtual void v74() = 0;
	virtual void v78() = 0;
	virtual void v7C() = 0;
	virtual void v80() = 0;
	virtual void v84() = 0;
	virtual void v88() = 0;
	virtual void v8C() = 0;
	virtual void v90() = 0;
	virtual void v94() = 0;
	virtual void v98() = 0;
	virtual void v9C() = 0;
	virtual void vA0() = 0;
	virtual void vA4() = 0;
	virtual void vA8() = 0;
	virtual void vAC() = 0;
	virtual void vB0() = 0;
	virtual void vB4() = 0;
	virtual void vB8() = 0;
	virtual void vBC() = 0;
	virtual void vC0() = 0;
	virtual void vC4() = 0;
	virtual void vC8() = 0;
	virtual void vCC() = 0;
	virtual void vD0() = 0;
	virtual void vD4() = 0;
	virtual void vD8() = 0;
	virtual void vDC() = 0;
	virtual void vE0() = 0;
	virtual void vE4() = 0;
	virtual void vE8() = 0;
	virtual void vEC() = 0;
	virtual void vF0() = 0;
	virtual void vF4() = 0;
	virtual void vF8() = 0;
	virtual void vFC() = 0;
	virtual void v100() = 0;
	virtual void v104() = 0;
	virtual void v108() = 0;
	virtual void v10C() = 0;
	virtual void v110() = 0;
	virtual void v114() = 0;
	virtual void v118() = 0;
	virtual void v11C() = 0;
	virtual void v120() = 0;
	virtual void v124() = 0;
	virtual void v128() = 0;
	virtual void v12C() = 0;
	virtual void v130() = 0;
	virtual void v134() = 0;
	virtual void v138() = 0;
	virtual void v13C() = 0;
	virtual void v140() = 0;
	virtual void v144() = 0;
	virtual void v148() = 0;
	virtual void v14C() = 0;
	virtual void v150() = 0;
	virtual void v154() = 0;
	virtual void v158() = 0;
	virtual int testPoint( void *param, Point2D *out ) = 0;
};

class Glo012F7048Shim
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual bool testPoint( void *param, Point2D *out ) = 0;
};

extern GloTacticalView00696040 *TheTacticalViewFadeShim;
extern Glo012F7048Shim *g_bfmeStateDF;

class Rva00696040Checker
{
	char m_pad604[0x604];
	int m_mode;

public:
	bool check( void *param );
};

// ?check@Rva00696040Checker@@QAE_NPAX@Z
bool Rva00696040Checker::check( void *param )
{
	Point2D pt;
	switch ( m_mode )
	{
	case 0:
		if ( TheTacticalViewFadeShim )
			return !TheTacticalViewFadeShim->testPoint( param, &pt );
		return false;
	case 1:
		if ( g_bfmeStateDF )
			return g_bfmeStateDF->testPoint( param, &pt );
		return false;
	default:
		return true;
	}
}




