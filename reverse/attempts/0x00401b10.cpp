// ?update@Rva00401B10Owner@@QAEXIPAV?@HV?@H@_STL@@@_STL@@@Z
// partial score=0.93 date=2026-09-19
// cl: /DNDEBUG /MD /EHs-c-
// stlport

#include <vector>

struct Rva00401B10Payload
{
	int m_first;
	int m_second;
	int m_third;
};

struct Rva00401B10Node
{
	char m_unmodelled00[ 8 ];
	Rva00401B10Node *m_next;
	Rva00401B10Payload m_payload;
	char m_unmodelled18[ 8 ];
	int m_key;
};

class Rva00401B10Owner
{
public:
	void update( unsigned int key, std::vector<int> *output );

private:
	char m_unmodelled00[ 4 ];
	Rva00401B10Node *m_head;
	Rva00401B10Node *m_tail;
	char m_unmodelled0c[ 4 ];
	Rva00401B10Node *m_current;
	Rva00401B10Payload m_payload;
	int m_unmodelled20;
};

void Rva00401B10Owner::update( unsigned int key, std::vector<int> *output )
{
	Rva00401B10Owner *self = this;
	if( self->m_head == 0 || self->m_current == 0 || key == 0x7FFFFFFF )
		return;

	Rva00401B10Node *node;
	while( self->m_current != 0 )
	{
		node = self->m_current;
		if( node->m_key == key )
			break;
		self->m_payload = node->m_payload;
		Rva00401B10Node *next = node->m_next;
		self->m_current = next;
	}

	while( self->m_current != 0 &&
		self->m_current->m_key != 0x7FFFFFFF )
	{
		if( self->m_current->m_next == 0 ||
			self->m_current->m_next->m_key == 0x7FFFFFFF )
			break;
		output->push_back( self->m_current->m_key );
		self->m_payload = self->m_current->m_payload;
		self->m_current = self->m_current->m_next;
	}

	if( self->m_current == 0 )
		self->m_current = self->m_tail;
	if( self->m_current != 0 )
		self->m_payload = self->m_current->m_payload;
	self->m_unmodelled20 = 0;
}
