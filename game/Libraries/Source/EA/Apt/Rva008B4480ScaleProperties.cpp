// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008B4480: copies eight named numeric properties from the stack's
// lookup into four two-component float pairs, when both values are defined.

class AptValue
{
public:
	int toInteger() const;
};

class BfmeN1034;
class BfmeTab1034
{
public:
	BfmeN1034 *bfmeFind1034F(int key);
};

extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern AptValue *g_bfmeFallbackDB;
extern int g_bfmeRouteKeys1282[1];
extern const float g_01076C24;
extern const float g_0107C64C;

AptValue *__cdecl rva008B4480ScaleProperties(void **owner, int count)
{
	if (count <= 0)
		return g_bfmeFallbackDB;
	{
		AptValue *value = g_bfmeArr1233[g_bfmeCount1233 - 1];
		void *target = owner[8];
		unsigned int targetFlags = reinterpret_cast<unsigned int *>(target)[1];
		if (((unsigned char)~(targetFlags >> 15) & 1) == 0) {
			unsigned int flags = reinterpret_cast<unsigned int *>(value)[1];
			if ((flags & 0x8000) && (flags & 0x3f) == 0x1b
				&& ((unsigned char)~(flags >> 15) & 1) == 0) {
				BfmeTab1034 *lookup = reinterpret_cast<BfmeTab1034 *>(
					reinterpret_cast<char *>(value) + 8);
				AptValue *found;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[122]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x2c) = found->toInteger() * g_01076C24;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[124]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x3c) = found->toInteger() * g_0107C64C;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[58]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x30) = found->toInteger() * g_01076C24;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[59]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x40) = found->toInteger() * g_0107C64C;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[37]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x34) = found->toInteger() * g_01076C24;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[38]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x44) = found->toInteger() * g_0107C64C;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[29]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x28) = found->toInteger() * g_01076C24;
				found = reinterpret_cast<AptValue *>(lookup->bfmeFind1034F((int)&g_bfmeRouteKeys1282[30]));
				if (found) *reinterpret_cast<float *>(reinterpret_cast<char *>(target) + 0x38) = found->toInteger() * g_0107C64C;
			}
		}
	}
	return g_bfmeFallbackDB;
}
