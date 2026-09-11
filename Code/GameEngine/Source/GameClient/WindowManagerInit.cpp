// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager::init.  The constructor's vtable at 0x010F72A8 names this
// body as slot 1; the slot layout and APT/vector offsets are shared with the
// existing WindowManager constructor and destructor models.

#include "../../../../reference/shims/stringinline/StringInline.h"

#include <vector>

class Gen_004659D0
{
public:
	Gen_004659D0();
	void setBfmeT() { m_bfmeT = 1; }

private:
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
	int m_bfmeF;
	int m_bfmeG;
	int m_bfmeH;
	int m_bfmeI;
	int m_bfmeJ;
	int m_bfmeK;
	int m_bfmeL;
	int m_bfmeM;
	int m_bfmeN;
	int m_bfmeO;
	int m_bfmeP;
	int m_bfmeQ;
	int m_bfmeR;
	int m_bfmeS;
	unsigned char m_bfmeT;
	unsigned char m_bfmeU;
};

void configureWindowParameters( Gen_004659D0 *parameters );

#pragma comment(linker, "/alternatename:?configureWindowParameters@@YAXPAVGen_004659D0@@@Z=?d_00894800@@YAXXZ")

extern void j_00025086();
extern void j_00039f1d();
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva8CD130IdleHook;

class WindowManager
{
public:
	#define WINDOW_MANAGER_SLOT( n ) virtual void windowManagerSlot##n() = 0
	WINDOW_MANAGER_SLOT( 0 ); WINDOW_MANAGER_SLOT( 1 ); WINDOW_MANAGER_SLOT( 2 );
	WINDOW_MANAGER_SLOT( 3 ); WINDOW_MANAGER_SLOT( 4 ); WINDOW_MANAGER_SLOT( 5 );
	WINDOW_MANAGER_SLOT( 6 ); WINDOW_MANAGER_SLOT( 7 ); WINDOW_MANAGER_SLOT( 8 );
	WINDOW_MANAGER_SLOT( 9 ); WINDOW_MANAGER_SLOT( 10 ); WINDOW_MANAGER_SLOT( 11 );
	WINDOW_MANAGER_SLOT( 12 ); WINDOW_MANAGER_SLOT( 13 ); WINDOW_MANAGER_SLOT( 14 );
	#undef WINDOW_MANAGER_SLOT
	virtual int loadAptWindow( AsciiString directory, AsciiString file,
		int unknown1, int unknown2, int unknown3 ) = 0;
	virtual void init();

private:
	char m_unmodelled[ 0xA4 ];
	struct AptWindow
	{
		char m_unmodelled[ 0x10 ];
		unsigned char m_flags;
		char m_padding[ 3 ];
	} m_aptWindows[ 12 ];
	_STL::vector<int> m_values198;
	unsigned char m_valuesChanged1A4;
};

void WindowManager::init()
{
	Gen_004659D0 parameters;
	parameters.setBfmeT();
	int windowIndex;
	configureWindowParameters( &parameters );
	*reinterpret_cast< unsigned int * >(
		reinterpret_cast< unsigned char * >( &g_rva8CD130IdleHook ) + 8 ) |= 2;
	j_00025086();
	j_00039f1d();

	windowIndex = loadAptWindow(
		"Apt\\", "AptLevel0.apt", 1, 0, 0 );
	m_values198.clear();
	m_values198.push_back( 12 );
	m_valuesChanged1A4 = 1;
	m_aptWindows[ windowIndex ].m_flags &= ~4;
}
