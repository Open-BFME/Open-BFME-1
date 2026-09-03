// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x004628E0, 144 bytes. Free function: find-or-insert the named
// holder slot on the map at 0x012F1990, then assign the by-value functor
// holder (addref incoming, release the stored pointer through vslot 0).

class AsciiString
{
	void *m_data;
};

class FunctorWrapperHead
{
public:
	virtual ~FunctorWrapperHead();

	int m_refCount;
};

class Rva0050F840FunctorHolder
{
public:
	~Rva0050F840FunctorHolder()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
};

class AptScreenRefMap
{
public:
	Rva0050F840FunctorHolder *findOrInsert( const AsciiString &name );
};

AptScreenRefMap *const g_theAptScreenRefMap = (AptScreenRefMap *)0x012F1990;

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder incoming )
{
	FunctorWrapperHead *p;
	Rva0050F840FunctorHolder *slot = g_theAptScreenRefMap->findOrInsert( name );
	p = incoming.m_ptr;
	if( slot != &incoming )
	{
		if( p )
			++p->m_refCount;
		FunctorWrapperHead *old = slot->m_ptr;
		if( old && ( old->m_refCount = old->m_refCount - 1 ) <= 0 )
			delete old;
		slot->m_ptr = p;
	}
}
