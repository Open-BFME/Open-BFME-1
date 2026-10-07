// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x0069A2E0: the audio owner's per-frame listener refresh, reached from
// the address-derived Rva006B6910 setter.  It asks two of its own virtuals for
// a source position and a look-at point, and when either moved it places the
// listener between them by the current distance profile, points it along the
// horizontal delta, hands both to Miles and re-attenuates the active channel.
// The owner's class is not evidenced, so the address-derived names stay.
//
// Shape notes: fraction is live from before the delta (its early 1.0f keeps
// retail's delta-first x87 multiply order), normalize reads its fields into
// locals (retail loads x, y, z in that order), and the relative offset reads
// the listener through a pointer (retail's EDI) in its own block, which also
// lets it share the offset's frame slot.

typedef float Real;
typedef bool Bool;
typedef int Int;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_orientation(
	void *sample, float xFace, float yFace, float zFace, float xUp, float yUp, float zUp);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(
	void *sample, float x, float y, float z);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}
};

// Retail's Coord3D::normalize (0x000FB930) has a zero check; this inlined
// shape does not, so it stays a file-static helper, not a Coord3D COMDAT.
static void normalizeCoord3D(Coord3D &c)
{
	Real lx = c.x;
	Real ly = c.y;
	Real lz = c.z;
	Real inv = 1.0f / (Real)sqrt(lx * lx + ly * ly + lz * lz);
	c.x *= inv;
	c.y *= inv;
	c.z *= inv;
}

// The 0x30-byte distance profile; +0x1C.. are the fields the landed
// attenuate body names, the first seven are read only here.
struct Rva006995F0Range
{
	Real m_float00;
	Real m_float04;
	Real m_float08;
	Real m_float0c;
	Real m_float10;
	Real m_float14;
	Real m_float18;
	Real m_near;
	Real m_near2;
	Real m_far;
	Real m_far2;
	Real m_scale;
};

struct Rva006995F0Vec3
{
	Real x;
	Real y;
	Real z;
};

class Rva006995F0Owner
{
public:
	void attenuate(Rva006995F0Range *range, Rva006995F0Vec3 *pos);

private:
	char m_pad[0x1c4];
};

struct Rva0069A2E0Settings
{
	char m_pad00[0xa8];
	Rva006995F0Range m_profiles[1];
};

template <int N>
class Rva0069A2E0Slots : public Rva0069A2E0Slots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva0069A2E0Slots<0>
{
};

class Rva0069A2E0Owner : public Rva0069A2E0Slots<95>
{
public:
	virtual void getSourcePosition17C(Coord3D *out) = 0;
	virtual Bool getLookAt180(Coord3D *out) = 0;

	void refresh0069A2E0();

private:
	char m_pad04[0x0c - 0x04];
	Rva0069A2E0Settings *m_settings;
	char m_pad10[0x14 - 0x10];
	Coord3D m_listenerPos;
	Coord3D m_listenerFacing;
	Coord3D m_lastSource;
	Coord3D m_lastLookAt;
	char m_pad44[0xb8 - 0x44];
	Rva006995F0Owner m_channels[3];
	Int m_profileIndex;
	char m_pad608[0x964 - 0x608];
	void *m_listener;
};

void Rva0069A2E0Owner::refresh0069A2E0()
{
	Rva006995F0Range *profile = &m_settings->m_profiles[m_profileIndex];
	Coord3D source;
	Coord3D lookAt;
	source.zero();
	lookAt.zero();

	getSourcePosition17C(&source);
	Bool hasLookAt = getLookAt180(&lookAt);

	if (m_lastSource.x == source.x && m_lastSource.y == source.y && m_lastSource.z == source.z &&
		m_lastLookAt.x == lookAt.x && m_lastLookAt.y == lookAt.y && m_lastLookAt.z == lookAt.z)
		return;

	Real fraction = 1.0f;
	Coord3D delta;
	delta.x = source.x - lookAt.x;
	m_lastLookAt = lookAt;
	delta.y = source.y - lookAt.y;
	delta.z = source.z - lookAt.z;
	m_lastSource = source;

	Real distSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
	if (distSq * profile->m_float04 >= profile->m_float14)
		fraction = profile->m_float10 / (Real)sqrt(distSq);
	else if (distSq <= profile->m_float0c)
		fraction = 1.0f;
	else if (distSq * profile->m_float04 <= profile->m_float0c)
		fraction = profile->m_float08 / (Real)sqrt(distSq);
	else
		fraction = profile->m_float00;

	Coord3D placed;
	{
		Coord3D offset;
		offset.set(delta.x * fraction, delta.y * fraction, delta.z * fraction);

		placed.x = source.x - offset.x;
		placed.y = source.y - offset.y;
		placed.z = source.z - offset.z;
	}

	if (hasLookAt)
	{
		m_listenerPos.x = (lookAt.x - placed.x) * profile->m_float18 + placed.x;
		m_listenerPos.y = (lookAt.y - placed.y) * profile->m_float18 + placed.y;
		m_listenerPos.z = placed.z;
	}
	else
	{
		m_listenerPos = placed;
	}

	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		m_listenerFacing.set(-delta.x, -delta.y, 0.0f);
		normalizeCoord3D(m_listenerFacing);
	}

	if (m_listener)
	{
		AIL_set_3D_orientation(m_listener, m_listenerFacing.x, m_listenerFacing.y,
			-m_listenerFacing.z, 0.0f, 0.0f, -1.0f);
		AIL_set_3D_position(m_listener, m_listenerPos.x, m_listenerPos.y, -m_listenerPos.z);
	}

	{
		Rva006995F0Vec3 relative;
		const Coord3D *listenerPos = &m_listenerPos;
		relative.x = source.x - listenerPos->x;
		relative.y = source.y - listenerPos->y;
		relative.z = source.z - listenerPos->z;
		m_channels[m_profileIndex].attenuate(profile, &relative);
	}
}
