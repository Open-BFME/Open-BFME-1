// cl: /DNDEBUG /MD /EHsc

// The retail body walks a circular list whose sentinel pointer is stored at
// this+0x99C and returns the number of nodes.  The owning class identity is not
// recovered, so only the byte-proven layout and behavior are named here.
struct Rva0021B1E0Node
{
	Rva0021B1E0Node *m_next;
};

class Rva0021B1E0ListOwner
{
public:
	unsigned int size() const;

private:
	unsigned char m_lead[ 0x99C ];
	Rva0021B1E0Node *m_sentinel;
};

unsigned int Rva0021B1E0ListOwner::size() const
{
	Rva0021B1E0Node *sentinel = m_sentinel;
	Rva0021B1E0Node *node = sentinel->m_next;
	unsigned int count = 0;
	while ( node != sentinel )
	{
		node = node->m_next;
		++count;
	}
	return count;
}
