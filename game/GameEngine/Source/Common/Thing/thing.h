// thing.h -- BFME's Thing: the primary base of Object (and of Drawable in ZH).
//
// Layout from the retail image, not from any one TU (docs/object_layout.md):
// ??0Thing at 0x001328C0 installs vftable 0x00C90DE0 (8 slots) and fills
// +0x04..+0x5C, so sizeof(Thing) == 0x60. Every member name below is witnessed
// by tools/name_oracle.py --class Thing at confidence >= 0.9.
//
// Nothing has to be included first. A member whose type lives elsewhere gets
// that type when the TU already has it, and otherwise the same bytes under the
// same name, so a TU that never touches it pulls nothing in:
//   m_transform                     Matrix3D once WWMath's matrix3d.h is in,
//                                   else Real[3][4]
//   m_cachedPos, m_cachedDirVector  Coord3D when the TU defines BFME_HAVE_COORD3D
//                                   (it has a complete 12-byte Coord3D), else Real[3]
// Using a member as the real type without it is a compile error, never a byte
// change, and the checks at the bottom refuse a wrongly sized type.
//
// Non-virtual members belong to the TU until their signatures are settled:
// define THING_TU_MEMBERS to the declarations a TU needs (member functions
// only; a data member there is a layout change this file cannot check).

#ifndef BFME_THING_H
#define BFME_THING_H

#include <stddef.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class ThingTemplate;
class Matrix3D;
struct Coord3D;

class Thing
{
protected:
	// Primary vftable 0x00C90DE0; Object's 0x00C9EE58 keeps these eight slots.
	virtual Real calculateHeightAboveTerrain() const;	// slot 0: ?calculateHeightAboveTerrain@Thing@@MBEMXZ 0x00132470
public:
	virtual void thingSlot01_00132110();				// slot 1
	virtual void thingSlot02_001320F0();				// slot 2
	virtual void thingSlot03_00132120();				// slot 3
	virtual void thingSlot04_00132100();				// slot 4
protected:
	// slot 5: _purecall in Thing; Object's ?reactToTransformChange@Object@@MAEXPBVMatrix3D@@PBUCoord3D@@M@Z
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle) = 0;
public:
	virtual void thingSlot06_00132130();				// slot 6
protected:
	virtual ~Thing();									// slot 7: scalar-deleting destructor

public:
	ThingTemplate *m_template;							// +0x04
#ifdef MATRIX3D_H
	Matrix3D m_transform;								// +0x08
#else
	Real m_transform[3][4];								// +0x08 include matrix3d.h first for the real type
#endif
#ifdef BFME_HAVE_COORD3D
	Coord3D m_cachedPos;								// +0x38
	Real m_cachedAngle;									// +0x44
	Coord3D m_cachedDirVector;							// +0x48
#else
	Real m_cachedPos[3];								// +0x38 define BFME_HAVE_COORD3D for the real type
	Real m_cachedAngle;									// +0x44
	Real m_cachedDirVector[3];							// +0x48
#endif
	Real m_cachedAltitudeAboveTerrain;					// +0x54
	Real m_cachedAltitudeAboveTerrainOrWater;			// +0x58
	Int m_cacheFlags;									// +0x5C

#ifdef THING_TU_MEMBERS
public:
	THING_TU_MEMBERS
#endif
};

#define BFME_LAYOUT_CHECK(cls, member, offset) \
	typedef char cls##_##member##_is_not_at_##offset[offsetof(cls, member) == (offset) ? 1 : -1]

BFME_LAYOUT_CHECK(Thing, m_template, 0x04);
BFME_LAYOUT_CHECK(Thing, m_transform, 0x08);
BFME_LAYOUT_CHECK(Thing, m_cachedPos, 0x38);
BFME_LAYOUT_CHECK(Thing, m_cachedAngle, 0x44);
BFME_LAYOUT_CHECK(Thing, m_cachedDirVector, 0x48);
BFME_LAYOUT_CHECK(Thing, m_cachedAltitudeAboveTerrain, 0x54);
BFME_LAYOUT_CHECK(Thing, m_cachedAltitudeAboveTerrainOrWater, 0x58);
BFME_LAYOUT_CHECK(Thing, m_cacheFlags, 0x5C);
typedef char Thing_size_is_not_0x60[sizeof(Thing) == 0x60 ? 1 : -1];

#endif // BFME_THING_H
