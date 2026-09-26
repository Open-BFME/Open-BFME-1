// ?copyVec3Strided@@YAXPAURva0090FB60Vec3@@HPBU1@H@Z
struct Rva0090FB60Vec3 { float x; float y; float z; };
void copyVec3Strided(Rva0090FB60Vec3* dst, int stride, const Rva0090FB60Vec3* src, int count)
{
	for (; count; --count) {
		dst->x = src->x; dst->y = src->y; dst->z = src->z;
		++src;
		dst = (Rva0090FB60Vec3*)((char*)dst + stride);
	}
}
