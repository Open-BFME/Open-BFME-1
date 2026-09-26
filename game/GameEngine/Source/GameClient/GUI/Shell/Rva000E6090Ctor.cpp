// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Byte-twin (tools/twin_scan.py) of ShellMenuScheme::ShellMenuScheme (retail
// 0x00580F20, ShellMenuScheme.cpp): an empty-body ctor that default-constructs a
// leading member and two std::list<T*> members. Where the twin stores NULL into
// its leading AsciiString, retail 0x000E6090 stores the address of a four-entry
// function table at 0x01084C40 (tools/vtable_lookup.py: four jump thunks) --
// at the SAME point, before EH state 0, i.e. as the inline ctor of a leading
// member that owns a pointer to that table and has an out-of-line dtor, not as
// a vptr install (a polymorphic class puts the this-save after the state
// push and compiles 5 bytes short). No matched caller names the owner, so it
// stays address-derived per the twin-lane identity policy.

class Rva000E6090ImageItem;
class Rva000E6090LineItem;

#include <list>

typedef void (*Rva000E6090Handler)(void);
extern const Rva000E6090Handler g_Rva000E6090Handlers[4];   // 0x01084C40

class Rva000E6090Dispatch
{
public:
	Rva000E6090Dispatch(void) : m_handlers(g_Rva000E6090Handlers) {}
	~Rva000E6090Dispatch(void);

private:
	const Rva000E6090Handler *m_handlers;
};

class Rva000E6090
{
public:
	Rva000E6090(void);

	Rva000E6090Dispatch m_dispatch;
	_STL::list<Rva000E6090ImageItem *> m_imageList;
	_STL::list<Rva000E6090LineItem *> m_lineList;
};

Rva000E6090::Rva000E6090(void)
{
}
