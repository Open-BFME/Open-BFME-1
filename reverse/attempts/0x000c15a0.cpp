// ?parseAttributeModifierAura@Rva000C15A0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.2 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: INI field parser at 0x000C15A0 (227 B). Parses an
// AsciiString vector via the already-matched INI::parseAsciiStringVector
// into a local temporary, allocates a 20-byte node with a self-referencing
// pair of header pointers at +8/+0xc (an _Rb_tree/_List sentinel init),
// hands the temporary vector and the new node to a five/six-argument
// helper (still-unmatched thunk 0x00019C45), then destructs the temporary
// std::set<AsciiString> (its dtor is separately pinned,
// ??1?$_Rb_tree@VAsciiString@@...) and an
// AttributeModifierAuraUpdateModuleDataMemberB temporary/subobject. Given
// the two unmatched callees this is a rough control-flow skeleton only,
// not yet byte-verified; the real class and member relationships are
// unrecovered.

class INI;

class AsciiString
{
public:
	AsciiString();
	~AsciiString();
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	~vector();
};
}

class INI
{
public:
	static void parseAsciiStringVector( INI *ini, void *instance, void *store, const void *userData );
};

struct Rva000C15A0Node
{
	char m_a;
	char m_pad[ 3 ];
	Rva000C15A0Node *m_left;
	Rva000C15A0Node *m_right;
};

extern "C" void __cdecl Rva000C15A0Helper( void *instance, Rva000C15A0Node *node,
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > *names, void *store, bool flag );

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();
};

class Rva000C15A0
{
public:
	static void parseAttributeModifierAura( INI *ini, void *instance, void *store, const void * );
};

// ?parseAttributeModifierAura@Rva000C15A0@@SAXPAVINI@@PAX1PBX@Z
void Rva000C15A0::parseAttributeModifierAura( INI *ini, void *instance, void *store, const void * )
{
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > names;
	names._M_start = 0;
	names._M_finish = 0;
	names._M_end_of_storage = 0;
	INI::parseAsciiStringVector( ini, instance, &names, 0 );

	Rva000C15A0Node *node = (Rva000C15A0Node *)::operator new( 0x14 );
	node->m_a = 0;
	node->m_left = node;
	node->m_right = node;

	Rva000C15A0Helper( instance, node, &names, store, true );

	AttributeModifierAuraUpdateModuleDataMemberB member;
	(void)member;
}
