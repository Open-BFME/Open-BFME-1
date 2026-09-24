// ?format_0046CF80@Rva0046CF80Owner@@QAEPADPBD@Z
// partial score=0.65 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager stores each player-color callback with the argument that the
// callback receives. The callback map starts at WindowManager+0x1C.

#include "StringInline.h"
#include <exception>
#include <hash_map>

class FunctorWrapperHead
{
public:
	virtual ~FunctorWrapperHead();

	int m_refCount;
};

class Rva0050F920FunctorHolder
{
public:
	Rva0050F920FunctorHolder( const Rva0050F920FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0050F920FunctorHolder()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
};

struct Rva0046C2A0Mapped
{
	Rva0046C2A0Mapped() : m_ptr( 0 ), m_value( 0 ) {}

	Rva0046C2A0Mapped( const Rva0046C2A0Mapped &other )
		: m_ptr( other.m_ptr ), m_value( other.m_value )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0046C2A0Mapped()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
	void *m_value;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()( AsciiString value ) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

typedef std::hash_map<AsciiString, Rva0046C2A0Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C2A0Map;

class WindowManager
{
public:
	void bindShownWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

private:
	unsigned char m_pad[0x1C];
	Rva0046C2A0Map m_callbacks;
};

// ?bindShownWithArg@WindowManager@@QAEXABVAsciiString@@PAXVRva0050F920FunctorHolder@@@Z
void WindowManager::bindShownWithArg( const AsciiString &name, void *argument,
	Rva0050F920FunctorHolder callback )
{
	if( callback.m_ptr == 0 )
		return;

	Rva0046C2A0Mapped *slot = &m_callbacks[name];
	Rva0050F920FunctorHolder previous(
		*reinterpret_cast<Rva0050F920FunctorHolder *>( slot ) );
	if( previous.m_ptr != 0 )
		return;
	if( slot != reinterpret_cast<Rva0046C2A0Mapped *>( &callback ) )
	{
		if( callback.m_ptr )
			++callback.m_ptr->m_refCount;
		FunctorWrapperHead *old = slot->m_ptr;
		if( old && ( old->m_refCount = old->m_refCount - 1 ) <= 0 )
			delete old;
		slot->m_ptr = callback.m_ptr;
	}
	slot->m_value = argument;
}


class BFMERetailAsciiString
{
public:
    BFMERetailAsciiString(const char *text);
    ~BFMERetailAsciiString() { releaseBuffer(); }
private:
    void releaseBuffer();
    void *m_data;
};
class FunctorNotSet : public std::exception
{
public:
    FunctorNotSet() : std::exception() {}
};
class Rva0046CF80Callback
{
public:
    virtual ~Rva0046CF80Callback();
    virtual void invoke(void *value, char *buffer, int flags);
};
typedef _STL::pair<const AsciiString, Rva0046C2A0Mapped> Rva0046CF80Pair;
typedef _STL::_Hashtable_node<Rva0046CF80Pair> Rva0046CF80Node;
extern const char *__cdecl bfmeSkipLevelPrefix(const char *text);
class Rva0046CF80Owner
{
public:
    char *format_0046CF80(const char *name);
private:
    unsigned char m_pad[0x1C];
    Rva0046C2A0Map m_callbacks;
};
char *Rva0046CF80Owner::format_0046CF80(const char *name)
{
    char *result = new char[255];
    result[0] = 0;
    Rva0046CF80Node *found;
    {
        BFMERetailAsciiString key(name);
        const Rva0046C2A0Map *map = &m_callbacks;
        found = map->find(reinterpret_cast<const AsciiString &>(key))._M_cur;
    }
    if (found == 0) {
        BFMERetailAsciiString key(bfmeSkipLevelPrefix(name));
        const Rva0046C2A0Map *map = &m_callbacks;
        found = map->find(reinterpret_cast<const AsciiString &>(key))._M_cur;
    }
    if (found != 0) {
        void *value = found->_M_val.second.m_value;
        Rva0046CF80Callback *callback = reinterpret_cast<Rva0046CF80Callback *>(found->_M_val.second.m_ptr);
        if (callback == 0)
            throw FunctorNotSet();
        callback->invoke(value, result, 0);
    }
    return result;
}
