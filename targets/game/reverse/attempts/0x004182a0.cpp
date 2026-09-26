// ?method@Rva004182A0@@QAEPAVObject@@XZ
// partial score=0.85 date=2026-09-16
// Scratch-only reconstruction of retail RVA 0x004182A0.
// The original method identity is not known; the address-derived owner name
// is intentional. This file is kept under build/ for the scoped probe.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "Common/BitFlags.h"

class Object;
class Player;

typedef BitFlags<192> Rva004182A0KindOfMask;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

// The root table is the already-witnessed native table at 0x01083B80. Its
// two-word base head is the complete stack object used by this body.
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// Retail vtable 0x0109687C is retained as an address-derived filter type;
// its semantic class name is not asserted here.
class Rva004182A0FilterAt0010 : public PartitionFilter
{
public:
	Rva004182A0FilterAt0010() {}
	virtual ~Rva004182A0FilterAt0010() {}
	virtual Bool allow(Object *);
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}
	virtual ~PartitionFilterPlayer() {}
	virtual Bool allow(Object *);
	const Player *m_player;
	Bool m_match;
};

struct BfmeSrc1196
{
	unsigned char m_pad0[0x38];
	Coord3D m_position;
	unsigned char m_pad1[0x78];
	Real m_range;
};

// The matched constructor writes this exact 28-byte base-plus-payload shape:
// vptr/next, Coord3D, Real, Bool, and three bytes of tail padding.
class BfmeA1196 : public PartitionFilter
{
public:
	BfmeA1196(BfmeSrc1196 *owner, char match);
	virtual ~BfmeA1196() {}
	virtual Bool allow(Object *);
	Coord3D m_position;
	Real m_range;
	Bool m_match;
	unsigned char m_tail[3];
};

// This is the native one-mask 192-bit filter evidenced by vtable
// 0x010F11B4. It is deliberately separate from the sibling two-mask
// accept/reject declarations.
class Rva004182A0KindOfFilter : public PartitionFilter
{
public:
	Rva004182A0KindOfFilter(const Rva004182A0KindOfMask &mask)
		: m_mask(mask) {}
	virtual ~Rva004182A0KindOfFilter() {}
	virtual Bool allow(Object *);
	Rva004182A0KindOfMask m_mask;
};

class Rva004182A0PlayerGlobal
{
public:
	unsigned char m_pad0[0x0c];
	Player *m_player;
};
extern "C" Rva004182A0PlayerGlobal *g_rva004182A0PlayerGlobal;

class Rva004182A0GlobalData
{
public:
	unsigned char m_pad0[0x60];
	Real m_radius;
};
extern "C" Rva004182A0GlobalData *g_rva004182A0GlobalData;

enum DistanceCalculationType
{
	RVA004182A0_FROM_CENTER_2D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real radius,
		DistanceCalculationType distanceType, PartitionFilter *filters);
};
extern PartitionManager *ThePartitionManager;

class Rva004182A0 : public BfmeSrc1196
{
public:
	Object *method();
};

Object *Rva004182A0::method()
{
	Rva0025ED50RootFilter rootFilter;
	Rva004182A0FilterAt0010 onMapFilter;
	PartitionFilterPlayer playerFilter(
		g_rva004182A0PlayerGlobal->m_player, true);
	Rva004182A0KindOfFilter kindOfFilter(
		Rva004182A0KindOfMask(
			Rva004182A0KindOfMask::kInit, 121, 157));
	BfmeA1196 shroudFilter(this, true);

	return ThePartitionManager->getClosestObject(
		&m_position, g_rva004182A0GlobalData->m_radius,
		RVA004182A0_FROM_CENTER_2D,
		kindOfFilter.link(&rootFilter)
			->link(&onMapFilter)
			->link(&playerFilter)
			->link(&shroudFilter));
}

