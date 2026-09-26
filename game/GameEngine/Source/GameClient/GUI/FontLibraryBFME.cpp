// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// BFME FontLibrary has the ordinary subsystem prefix and two small STLport
// trees after the font-list fields.  The retail vtable/caller chain, rather
// than the older Zero Hour header, is the source of this layout.

#include <map>

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	unsigned char m_bfmeHead[4];
};

class GameFont;

struct Gen_t_00475950_p4pod
{
	int value;
};

struct Gen_t_004759f0_p4pod
{
	int value;
};

typedef _STL::map<int, Gen_t_00475950_p4pod> FontTreeA;
typedef _STL::map<int, Gen_t_004759f0_p4pod> FontTreeB;

class FontLibrary : public SubsystemInterface
{
public:
	virtual ~FontLibrary();
	virtual void fontLibraryAnchor() = 0;

	protected:
	void deleteAllFonts();

	public:
	GameFont *m_fontList;
	int m_count;
	FontTreeA m_fontTreeA;
	FontTreeB m_fontTreeB;
};

FontLibrary::~FontLibrary()
{
	deleteAllFonts();
}
