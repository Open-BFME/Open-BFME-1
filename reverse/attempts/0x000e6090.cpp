// ??0Rva000E6090@@QAE@XZ
// partial score=0.7 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// twin of ShellMenuScheme::ShellMenuScheme (retail 0x00580F20, matched in
// ShellMenuScheme.cpp): an empty-body ctor whose only work is default
// constructing two std::list<T*> members. Retail 0x000E6090 differs by
// installing a vtable (0x01084C40, tools/vtable_lookup.py names only jump
// thunks for its four slots) at +0x0 instead of ShellMenuScheme's leading
// AsciiString m_name, so this is a distinct, virtual class with the same
// two-list tail layout. No matched caller or ZH source names it, so it lands
// address-derived per the twin-lane identity policy.

class Rva000E6090ImageItem;
class Rva000E6090LineItem;

#include <list>

class Rva000E6090
{
public:
	Rva000E6090(void);
	virtual ~Rva000E6090(void);

	_STL::list<Rva000E6090ImageItem *> m_imageList;
	_STL::list<Rva000E6090LineItem *> m_lineList;
};

Rva000E6090::Rva000E6090(void)
{
}
