// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x00604EE0. Three stack arguments with the second one a Coord3D
// the body compares against the current position, which is the shape of
// reactToTransformChange. The owning module is not recovered, so the class
// carries an address-derived name.

class Coord3D
{
public:
	bool IsExactlyEqualTo(const Coord3D &other) const;
};

class BfmeResetSubsystem;

extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

// The position accessor is matched as BFMERopeDrawableGetPositionShim::get and
// the notify helper as Gen_00409040Registry::m. Both declare a Coord3D that
// this file cannot spell at the same time, so they go through their thunks.
extern void j_0004b12d();
extern void j_000281c8();

typedef const Coord3D *(__fastcall *Rva00604EE0GetPosition)(void *rope);
class Rva00604EE0Registry
{
public:
	void notify(void *module);
};

typedef void (Rva00604EE0Registry::*Rva00604EE0NotifyCall)(void *module);

union Rva00604EE0Cast
{
	void *asVoid;
	Rva00604EE0NotifyCall asCall;
};

class Rva00604EE0Module
{
public:
	void reactToTransformChange(void *oldMatrix, const Coord3D *oldPosition, float oldAngle);

	unsigned char m_padding000[8];
	void *m_rope;
};

void Rva00604EE0Module::reactToTransformChange(void *oldMatrix, const Coord3D *oldPosition,
	float oldAngle)
{
	void *rope = m_rope;

	if (oldPosition != 0 && rope != 0
		&& ((Rva00604EE0GetPosition)j_0004b12d)(rope) != 0
		&& ((Rva00604EE0GetPosition)j_0004b12d)(rope)->IsExactlyEqualTo(*oldPosition))
		return;

	BfmeResetSubsystem *subsystem = g_animationSoundClientBehaviorGlobal;
	if (subsystem != 0)
	{
		Rva00604EE0Cast cast;
		cast.asVoid = (void *)j_000281c8;
		(((Rva00604EE0Registry *)subsystem)->*cast.asCall)(this);
	}
}
