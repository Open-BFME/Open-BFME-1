// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	int compare( const AsciiString &other ) const;
};

class BfmeDrawableWithID
{
public:
	unsigned int bfmeGetID(void);
};

class Rva006F9840Element
{
public:
	unsigned char m_padding0[0x28];
	int m_28;
	unsigned char m_padding2c[0x48 - 0x2c];
	unsigned int m_id;
	unsigned char m_padding4c[0x88 - 0x4c];
	unsigned char m_name_storage[0xc];
	unsigned char m_active;

	AsciiString *name() { return reinterpret_cast<AsciiString *>( m_name_storage ); }
};

struct Rva006F9840ListNode
{
	Rva006F9840ListNode *m_next;
	Rva006F9840ListNode *m_previous;
	Rva006F9840Element *m_element;
};

struct Rva006F9840List
{
	struct iterator
	{
		Rva006F9840Element *operator->() const { return m_node->m_element; }
		void operator++() { m_node = m_node->m_next; }
		bool operator!=( const iterator &other ) const { return m_node != other.m_node; }
		bool operator==( const iterator &other ) const { return m_node == other.m_node; }

		Rva006F9840ListNode *m_node;
	};

	iterator begin() const
	{
		iterator result = { m_head->m_next };
		return result;
	}

	iterator end() const
	{
		iterator result = { m_head };
		return result;
	}

	Rva006F9840ListNode *m_head;
};

// Address-derived manager for the shell's variant scheme lookup. Retail uses
// the manager at this+0x30A4 and forwards a raw AsciiString handle plus a
// by-value copy through ILT 0x00016793. The body below walks the linked list,
// compares drawable IDs and names, then updates the matching element.
class Rva006CCCA0Mgr
{
public:
	void setRva006CCCA0( void *rawHandle, AsciiString name );

private:
	unsigned char m_padding[0x20];
	Rva006F9840List m_list;
};

class Rva006CCCA0Owner
{
public:
	// ?loadSchemeVariant@Rva006CCCA0Owner@@QAEXPAXVAsciiString@@@Z
	void loadSchemeVariant( void *rawHandle, AsciiString name );

private:
	char m_unmodelled[ 0x30A8 ];
};

void Rva006CCCA0Owner::loadSchemeVariant( void *rawHandle, AsciiString name )
{
	if ( !*(Rva006CCCA0Mgr **)( m_unmodelled + 0x30A4 ) )
		return;

	( *(Rva006CCCA0Mgr **)( m_unmodelled + 0x30A4 ) )->setRva006CCCA0( rawHandle, name );
}

// ?setRva006CCCA0@Rva006CCCA0Mgr@@QAEXPAXVAsciiString@@@Z
void Rva006CCCA0Mgr::setRva006CCCA0( void *rawHandle, AsciiString name )
{
	Rva006CCCA0Mgr *self = this;
	if ( rawHandle != 0 )
	{
		Rva006F9840List::iterator node = self->m_list.begin();
		if ( node != self->m_list.end() )
		{
			while ( true )
			{
				unsigned int id = ((BfmeDrawableWithID *)rawHandle)->bfmeGetID();
				Rva006F9840Element *element = node.operator->();
				if ( id == element->m_id )
				{
					if ( element->name()->compare( name ) == 0 )
					{
						Rva006F9840Element *matched = node.operator->();
						matched->m_active = 1;
						matched->m_28 = 0;
						break;
					}
				}

				++node;
				if ( node == self->m_list.end() )
					break;
			}
		}
	}
}
