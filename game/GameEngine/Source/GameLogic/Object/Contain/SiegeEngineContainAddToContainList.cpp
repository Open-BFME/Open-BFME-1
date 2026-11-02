// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: SiegeEngineContain::addToContainList at retail 0x0022C160
// (251 bytes; ret 4 at +0xF8, int3 padding after).
//
// IDENTITY.  The constructor at 0x0022BC50 installs the secondary vtable at
// 0x010ACE08; its slot 35 routes through ILT 0x0003BF16 to this body, while
// slot 33 is the matched SiegeEngineContain::isValidContainerFor (0x0022BF30).
// The list, count and marker fields use the offsets of the matched sibling
// removeFromContainList (0x0022BE30).
//
// SHAPE.  Retail calls the contain list's push_back out of line (ILT
// 0x0001DE71 -> 0x000CFFE0, STLport list<T *>::push_back without exceptions)
// and still tail-jumps the final AI slot call, writing 10 over the parameter
// slot whose address push_back received.  VC7.1 keeps that tail call only when
// push_back is an inline member the optimiser declined to expand; a bare
// declaration marks the parameter address-taken here and forces call+ret.

enum KindOfType
{
	KINDOF_RVA0022C160_54 = 0x36
};

enum WeaponSetType
{
	WEAPONSET_RVA0022C160_20 = 0x14
};

class Player;

class SiegeEngineMemberAI
{
public:
#define SIEGE_ENGINE_AI_PAD( N ) virtual void slot##N();
	SIEGE_ENGINE_AI_PAD( 000 ) SIEGE_ENGINE_AI_PAD( 001 ) SIEGE_ENGINE_AI_PAD( 002 ) SIEGE_ENGINE_AI_PAD( 003 )
	SIEGE_ENGINE_AI_PAD( 004 ) SIEGE_ENGINE_AI_PAD( 005 ) SIEGE_ENGINE_AI_PAD( 006 ) SIEGE_ENGINE_AI_PAD( 007 )
	SIEGE_ENGINE_AI_PAD( 008 ) SIEGE_ENGINE_AI_PAD( 009 ) SIEGE_ENGINE_AI_PAD( 010 ) SIEGE_ENGINE_AI_PAD( 011 )
	SIEGE_ENGINE_AI_PAD( 012 ) SIEGE_ENGINE_AI_PAD( 013 ) SIEGE_ENGINE_AI_PAD( 014 ) SIEGE_ENGINE_AI_PAD( 015 )
	SIEGE_ENGINE_AI_PAD( 016 ) SIEGE_ENGINE_AI_PAD( 017 ) SIEGE_ENGINE_AI_PAD( 018 ) SIEGE_ENGINE_AI_PAD( 019 )
	SIEGE_ENGINE_AI_PAD( 020 ) SIEGE_ENGINE_AI_PAD( 021 ) SIEGE_ENGINE_AI_PAD( 022 ) SIEGE_ENGINE_AI_PAD( 023 )
	SIEGE_ENGINE_AI_PAD( 024 ) SIEGE_ENGINE_AI_PAD( 025 ) SIEGE_ENGINE_AI_PAD( 026 ) SIEGE_ENGINE_AI_PAD( 027 )
	SIEGE_ENGINE_AI_PAD( 028 ) SIEGE_ENGINE_AI_PAD( 029 ) SIEGE_ENGINE_AI_PAD( 030 ) SIEGE_ENGINE_AI_PAD( 031 )
	SIEGE_ENGINE_AI_PAD( 032 ) SIEGE_ENGINE_AI_PAD( 033 ) SIEGE_ENGINE_AI_PAD( 034 ) SIEGE_ENGINE_AI_PAD( 035 )
	SIEGE_ENGINE_AI_PAD( 036 ) SIEGE_ENGINE_AI_PAD( 037 ) SIEGE_ENGINE_AI_PAD( 038 ) SIEGE_ENGINE_AI_PAD( 039 )
	SIEGE_ENGINE_AI_PAD( 040 ) SIEGE_ENGINE_AI_PAD( 041 ) SIEGE_ENGINE_AI_PAD( 042 ) SIEGE_ENGINE_AI_PAD( 043 )
	SIEGE_ENGINE_AI_PAD( 044 ) SIEGE_ENGINE_AI_PAD( 045 ) SIEGE_ENGINE_AI_PAD( 046 ) SIEGE_ENGINE_AI_PAD( 047 )
	SIEGE_ENGINE_AI_PAD( 048 ) SIEGE_ENGINE_AI_PAD( 049 ) SIEGE_ENGINE_AI_PAD( 050 ) SIEGE_ENGINE_AI_PAD( 051 )
	SIEGE_ENGINE_AI_PAD( 052 ) SIEGE_ENGINE_AI_PAD( 053 ) SIEGE_ENGINE_AI_PAD( 054 ) SIEGE_ENGINE_AI_PAD( 055 )
	SIEGE_ENGINE_AI_PAD( 056 ) SIEGE_ENGINE_AI_PAD( 057 ) SIEGE_ENGINE_AI_PAD( 058 ) SIEGE_ENGINE_AI_PAD( 059 )
	SIEGE_ENGINE_AI_PAD( 060 ) SIEGE_ENGINE_AI_PAD( 061 ) SIEGE_ENGINE_AI_PAD( 062 ) SIEGE_ENGINE_AI_PAD( 063 )
	SIEGE_ENGINE_AI_PAD( 064 ) SIEGE_ENGINE_AI_PAD( 065 ) SIEGE_ENGINE_AI_PAD( 066 ) SIEGE_ENGINE_AI_PAD( 067 )
	SIEGE_ENGINE_AI_PAD( 068 ) SIEGE_ENGINE_AI_PAD( 069 ) SIEGE_ENGINE_AI_PAD( 070 ) SIEGE_ENGINE_AI_PAD( 071 )
	SIEGE_ENGINE_AI_PAD( 072 ) SIEGE_ENGINE_AI_PAD( 073 ) SIEGE_ENGINE_AI_PAD( 074 ) SIEGE_ENGINE_AI_PAD( 075 )
	SIEGE_ENGINE_AI_PAD( 076 ) SIEGE_ENGINE_AI_PAD( 077 ) SIEGE_ENGINE_AI_PAD( 078 ) SIEGE_ENGINE_AI_PAD( 079 )
	SIEGE_ENGINE_AI_PAD( 080 ) SIEGE_ENGINE_AI_PAD( 081 ) SIEGE_ENGINE_AI_PAD( 082 ) SIEGE_ENGINE_AI_PAD( 083 )
	SIEGE_ENGINE_AI_PAD( 084 ) SIEGE_ENGINE_AI_PAD( 085 ) SIEGE_ENGINE_AI_PAD( 086 ) SIEGE_ENGINE_AI_PAD( 087 )
	SIEGE_ENGINE_AI_PAD( 088 ) SIEGE_ENGINE_AI_PAD( 089 ) SIEGE_ENGINE_AI_PAD( 090 ) SIEGE_ENGINE_AI_PAD( 091 )
	SIEGE_ENGINE_AI_PAD( 092 ) SIEGE_ENGINE_AI_PAD( 093 ) SIEGE_ENGINE_AI_PAD( 094 ) SIEGE_ENGINE_AI_PAD( 095 )
	SIEGE_ENGINE_AI_PAD( 096 ) SIEGE_ENGINE_AI_PAD( 097 ) SIEGE_ENGINE_AI_PAD( 098 ) SIEGE_ENGINE_AI_PAD( 099 )
	SIEGE_ENGINE_AI_PAD( 100 ) SIEGE_ENGINE_AI_PAD( 101 ) SIEGE_ENGINE_AI_PAD( 102 ) SIEGE_ENGINE_AI_PAD( 103 )
	SIEGE_ENGINE_AI_PAD( 104 ) SIEGE_ENGINE_AI_PAD( 105 ) SIEGE_ENGINE_AI_PAD( 106 ) SIEGE_ENGINE_AI_PAD( 107 )
	SIEGE_ENGINE_AI_PAD( 108 ) SIEGE_ENGINE_AI_PAD( 109 ) SIEGE_ENGINE_AI_PAD( 110 ) SIEGE_ENGINE_AI_PAD( 111 )
	SIEGE_ENGINE_AI_PAD( 112 ) SIEGE_ENGINE_AI_PAD( 113 ) SIEGE_ENGINE_AI_PAD( 114 ) SIEGE_ENGINE_AI_PAD( 115 )
	SIEGE_ENGINE_AI_PAD( 116 ) SIEGE_ENGINE_AI_PAD( 117 ) SIEGE_ENGINE_AI_PAD( 118 ) SIEGE_ENGINE_AI_PAD( 119 )
	SIEGE_ENGINE_AI_PAD( 120 ) SIEGE_ENGINE_AI_PAD( 121 ) SIEGE_ENGINE_AI_PAD( 122 ) SIEGE_ENGINE_AI_PAD( 123 )
	SIEGE_ENGINE_AI_PAD( 124 ) SIEGE_ENGINE_AI_PAD( 125 ) SIEGE_ENGINE_AI_PAD( 126 )
#undef SIEGE_ENGINE_AI_PAD
	virtual void __declspec( nothrow ) invoke( int value );
};

class Thing
{
public:
	bool isKindOf( KindOfType type ) const;
	bool bfmeHasWeaponTemplateSet( WeaponSetType type ) const;

	char m_rva000[ 0x90 ];
	unsigned char m_rva090Flags;
};

class Gen001C9A10
{
public:
	void handle( int value );
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	char m_rva091[ 0x128 - 0x91 ];
	union
	{
		unsigned char m_rva128Byte;
		unsigned int m_rva128Bits;
	};
	union
	{
		unsigned char m_rva12CByte;
		unsigned int m_rva12CBits;
	};
	char m_rva130[ 0x204 - 0x130 ];
	SiegeEngineMemberAI *m_ai;
};

class Rva2225E0Filter
{
public:
	bool accepts( Object *object, Player *player );
};

class SiegeEngineModuleData
{
public:
	char m_rva000[ 0x224 ];
	Rva2225E0Filter m_filter;
	int m_capacity;
};

namespace _STL
{
	// STLport's node allocator entry point is the private
	// _STL::__node_alloc<true, 0>::_M_allocate (retail 0x0082E540); this
	// TU-local helper reaches it under its real name.
	static void *nodePoolAllocate(unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void *nodePoolAllocate(unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
	};
	static inline void *nodePoolAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
}

struct Rva000CFFE0Node
{
	Rva000CFFE0Node *m_next;
	Rva000CFFE0Node *m_prev;
	Object *m_data;
};

class Rva000CFFE0List
{
public:
	void push_back( Object *const &object )
	{
		Rva000CFFE0Node *pos = m_node;
		Rva000CFFE0Node *node = (Rva000CFFE0Node *)_STL::nodePoolAllocate( sizeof( Rva000CFFE0Node ) );
		Object **data = &node->m_data;
		if( data != 0 )
			*data = object;
		Rva000CFFE0Node *prev = pos->m_prev;
		node->m_next = pos;
		node->m_prev = prev;
		prev->m_next = node;
		pos->m_prev = node;
	}
	Rva000CFFE0Node *m_node;
};

struct Rva226790Object;

class SiegeEngineContainBase
{
public:
	virtual void slot00();

	SiegeEngineModuleData *m_moduleData;
	Object *m_object;
	char m_rva0C[ 0x20 - 0x0C ];
};

class Rva226790InsertAndCount
{
public:
	void insert( Rva226790Object *object );

#define CONTAIN_SLOT( N ) virtual void slot##N();
	CONTAIN_SLOT( 00 ) CONTAIN_SLOT( 01 ) CONTAIN_SLOT( 02 ) CONTAIN_SLOT( 03 ) CONTAIN_SLOT( 04 )
	CONTAIN_SLOT( 05 ) CONTAIN_SLOT( 06 ) CONTAIN_SLOT( 07 ) CONTAIN_SLOT( 08 ) CONTAIN_SLOT( 09 )
	CONTAIN_SLOT( 10 ) CONTAIN_SLOT( 11 ) CONTAIN_SLOT( 12 ) CONTAIN_SLOT( 13 ) CONTAIN_SLOT( 14 )
	CONTAIN_SLOT( 15 ) CONTAIN_SLOT( 16 ) CONTAIN_SLOT( 17 ) CONTAIN_SLOT( 18 ) CONTAIN_SLOT( 19 )
	CONTAIN_SLOT( 20 ) CONTAIN_SLOT( 21 ) CONTAIN_SLOT( 22 ) CONTAIN_SLOT( 23 ) CONTAIN_SLOT( 24 )
	CONTAIN_SLOT( 25 ) CONTAIN_SLOT( 26 ) CONTAIN_SLOT( 27 ) CONTAIN_SLOT( 28 ) CONTAIN_SLOT( 29 )
	CONTAIN_SLOT( 30 ) CONTAIN_SLOT( 31 ) CONTAIN_SLOT( 32 ) CONTAIN_SLOT( 33 ) CONTAIN_SLOT( 34 )
#undef CONTAIN_SLOT
	virtual void addToContainList( Object *object ) = 0;
};

class SiegeEngineContain : public SiegeEngineContainBase, public Rva226790InsertAndCount
{
public:
	virtual void addToContainList( Object *object );

	SiegeEngineModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	char m_rva020[ 0xE4 - 0x24 ];
	Rva000CFFE0List m_containList;
	int m_containCount;
	bool m_rvaECKindOf54;
};

void SiegeEngineContain::addToContainList( Object *object )
{
	Object *obj = object;
	if( obj == 0 )
		return;
	if( getObject()->m_rva090Flags & 1 )
		return;
	if( obj->m_rva090Flags & 1 )
		return;

	SiegeEngineModuleData *moduleData = getModuleData();
	if( moduleData->m_filter.accepts( obj, getObject()->getControllingPlayer() ) && moduleData->m_capacity > 0 )
	{
		m_containList.push_back( object );
		++m_containCount;
		if( obj->bfmeHasWeaponTemplateSet( WEAPONSET_RVA0022C160_20 ) )
		{
			( (Gen001C9A10 *)obj )->handle( 0x14 );
			if( ( obj->m_rva12CByte & 0x80 ) == 0 )
			{
				obj->m_rva12CBits |= 0x80;
				obj->notifyModelConditionChanged();
			}
		}
		if( obj->m_ai )
			return obj->m_ai->invoke( 10 );
		return;
	}

	if( ( obj->m_rva128Byte & 0x40 ) == 0 )
	{
		obj->m_rva128Bits |= 0x40;
		obj->notifyModelConditionChanged();
	}
	insert( (Rva226790Object *)obj );
	if( obj->isKindOf( KINDOF_RVA0022C160_54 ) )
		m_rvaECKindOf54 = true;
}
