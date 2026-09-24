// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// AI::parseAttackPriority reads the AttackPriority field from the AIData block.
// The FieldParse table at 0x01094B00 maps that field to retail 0x0014E130.
// The ILT constructor pin at 0x000026BC names AINamedListNode. AI::newOverride
// uses that constructor when it copies these nodes.
// This body searches TAiData::m_namedLists at +0xF4, clears or adds a node, then
// parses its Target table at 0x010959F4.

#include "ascii_string.h"
#include <list>

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const void *fieldParse );
};

struct Gen_t_0014bd80_p8cd
{
	int m_words[ 2 ];
	Gen_t_0014bd80_p8cd();
	Gen_t_0014bd80_p8cd( const Gen_t_0014bd80_p8cd &that );
	~Gen_t_0014bd80_p8cd();
	Gen_t_0014bd80_p8cd &operator=( const Gen_t_0014bd80_p8cd &that );
};

typedef _STL::list<Gen_t_0014bd80_p8cd> AINamedListTail;

class AINamedListNode
{
public:
	AINamedListNode( AsciiString name );

	void *m_vtable;
	AsciiString m_name;
	unsigned int m_value;
	AINamedListTail m_tail;
	AINamedListNode *m_next;
};

class TAiData
{
public:
	unsigned char m_unmodelled_000[ 0xF4 ];
	AINamedListNode *m_namedLists;
};

class AI
{
public:
	static void parseAttackPriority( INI *ini, void *instance, void *store, const void *userData );
};

void AI::parseAttackPriority( INI *ini, void *instance, void *, const void * )
{
	AsciiString name( ini->getNextToken() );
	TAiData *data = (TAiData *)instance;
	AINamedListNode *node = data->m_namedLists;
	while( node != 0 )
	{
		if( name.compare( node->m_name ) == 0 )
		{
			node->m_tail.clear();
			break;
		}
		node = node->m_next;
	}

	if( node == 0 )
	{
		node = new AINamedListNode( name );
		node->m_next = data->m_namedLists;
		data->m_namedLists = node;
	}

	ini->initFromINI( node, (const void *)0x010959F4 );
}
