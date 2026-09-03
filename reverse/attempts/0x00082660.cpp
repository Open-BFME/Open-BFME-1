// ?getNicksForEmail@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z
// partial score=0.86 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// ?getNicksForEmail@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z
// ZH twin: WOLLoginMenu.cpp. Nick map lives at +0x20; empty list is a 0xC-byte
// circular sentinel; copy ctor and clear stay out of line.

class AsciiString
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString();

private:
	void *m_data;
};

void __cdecl node_dealloc( void *ptr, unsigned int size );

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A>
class list
{
public:
	__forceinline list()
	{
		void *node = ::operator new( 0xC );
		*(void **)node = node;
		*((void **)node + 1) = node;
		m_node = node;
	}
	list( const list &other );
	__forceinline ~list()
	{
		void *node = m_node;
		clear();
		node_dealloc( node, 0xC );
	}

	void clear();

private:
	void *m_node;
};

}

typedef _STL::list<AsciiString, _STL::allocator<AsciiString> > AsciiStringList;

struct NickMapNode
{
	unsigned char m_unreconstructed_00[ 4 ];
};

class NickMap
{
public:
	NickMapNode *find( const AsciiString &key );
	AsciiStringList &operator[]( const AsciiString &key );
	NickMapNode *end() const { return m_header; }

private:
	NickMapNode *m_header;
};

class UserPreferences
{
public:
	virtual ~UserPreferences();

private:
	unsigned char m_unreconstructed_04[ 0x10 ];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	AsciiStringList getNicksForEmail( AsciiString email );

private:
	unsigned char m_emailPasswordMap[ 0xC ];
	NickMap m_emailNickMap;
};

// ?getNicksForEmail@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z
AsciiStringList GameSpyLoginPreferences::getNicksForEmail( AsciiString email )
{
	if ( m_emailNickMap.find( email ) == m_emailNickMap.end() )
	{
		AsciiStringList empty;
		return empty;
	}
	return m_emailNickMap[ email ];
}
