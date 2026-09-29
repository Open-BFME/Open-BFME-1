// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// Retail 0x0092CC40 (180 bytes): a frustum-versus-AABox rejection test built
// from the WWMath plane pieces.  For each of the six frustum planes it takes
// the box corner farthest against the plane normal (get_far_extent, then
// Vector3::Subtract from the centre in place -- the aliasing out-pointer is
// what keeps x and y on the stack) and reports the box outside as soon as
// that corner is on the plane's positive side.  Nothing calls it directly
// and no table points at it; the name is the address's.

#include "colmath.h"
#include "colmathinlines.h"
#include "frustum.h"
#include "aabox.h"

bool Rva0092CC40BoxOutsideFrustum(const FrustumClass & frustum,const AABoxClass & box)
{
	for (int i = 0; i < 6; i++) {
		Vector3 negfarpt;
		get_far_extent(frustum.Planes[i].N,box.Extent,&negfarpt);
		Vector3::Subtract(box.Center,negfarpt,&negfarpt);
		if (CollisionMath::Overlap_Test(frustum.Planes[i],negfarpt) == CollisionMath::POS) {
			return true;
		}
	}
	return false;
}
