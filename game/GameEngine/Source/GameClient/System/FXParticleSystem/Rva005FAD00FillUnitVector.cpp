// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Retail RVA 0x005FAD00: complete 246-byte cdecl output-pointer helper.
// Point and related emission callbacks reach it through ILT RVA 0x000107EE.
// Caller RVA0x005FAA40 immediately reads the returned address in EAX. This
// address-qualified ABI view exposes that output-address return explicitly.
// The original pointer/inputs/reference/hidden-aggregate source spelling is unknown.
// The historical helper name is unknown. Three random-real calls use source
// lines31/32/33 and ILT RVA0x00047681 -> body RVA0x00096E80 (69 bytes).
// A zero vector is retried; other vectors are normalized when length is nonzero.
// The only return is at +0xF5; padding starts at +0xF6. No EH or owned tables.
// Readonly float cells: RVA0x00C75350 is +0.0f; RVA0x00C75334 is 1.0f.

#include <math.h>

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );
extern const float Rva00C75350Zero;
extern const float Rva00C75334One;

struct Coord3D
{
	float x;
	float y;
	float z;
};

static char kRetailFile[] =
	"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittervolumemodule.cpp";

extern "C" Coord3D *Rva005FAD00FillUnitVector( Coord3D *out )
{
	Coord3D components;

	do
	{
		components.x = GetGameClientRandomValueReal(
			-1.0f, 1.0f, kRetailFile, 31 );
		components.y = GetGameClientRandomValueReal(
			-1.0f, 1.0f, kRetailFile, 32 );
		components.z = GetGameClientRandomValueReal(
			-1.0f, 1.0f, kRetailFile, 33 );
	}
	while ( components.x == Rva00C75350Zero &&
		components.y == Rva00C75350Zero &&
		components.z == Rva00C75350Zero );

	float length = (float)sqrt( components.x * components.x +
		components.y * components.y + components.z * components.z );
	if ( length != Rva00C75350Zero )
	{
		float inverseLength = Rva00C75334One / length;
		components.x *= inverseLength;
		components.y *= inverseLength;
		components.z *= inverseLength;
	}

	out->x = components.x;
	out->y = components.y;
	out->z = components.z;
	return out;
}
