// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameLogic /Igame/Libraries/Source/WWVegas/WWMath
#include <math.h>
#include "command_source_type.h"
#include "coord.h"
#define BFME_HAVE_COORD3D
#include "object.h"

typedef float Real;
typedef bool Bool;

#include "snapshot.h"

// BFME GeometryInfo is 0x5C, proven by the matched copy constructor at
// 000FFD10 and canonical Object::m_geometryInfo. Legacy geometry.h describes
// the smaller ZH type and does not cover this retail layout. Keep unknown
// geometry storage opaque; the existing Snapshot header supplies its base.
class GeometryInfo : public Snapshot
{
public:
	GeometryInfo( const GeometryInfo &other );
	virtual ~GeometryInfo();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer &xfer);

private:
 unsigned char m_unmodelled04[0x58];
};

typedef char GeometryInfoLayoutCheck[ sizeof( GeometryInfo ) == 0x5C ? 1 : -1 ];

class AIUpdateInterface
{
 friend class Rva002C4FD0;
protected:
	virtual void privateMoveToPosition( const Coord3D *position, CommandSourceType commandSource );
};

extern Real BfmeZeroRange;
extern Real g_bfmeDefaultBU;

class Rva002C4FD0
{
public:
	
 void setFirst(int value) { m_bfme344ESE=value; }
 void setSecond(int value) { m_bfme348ESE=value; }
	void method(Object *thing, CommandSourceType ctx);
	

	unsigned char m_bfmeHeadESE[8];
	Object *m_bfme08ESE;
	unsigned char m_bfmeMidESE[0x32C];
	unsigned char m_bfme338ESE;
	unsigned char m_bfme33cESE[0x0B];
	int m_bfme344ESE;
	int m_bfme348ESE;
	int m_bfme34cESE;
};

// RET8 at 002C5147 followed by INT3 gives the complete 378-byte extent.
// The matched bfmeStepESE caller reaches this body through ILT 0003C8CB.
// Its synthetic name is not identity proof; the owner/method retain the RVA.
// Evidence: identity_evidence/002c4fd0-inline-setters.md
void Rva002C4FD0::method(Object *thing, CommandSourceType ctx)
{
	Object *object = m_bfme08ESE;
	m_bfme338ESE = 1;
	setFirst(thing->m_id);
	setSecond(thing->m_id);

	Coord3D delta;
	delta.x = object->m_cachedPos.x;
	delta.y = object->m_cachedPos.y;
	delta.z = object->m_cachedPos.z;
	delta.x -= thing->m_cachedPos.x;
	delta.y -= thing->m_cachedPos.y;
	delta.z -= thing->m_cachedPos.z;
	double distance = sqrt( delta.z * delta.z + delta.y * delta.y + delta.x * delta.x );
	if (distance != BfmeZeroRange)
	{
		Real scale = g_bfmeDefaultBU / distance;
		delta.x *= scale;
		delta.y *= scale;
	}

	GeometryInfo thingGeometry = *(const GeometryInfo *)thing->m_geometryInfo;
	GeometryInfo objectGeometry = *(const GeometryInfo *)object->m_geometryInfo;
	Real range = *(Real *)((char *)&thingGeometry + 0x10)
		+ *(Real *)((char *)&objectGeometry + 0x10);
	delta.x *= range;
	range *= delta.y;
	delta.y = range;
	Coord3D position;
	position.y = thing->m_cachedPos.y;
	position.z = thing->m_cachedPos.z;
	Real thingX = thing->m_cachedPos.x;
	position.x = thingX + delta.x;
	position.y += delta.y;

	((AIUpdateInterface *)this)->AIUpdateInterface::privateMoveToPosition(
		(const Coord3D *)&position, ctx );
}
