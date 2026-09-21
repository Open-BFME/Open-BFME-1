// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Address-derived leaf recoveries from the 2026-09-20 carved batch.
#include "PreRTS.h"
#include "Common/AsciiString.h"

#define _BFME_RETAIL_TREE_INSERT_LAYOUT

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

struct Rva00142EE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00142EE0Value> Rva00142EE0Pair;
typedef _STL::_Rb_tree<AsciiString, Rva00142EE0Pair,
	_STL::_Select1st<Rva00142EE0Pair>, _STL::less<AsciiString>,
	_STL::allocator<Rva00142EE0Pair> > Rva00142EE0Tree;
typedef _STL::pair<Rva00142EE0Tree::iterator, bool> Rva00145030Result;

extern template Rva00145030Result
Rva00142EE0Tree::insert_unique( const Rva00142EE0Pair & );

class Rva00145030Owner
{
public:
	Rva00145030Result invoke( const void *value );
};

// ?invoke@Rva00145030Owner@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@URva00142EE0Value@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@URva00142EE0Value@@@_STL@@@2@@_STL@@_N@_STL@@PBX@Z
Rva00145030Result Rva00145030Owner::invoke( const void *value )
{
	return reinterpret_cast<Rva00142EE0Tree *>(this)->insert_unique( *reinterpret_cast<const Rva00142EE0Pair *>(value) );
}

struct Rva001430D0Value
{
	AsciiString m_key;
};

struct Rva001430D0KeyOfValue
{
	const AsciiString &operator()( const Rva001430D0Value &value ) const
	{
		return value.m_key;
	}
};

typedef _STL::_Rb_tree<AsciiString, Rva001430D0Value, Rva001430D0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva001430D0Value> > Rva001430D0Tree;

extern template _STL::_Rb_tree_node<Rva001430D0Value> *
Rva001430D0Tree::_M_find<AsciiString>( const AsciiString & ) const;

extern void j_00040430();

class Rva00145050FindRoute
{
public:
	typedef _STL::_Rb_tree_node<Rva001430D0Value> *(Rva00145050FindRoute::*Call)(const AsciiString &) const;
};

struct Rva00145050Result
{
	void *m_node;
	Rva00145050Result( void *node ) : m_node( node ) {}
};

class Rva00145050Owner
{
public:
	Rva00145050Result find( const void *key ) const;
};

// ?find@Rva00145050Owner@@QBE?AURva00145050Result@@PBX@Z
Rva00145050Result Rva00145050Owner::find( const void *key ) const
{
	union { void (*address)(); Rva00145050FindRoute::Call member; } route = { j_00040430 };
	return Rva00145050Result( (reinterpret_cast<const Rva00145050FindRoute *>(this)->*route.member)( *reinterpret_cast<const AsciiString *>(key) ) );
}

class Rva00148700Owner
{
public:
	unsigned char get() const;

	char m_padding[ 0x24 ];
	unsigned char m_value;
};

// ?get@Rva00148700Owner@@QBEEXZ
unsigned char Rva00148700Owner::get() const
{
	return m_value;
}

class Rva00148720Owner
{
public:
	float get() const;

	char m_padding[ 0x44 ];
	float m_value;
};

// ?get@Rva00148720Owner@@QBEMXZ
float Rva00148720Owner::get() const
{
	return m_value;
}

// ?Rva001487E0False@@YA_NXZ
bool Rva001487E0False()
{
	return false;
}

// Retail RVA 0x001487F0 contains only ret.
void Rva001487F0Noop()
{
}

class Rva0014A850Owner
{
public:
	Rva0014A850Owner *self();
};

// ?self@Rva0014A850Owner@@QAEPAV1@XZ
Rva0014A850Owner *Rva0014A850Owner::self()
{
	return this;
}

class Rva0014A9F0Owner
{
public:
	char *get() const;

	char *m_value;
};

// ?get@Rva0014A9F0Owner@@QBEPADXZ
char *Rva0014A9F0Owner::get() const
{
	return m_value + 8;
}

class Rva0014E600Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x10 ];
	unsigned int m_value;
};

// ?get@Rva0014E600Owner@@QBEIXZ
unsigned int Rva0014E600Owner::get() const
{
	return m_value;
}

class Rva0015E6C0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x10 ];
	unsigned int m_value;
};

// ?get@Rva0015E6C0Owner@@QBEIXZ
unsigned int Rva0015E6C0Owner::get() const
{
	return m_value;
}

class Rva0015E6D0Owner
{
public:
	char *get();

	char m_padding[ 0x44 ];
	char m_value;
};

// ?get@Rva0015E6D0Owner@@QAEPADXZ
char *Rva0015E6D0Owner::get()
{
	return &m_value;
}

class Rva0015E6F0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x50 ];
	unsigned int m_value;
};

// ?get@Rva0015E6F0Owner@@QBEIXZ
unsigned int Rva0015E6F0Owner::get() const
{
	return m_value;
}

class Rva0015E710Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x1c ];
	unsigned int m_value;
};

// ?get@Rva0015E710Owner@@QBEIXZ
unsigned int Rva0015E710Owner::get() const
{
	return m_value;
}

class Rva0015F6C0Owner
{
public:
	char *get();

	char m_padding[ 0x24 ];
	char m_value;
};

// ?get@Rva0015F6C0Owner@@QAEPADXZ
char *Rva0015F6C0Owner::get()
{
	return &m_value;
}

class Rva0015F6E0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x0c ];
	unsigned int m_value;
};

// ?get@Rva0015F6E0Owner@@QBEIXZ
unsigned int Rva0015F6E0Owner::get() const
{
	return m_value;
}

class Rva0015F6F0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x10 ];
	unsigned int m_value;
};

// ?get@Rva0015F6F0Owner@@QBEIXZ
unsigned int Rva0015F6F0Owner::get() const
{
	return m_value;
}

class Rva0015F700Owner
{
public:
	unsigned char get() const;

	char m_padding[ 0x18 ];
	unsigned char m_value;
};

// ?get@Rva0015F700Owner@@QBEEXZ
unsigned char Rva0015F700Owner::get() const
{
	return m_value;
}

class Rva0015F710Owner
{
public:
	char *get();

	char m_padding[ 0x1c ];
	char m_value;
};

// ?get@Rva0015F710Owner@@QAEPADXZ
char *Rva0015F710Owner::get()
{
	return &m_value;
}

class Rva0015FD60Owner
{
public:
	void clear( void *value );
};

// ?clear@Rva0015FD60Owner@@QAEXPAX@Z
void Rva0015FD60Owner::clear( void *value )
{
}

class Rva00168650Owner
{
public:
	float get() const;

	char m_padding[ 0x20 ];
	float m_value;
};

// ?get@Rva00168650Owner@@QBEMXZ
float Rva00168650Owner::get() const
{
	return m_value;
}

// ?Rva001686E0True@@YA_NXZ
bool Rva001686E0True()
{
	return true;
}

class Rva0016AD40Owner
{
public:
	void clear( void *value );
};

// ?clear@Rva0016AD40Owner@@QAEXPAX@Z
void Rva0016AD40Owner::clear( void *value )
{
}

class Rva0016AEC0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x50 ];
	unsigned int m_value;
};

// ?get@Rva0016AEC0Owner@@QBEIXZ
unsigned int Rva0016AEC0Owner::get() const
{
	return m_value;
}

class Rva0016AED0Owner
{
public:
	unsigned int get() const;

	char m_padding[ 0x54 ];
	unsigned int m_value;
};

// ?get@Rva0016AED0Owner@@QBEIXZ
unsigned int Rva0016AED0Owner::get() const
{
	return m_value;
}

class Rva0016B920Owner
{
public:
	Rva0016B920Owner *self();
};

// ?self@Rva0016B920Owner@@QAEPAV1@XZ
Rva0016B920Owner *Rva0016B920Owner::self()
{
	return this;
}

// ?Rva0016C980Zero@@YAHXZ
int Rva0016C980Zero()
{
	return 0;
}
