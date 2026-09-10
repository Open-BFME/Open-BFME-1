// ?bfmeArenaReady@@YAXXZ
// partial score=0.98 date=2026-09-10
// ?bfmeArenaReady@@YAXXZ

extern char *g_bfmeArenaCursor;

struct BfmeArenaVec4
{
	BfmeArenaVec4(float valueX, float valueY, float valueZ, float valueW)
		: x(valueX), y(valueY), z(valueZ), w(valueW) {}

	float x;
	float y;
	float z;
	float w;
};

struct BfmeArenaTransform
{
	float m00;
	float m04;
	float m08;
	float m0c;
	float m10;
	float m14;
	float m18;
	float m1c;
	float m20;
	float m24;
	float m28;
	float m2c;
	float m30;
	float m34;
	float m38;
	float m3c;
	BfmeArenaVec4 m40;
	BfmeArenaVec4 m50;
};

__declspec(noinline) void __cdecl bfmeArenaReady(void)
{
	BfmeArenaTransform *transform = reinterpret_cast<BfmeArenaTransform *>(g_bfmeArenaCursor);
	BfmeArenaVec4 one(1.0f, 1.0f, 1.0f, 1.0f);
	BfmeArenaVec4 zero(0.0f, 0.0f, 0.0f, 0.0f);
	transform->m04 = 0;
	transform->m08 = 0;
	transform->m0c = 0;
	transform->m10 = 0;
	transform->m18 = 0;
	transform->m1c = 0;
	transform->m20 = 0;
	transform->m24 = 0;
	transform->m2c = 0;
	transform->m30 = 0;
	transform->m34 = 0;
	transform->m38 = 0;
	transform->m00 = 1.0f;
	transform->m14 = 1.0f;
	transform->m28 = 1.0f;
	transform->m3c = 1.0f;
	transform->m40 = one;
	transform->m50 = zero;
}
