// ?buildMatrix2D@@YAXPAURva008BCF90Matrix4@@PBURva008BCF90Affine2D@@@Z
struct Rva008BCF90Affine2D { float a; float b; float c; float d; float tx; float ty; };
struct Rva008BCF90Matrix4 { float m[4][4]; };
void buildMatrix2D(Rva008BCF90Matrix4* out, const Rva008BCF90Affine2D* in)
{
	out->m[0][0] = in->a;
	out->m[0][1] = in->b;
	out->m[0][2] = 0.0f;
	out->m[0][3] = 0.0f;
	out->m[1][0] = in->c;
	out->m[1][1] = in->d;
	out->m[1][2] = 0.0f;
	out->m[1][3] = 0.0f;
	out->m[2][0] = 0.0f;
	out->m[2][1] = 0.0f;
	out->m[2][2] = 1.0f;
	out->m[2][3] = 0.0f;
	out->m[3][0] = in->tx;
	out->m[3][1] = in->ty;
	out->m[3][2] = 0.0f;
	out->m[3][3] = 1.0f;
}
