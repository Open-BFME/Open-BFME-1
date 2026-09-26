// ?divideBy@Rva008D63A0Vec4@@QAEXM@Z
// partial score=0.85 date=2026-09-06
// 41/43 B: identical FPU sequence but retail copies this into eax first (mov eax,ecx) and addresses through eax; array/pointer/local-alias forms all keep ecx.
extern float g_bfmeDefaultBU;
struct Rva008D63A0Vec4 {
	float x; float y; float z; float w;
	void divideBy(float d);
};
void Rva008D63A0Vec4::divideBy(float d)
{
	float s = g_bfmeDefaultBU / d;
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}
