// ?rva001E49E0Aim@@YAPAUCoord3D@@PBVLinearTargets@@HPBVObject@@PAU1@@Z
// partial score=0.10 date=2026-09-26
// Retail 0x001E49E0, 144 bytes, called from Weapon::privateFireWeapon.
// Include after the Object, LinearTargets, Matrix3D and TerrainLogic definitions
// in 0x001e9fd0.cpp. The probe is 140/144 bytes with 124 non-relocation
// differences and two relocation-layout mismatches. Retail uses a compiler-
// private ABI: ECX=targets, EAX=index, EDI=source, ESI=out, without saving the
// latter two. Ordinary C++ passes source in EDX and out in EDI and saves ESI;
// do not pin this proposed semantic name without independent identity and
// byte-match proof.
struct LinearAimStep
{
	Coord2D offset;
	int marker;
};

static Coord3D *rva001E49E0Aim(const LinearTargets *targets, int index,
	const Object *source, Coord3D *out)
{
	const LinearAimStep *step =
		reinterpret_cast<const LinearAimStep *>(targets->m_begin) + index;
	Coord2D offset = step->offset;
	const Matrix3D *transform = reinterpret_cast<const Matrix3D *>(
		reinterpret_cast<const char *>(source) + 8);
	float rotation = transform->Get_Z_Rotation();
	float sinValue = sinf(rotation);
	float cosValue = cosf(rotation);
	Coord3D pos;
	pos.x = source->m_position.x + (offset.x * cosValue - offset.y * sinValue);
	pos.y = source->m_position.y + (offset.x * sinValue + offset.y * cosValue);
	pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
	*out = pos;
	return out;
}
