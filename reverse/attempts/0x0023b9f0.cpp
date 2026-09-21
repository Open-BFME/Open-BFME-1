// ?rva0023B9F0@BfmeHordeContainRoster@@QAEXXZ
// partial score=0.68 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BfmeHordeContainRoster slot-recenter, retail 0x0023B9F0.
//
// PARTIAL (banked stash). Identity: this+0x04 = roster owner, this+0x12c/0x130
// = the 16-byte-slot vector begin/end, exactly the BfmeHordeContainRoster layout
// from HordeContainMemberNameMatches.cpp; callee is ThingFactory::findTemplate
// (ILT 0x00028560) with TheThingFactory at 0x012EF1D8; x87 constants are
// BfmeZeroRange (0x01075350) and g_bfmeDefaultBU==1.0 (0x01075334).
//
// Semantics: scan the owner roster; if a template carries flag 0x0800 the running
// sum of the entries' inner-vector sizes becomes the leader slot index (else -1).
// Then walk the slot vector: if a slot's index hits that leader index snap the
// centre to that slot (count 1), else average all slot positions; finally subtract
// the centre from every slot (recentre the formation).
//
// EXACT so far (first divergence at +0x88): the whole roster loop, the sub esp,0xc
// frame, the special/leader branch, and the end (edx) / index (ecx) registers.
// REMAINING WALL: MSVC assigns the slot-begin pointer to ESI and the member-count
// (divisor) to EDI, where retail uses EDI for begin and ESI for the count. This one
// callee-saved pair (begin<->cnt, esi/edi) is a compiler register-schedule choice
// that no local-order / loop-form / counter-type variant here flips; it cascades
// into loop3's induction base (+3 bytes) and the divide's fxch-vs-fld FP order.
// The `*(Int*)&sumX = ...` cast in the leader is a stand-in that reproduces retail's
// memory-spill frame (sub esp,0xc); a trivially-copyable Coord2D local is folded
// away by MSVC (frame shrinks to 8), so the real source used some non-trivial copy.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern const float BfmeZeroRange;      // 0x01075350
extern float g_bfmeDefaultBU;          // 0x01075334

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_bfmeData;
};

class ThingTemplate
{
public:
	char m_bfmeHead[ 0xc8 ];
	UnsignedInt m_bfmeFlags;							///< retail this+0xc8
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );	///< ILT 0x00028560
};

extern ThingFactory *TheThingFactory;					///< 0x012EF1D8

struct BfmeHordeInner12
{
	int a, b, c;
};

class BfmeHordeInnerVec
{
public:
	UnsignedInt size( void ) const { return (UnsignedInt)( m_bfmeEnd - m_bfmeBegin ); }

	BfmeHordeInner12 *m_bfmeBegin;						///< +0
	BfmeHordeInner12 *m_bfmeEnd;						///< +4
	BfmeHordeInner12 *m_bfmeCap;						///< +8
};

class BfmeHordeRosterEntry
{
public:
	void *m_bfmeKey;									///< +0
	AsciiString m_bfmeName;								///< +4
	BfmeHordeInnerVec m_bfmeInner;						///< +8
};

class BfmeHordeRosterVec
{
public:
	UnsignedInt size( void ) const { return (UnsignedInt)( m_bfmeEnd - m_bfmeBegin ); }
	BfmeHordeRosterEntry *operator[]( UnsignedInt i ) const { return m_bfmeBegin[ i ]; }

	BfmeHordeRosterEntry **m_bfmeBegin;					///< +0
	BfmeHordeRosterEntry **m_bfmeEnd;					///< +4
	BfmeHordeRosterEntry **m_bfmeCap;					///< +8
};

class BfmeHordeRosterOwner
{
public:
	char m_bfmeHead[ 0x224 ];
	BfmeHordeRosterVec m_bfmeRoster;					///< retail this+0x224
};

struct BfmeHordeSlot
{
	void *m_bfmeKey;									///< +0
	float m_bfmeX;										///< +4
	float m_bfmeY;										///< +8
	float m_bfmeW;										///< +0xc
};

class BfmeHordeContainRoster
{
public:
	void rva0023B9F0( void );

private:
	char m_bfmeHead[ 4 ];
	BfmeHordeRosterOwner *m_bfmeOwner;					///< retail this+0x04
	char m_bfmeGap[ 0x12c - 0x08 ];
	BfmeHordeSlot *m_bfmeSlotBegin;						///< retail this+0x12c
	BfmeHordeSlot *m_bfmeSlotEnd;						///< retail this+0x130
};

// ?rva0023B9F0@BfmeHordeContainRoster@@QAEXXZ
void BfmeHordeContainRoster::rva0023B9F0( void )
{
	BfmeHordeRosterOwner *owner = m_bfmeOwner;

	BfmeHordeRosterVec &roster = owner->m_bfmeRoster;

	Int total = -1;
	Int count = 0;
	for ( UnsignedInt i = 0; i < roster.size(); ++i )
	{
		ThingTemplate *t = TheThingFactory->findTemplate( roster[ i ]->m_bfmeName );
		if ( t && ( t->m_bfmeFlags & 0x0800 ) )
		{
			total = count;
			break;
		}

		count += roster[ i ]->m_bfmeInner.size();
	}

	Int cnt = 0;
	Int idx = 0;
	BfmeHordeSlot *begin = m_bfmeSlotBegin;
	float sumX = BfmeZeroRange;
	BfmeHordeSlot *end = m_bfmeSlotEnd;
	float sumY = BfmeZeroRange;

	for ( BfmeHordeSlot *p = begin; p != end; ++p )
	{
		sumX += p->m_bfmeX;
		++cnt;
		sumY += p->m_bfmeY;
		if ( idx == total )
		{
			// retail re-reads the leader slot's position through memory temps
			// (frame sub esp,0xc); a trivially-copyable local is optimised away
			*(Int *)&sumX = *(Int *)&p->m_bfmeX;
			*(Int *)&sumY = *(Int *)&p->m_bfmeY;
			cnt = 1;
			break;
		}
		++idx;
	}

	if ( cnt != 0 )
	{
		float inv = g_bfmeDefaultBU / (float)cnt;
		sumX *= inv;
		sumY *= inv;
	}

	// loop3 re-reads m_bfmeSlotEnd (the store may alias this) so it reloads
	for ( BfmeHordeSlot *p = begin; p != m_bfmeSlotEnd; ++p )
	{
		p->m_bfmeX = p->m_bfmeX - sumX;
		p->m_bfmeY = p->m_bfmeY - sumY;
	}
}
