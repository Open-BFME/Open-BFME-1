// ?d_002c4fd0@@YAXXZ
// partial score=0.963 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
#include <math.h>
#include <vector>
#include "../GameLogic/command_source_type.h"
#include "../../../Libraries/Source/WWVegas/WWMath/coord3d.h"

typedef float Real;
typedef bool Bool;

class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer( Xfer &xfer );
};

struct Rva002C4FD0GeometryShape
{
	unsigned char m_bytes[ 0x24 ];
};

struct Rva002C4FD0GeometryRecord
{
	unsigned char m_bytes[ 0x10 ];
};

// BFME's 0x5C GeometryInfo layout matches GeometryInfoCopyConstructor.cpp.
class GeometryInfo : public Snapshot
{
public:
	GeometryInfo( const GeometryInfo &other );
	virtual ~GeometryInfo();

private:
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<Rva002C4FD0GeometryShape> m_shapes;
	std::vector<Rva002C4FD0GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

typedef char GeometryInfoLayoutCheck[ sizeof( GeometryInfo ) == 0x5C ? 1 : -1 ];

class AIUpdateInterface
{
public:
	void privateMoveToPosition( const Coord3D *position, CommandSourceType commandSource );
};

extern Real BfmeZeroRange;
extern Real g_bfmeDefaultBU;

class BfmeStateESE
{
public:
	virtual void bfmeSlot00ESE();
	virtual void bfmeSlot01ESE();
	virtual void bfmeSlot02ESE();
	virtual void bfmeSlot03ESE();
	virtual void bfmeSlot04ESE();
	virtual float bfmeSlot05ESE();
};

extern float g_bfmeDefaultESE;

class BfmeThingESE
{
public:
	unsigned char m_bfmeHeadESE[0x38];
	Coord3DBase m_bfme38ESE;
	unsigned char m_bfme44ESE[0x30];
	int m_bfme74ESE;
	unsigned char m_bfme78ESE[0x34];
	GeometryInfo m_bfmeACESE;
	unsigned char m_bfme108ESE[0xF8];
	BfmeStateESE *m_bfmeStateESE;
};

class BfmeActionsESE
{
public:
	char bfmeCheckESE(void *owner, BfmeThingESE *thing, void *ctx);
};

extern BfmeActionsESE *g_bfmeActionsESE;

class BfmeHostESE
{
public:
	void bfmeStepESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoAESE(BfmeThingESE *thing, void *ctx);
	void bfmeDoBESE(BfmeThingESE *thing, void *ctx);

	unsigned char m_bfmeHeadESE[8];
	void *m_bfme08ESE;
	unsigned char m_bfmeMidESE[0x32C];
	unsigned char m_bfme338ESE;
	unsigned char m_bfme33cESE[0x0B];
	int m_bfme344ESE;
	int m_bfme348ESE;
	int m_bfme34cESE;
};

void BfmeHostESE::bfmeStepESE(BfmeThingESE *thing, void *ctx)
{
	BfmeStateESE *state = thing->m_bfmeStateESE;

	if (state != 0 && state->bfmeSlot05ESE() < g_bfmeDefaultESE)
	{
		void *owner = m_bfme08ESE;

		if (g_bfmeActionsESE->bfmeCheckESE(owner, thing, ctx))
		{
			m_bfme34cESE = thing->m_bfme74ESE;

			bfmeDoAESE(thing, ctx);
		}
	}

	if (m_bfme34cESE == 0)
		bfmeDoBESE(thing, ctx);
}

// The matched bfmeStepESE caller reaches this body through ILT 0x0003C8CB.
void BfmeHostESE::bfmeDoAESE(BfmeThingESE *thing, void *ctx)
{
	BfmeThingESE *object = (BfmeThingESE *)m_bfme08ESE;
	m_bfme338ESE = 1;
	m_bfme344ESE = thing->m_bfme74ESE;
	m_bfme348ESE = thing->m_bfme74ESE;

	Coord3DBase delta;
	delta.x = object->m_bfme38ESE.x;
	delta.y = object->m_bfme38ESE.y;
	delta.z = object->m_bfme38ESE.z;
	delta.x -= thing->m_bfme38ESE.x;
	delta.y -= thing->m_bfme38ESE.y;
	delta.z -= thing->m_bfme38ESE.z;
	double distance = sqrt( delta.z * delta.z + delta.y * delta.y + delta.x * delta.x );
	if (distance != BfmeZeroRange)
	{
		Real scale = g_bfmeDefaultBU / distance;
		delta.x *= scale;
		delta.y *= scale;
	}

	GeometryInfo thingGeometry = thing->m_bfmeACESE;
	GeometryInfo objectGeometry = object->m_bfmeACESE;
	Real range = *(Real *)((char *)&thingGeometry + 0x10)
		+ *(Real *)((char *)&objectGeometry + 0x10);
	delta.x *= range;
	range *= delta.y;
	delta.y = range;
	Coord3DBase position;
	position.y = thing->m_bfme38ESE.y;
	position.z = thing->m_bfme38ESE.z;
	Real thingX = thing->m_bfme38ESE.x;
	position.x = thingX + delta.x;
	position.y += delta.y;

	((AIUpdateInterface *)this)->privateMoveToPosition(
		(const Coord3D *)&position, (CommandSourceType)(int)ctx );
}
