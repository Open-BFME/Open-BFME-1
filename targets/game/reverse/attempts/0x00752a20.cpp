// ?method@Rva00752A20@@QBE_NABU1@M@Z
// partial score=0.3381 date=2026-10-05
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/drawable /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "GameClient/Drawable.h"
#include <math.h>

class Rva00765AC0
{
public:
	unsigned char ready( void ) const;
};

class GameLODManager;
struct Rva00752A20LODView { char m_pad00[0x170c]; int m_field170c; };

extern GameLODManager *TheGameLODManager;

struct Rva00752A20Entry
{
 unsigned int m_field00;
 float m_field04;
 char m_pad08[8];
 unsigned int m_field10;
 unsigned int m_field14;
 char m_pad18[4];
};

struct Q4Sort00751F50Record
{
	char m_pad00[ 8 ];
	Drawable *m_drawable;
	char m_pad0c[ 8 ];
	Rva00765AC0 *m_state;
	char m_pad18[0xdc-0x18];
	Rva00752A20Entry m_entries[2];

	bool compare( const Q4Sort00751F50Record &other, int *outLeft,
		int *outRight ) const;
};

// Retail RVA 0x00751F50. The comparator at 0x00752B80 calls this helper with
// the two nested records and two output slots. The call chain identifies the
// Drawable and ready checks, while the retail offsets identify this record's
// fields at +0x08 and +0x14.
bool Q4Sort00751F50Record::compare( const Q4Sort00751F50Record &other,
	int *outLeft, int *outRight ) const
{
	*outRight = 0;
	*outLeft = 0;
	if ( m_state == 0 )
		return false;
	else
	{
		if ( m_state != other.m_state )
			return false;

		int divisor = 3;
		if ( ((const Rva00752A20LODView *)TheGameLODManager)->m_field170c == 0 )
			divisor = 1;
		*outLeft = m_drawable->getID() % divisor;
		*outRight = other.m_drawable->getID() % divisor;
		return m_state->ready();
	}
}

struct Rva00752A20DrawableView { char m_pad00[0x1f8]; float m_field1f8; };

static __forceinline bool rva00752A20Fallback(const Q4Sort00751F50Record &lhs,
 const Q4Sort00751F50Record &rhs, float tolerance)
{
 const Rva00752A20Entry *left = lhs.m_entries;
 const Rva00752A20Entry *right = rhs.m_entries;
 for (int i=0; i<=1; ++i, ++left, ++right)
 {
  if (left->m_field00 != right->m_field00) return false;
  if (left->m_field00)
  {
   if (left->m_field14 != right->m_field14) return false;
   if (left->m_field10 != right->m_field10) return false;
  }
 }
 if (fabs(lhs.m_entries[0].m_field04-rhs.m_entries[0].m_field04)>tolerance) return false;
 if (lhs.m_entries[1].m_field00 &&
     fabs(lhs.m_entries[1].m_field04-rhs.m_entries[1].m_field04)>tolerance) return false;
 return true;
}

struct Rva00752A20
{
 unsigned int m_field00;
 Q4Sort00751F50Record *m_field04;
 unsigned int m_field08;
 bool method(const Rva00752A20 &other, float tolerance) const;
};

bool Rva00752A20::method(const Rva00752A20 &other,float tolerance) const
{
 if (((const Rva00752A20LODView *)TheGameLODManager)->m_field170c==4) return false;
 if (m_field00!=other.m_field00 || m_field08!=other.m_field08) return false;
 if (((const Rva00752A20DrawableView *)m_field04->m_drawable)->m_field1f8 !=
     ((const Rva00752A20DrawableView *)other.m_field04->m_drawable)->m_field1f8) return false;
 if (m_field04 && other.m_field04)
 {
  int leftResult,rightResult;
  if (m_field04->compare(*other.m_field04,&leftResult,&rightResult))
   return leftResult==rightResult;
 }
 return rva00752A20Fallback(*m_field04,*other.m_field04,tolerance);
}
