// ??0ObjectSMCHelper@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.89 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: constructor of a class deriving from ObjectHelper and
// installing three vtables (multiple-inheritance module-style layout) plus
// one embedded intrusive list-style member, retail 0x001C54A0, 113 bytes.
// The base ctor (pinned 0x00021BE8) runs first, then the three vtable
// pointers are stored as literal constants, then the list member is zeroed
// and a 16-byte sentinel node (8 overhead + 8 value) is allocated through
// __node_alloc::_M_allocate and self-linked.  Owning class/real member types
// are unidentified (address-derived tag); a Zero Hour twin was suggested for
// SmartBombTargetHomingUpdate but its source does not reproduce this shape,
// so the identity is left open per a prior partial attempt (score 0.88).

class Thing;
class ModuleData;

class ObjectHelper
{
public:
	ObjectHelper( Thing *, const ModuleData * );
	~ObjectHelper();
private:
	unsigned char m_bfmeBase[ 0x20 ];
};

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( unsigned int n );
};
}

struct Rva001C54A0Node
{
	Rva001C54A0Node *m_next;
	Rva001C54A0Node *m_prev;
	int m_v0;
	int m_v1;
};

class ObjectSMCHelper : public ObjectHelper
{
public:
	ObjectSMCHelper( Thing *thing, const ModuleData *moduleData );
private:
	Rva001C54A0Node *m_list;
};

ObjectSMCHelper::ObjectSMCHelper( Thing *thing, const ModuleData *moduleData )
	: ObjectHelper( thing, moduleData )
{
	*reinterpret_cast<void *volatile *>( this ) = reinterpret_cast<void *>( 0x0109ebbc );
	*reinterpret_cast<void *volatile *>( reinterpret_cast<char *>( this ) + 0x0c ) = reinterpret_cast<void *>( 0x0109eaf8 );
	*reinterpret_cast<void *volatile *>( reinterpret_cast<char *>( this ) + 0x10 ) = reinterpret_cast<void *>( 0x0109eaec );
	m_list = 0;
	Rva001C54A0Node *node = (Rva001C54A0Node *)_STL::__new_alloc::allocate( sizeof( char[ 0x10 ] ) );
	node->m_next = node;
	node->m_prev = node;
	m_list = node;
}
