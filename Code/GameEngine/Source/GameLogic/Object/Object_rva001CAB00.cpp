// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Method of a subobject at host+0x70: walk OVERRIDE at host+4
// (this-0x6C), test KindOf bit 2, else return host+0x214 or &host.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;
	void *m_head;
	Overridable *m_nextOverride;
};

class Rva001CAB00Thing : public Overridable
{
public:
	char m_gap[ 0xC8 - 8 ];
	unsigned char m_kindof;
};

class Rva001CAB00
{
public:
	void *query();
};

void *Rva001CAB00::query()
{
	char *self = (char *)this;
	Rva001CAB00Thing *thing = *(Rva001CAB00Thing **)( self - 0x6C );
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001CAB00Thing *)thing->m_nextOverride->getFinalOverride();
	}
	if ( thing->m_kindof & 4 )
		return (void *)1;
	void *p = *(void **)( self + 0x1A4 );
	if ( p )
		return p;
	return self - 0x70;
}
