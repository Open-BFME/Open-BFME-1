// Address-derived reconstruction of a member that resolves a nested object and
// returns the combined sizes of its two four-byte spans.

struct Rva003BDF70Span
{
	void **m_begin;
	void **m_end;
	int size() const { return m_end - m_begin; }
};

class Gen003C8A50Result
{
public:
	char m_pad00[ 0x54 ];
	Rva003BDF70Span m_first;             // +0x54
	char m_pad5C[ 0x4 ];
	Rva003BDF70Span m_second;            // +0x60
};

class Gen003C8A50
{
public:
	Gen003C8A50Result *find( const char *key );
};

class Rva003BDF70Owner
{
public:
	int combinedSpanCount();

private:
	char m_pad00[ 0x28 ];
	Gen003C8A50 *m_resolver;             // +0x28
	char m_pad2C[ 0x4 ];
	char m_key;                          // +0x30
};

int Rva003BDF70Owner::combinedSpanCount()
{
	if (!m_resolver)
		return 0;

	Gen003C8A50Result *result = m_resolver->find( &m_key );
	if (!result)
		return 0;

	return result->m_first.size() + result->m_second.size();
}

// cl: /DNDEBUG /MD /EHsc
