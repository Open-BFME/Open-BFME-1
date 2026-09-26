// ?aptMathRandom@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
class AptValue;
extern const float Rva008A51B0RandomScale;
unsigned int __cdecl bfmeNext1221();
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathRandom(void* self, int argc)
{
	int r = (int)bfmeNext1221();
	float f = (float)r;
	if (r < 0)
		f = f * Rva008A51B0RandomScale;
	return Rva008A4EA0MakeFloat(f);
}
