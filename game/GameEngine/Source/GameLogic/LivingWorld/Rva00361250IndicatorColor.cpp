// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00361250, 113 bytes.  Bounds-checks an index into an STLport
// vector of 0x58-byte entries at +0x18 (the layout Gen00362760 walks), picks
// the entry's +0x1C colour when GlobalData::m_timeOfDay is 4 (night) and its
// +0x18 colour otherwise, hands it to the target's slot +0x28 drawable through
// Drawable::setIndicatorColor, then passes the index to the target through
// 0x001BF2E0.  No caller names the owner, so the names keep the address.  The
// STLport vector, not a raw begin/end pair, gives retail's ESI index and EDI
// begin.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Drawable
{
public:
	void setIndicatorColor( unsigned int color );
};

class Rva00361250Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable28();
};

// The ledger's name for the 0x001BF2E0 body that receives the target.
class Rva001BF2E0Source
{
public:
	void setAndNotify( int value );
};

struct Rva006C9270GlobalData
{
	char m_unmodelled[ 0x218 ];
	int m_timeOfDay;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

struct Rva00361250Entry
{
	char m_unmodelled00[ 0x18 ];
	unsigned int m_color18;
	unsigned int m_nightColor1C;
	char m_unmodelled20[ 0x38 ];
};

class Rva00361250Owner
{
public:
	void applyIndicatorColor( Rva00361250Target *target, int index );

private:
	char m_unmodelled[ 0x18 ];
	_STL::vector<Rva00361250Entry> m_entries;
};

void Rva00361250Owner::applyIndicatorColor( Rva00361250Target *target, int index )
{
	if( target == 0 || index < 0 || index > m_entries.size() )
		return;
	const Rva00361250Entry &entry = m_entries[ index ];
	unsigned int color = TheWritableGlobalData->m_timeOfDay == 4 ? entry.m_nightColor1C : entry.m_color18;
	Drawable *draw = target->getDrawable28();
	if( draw == 0 )
		return;
	draw->setIndicatorColor( color );
	( (Rva001BF2E0Source *)target )->setAndNotify( index );
}
