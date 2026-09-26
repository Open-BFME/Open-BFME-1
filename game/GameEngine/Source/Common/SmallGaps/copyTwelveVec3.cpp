// ?copyTwelveVec3@@YAXPBURva009C6DA0Vec3@@PAU1@HH@Z
struct Rva009C6DA0Vec3 { float x; float y; float z; };
void copyTwelveVec3(const Rva009C6DA0Vec3* src, Rva009C6DA0Vec3* dst, int srcStride, int dstStride)
{
	for (int i = 12; i; --i) {
		dst->x = src->x; dst->y = src->y; dst->z = src->z;
		src = (const Rva009C6DA0Vec3*)((const char*)src + srcStride);
		dst = (Rva009C6DA0Vec3*)((char*)dst + dstStride);
	}
}
