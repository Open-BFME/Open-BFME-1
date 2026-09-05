// ?bfmeContains1283@@YAHPBVBfmeTriangle1290@@MM@Z
// partial score=1.0 date=2026-09-05
// ?bfmeMeshHitTest1290@@YG_NPAUBfmeMesh1290@@PBUBfmeTransform2_1290@@HH@Z
// Grok draft review: complete same-TU caller gives the static triangle helper
// retail ECX receiver plus caller-clean floating args. Helper303B strict;
// caller still differs. Both bodies must remain together; no progress claim.
struct BfmeVector2_1290
{
	float x;
	float y;
};

struct BfmeTransform2_1290
{
	float m00;
	float m10;
	float m01;
	float m11;
	float tx;
	float ty;
};

class BfmeTriangle1290
{
public:

	BfmeVector2_1290 points[3];
};

struct BfmeMesh1290
{
	char m_padding00[0x14];
	int m_triangleCount;
	char m_padding18[4];
	BfmeVector2_1290 *m_vertices;
	short *m_indices;
};

static int bfmeContains1283(const BfmeTriangle1290 *triangle, float x, float y)
{
	int inside = 0;
	if (((triangle->points[0].y <= y && y < triangle->points[2].y) || (triangle->points[2].y <= y && y < triangle->points[0].y)) &&
		triangle->points[0].x + (triangle->points[2].x - triangle->points[0].x) * (y - triangle->points[0].y) / (triangle->points[2].y - triangle->points[0].y) > x)
		inside = 1;

	if (((triangle->points[1].y <= y && y < triangle->points[0].y) || (triangle->points[0].y <= y && y < triangle->points[1].y)) &&
		triangle->points[1].x + (triangle->points[0].x - triangle->points[1].x) * (y - triangle->points[1].y) / (triangle->points[0].y - triangle->points[1].y) > x)
		inside = !inside;

	if (((triangle->points[2].y <= y && y < triangle->points[1].y) || (triangle->points[1].y <= y && y < triangle->points[2].y)) &&
		triangle->points[2].x + (triangle->points[1].x - triangle->points[2].x) * (y - triangle->points[2].y) / (triangle->points[1].y - triangle->points[2].y) > x)
		inside = !inside;

	return inside;
}

bool __stdcall bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform,
	int pointX, int pointY)
{
	float x = pointX;
	int triangleCount = mesh->m_triangleCount;
	float y = pointY;
	BfmeVector2_1290 *vertices = mesh->m_vertices;
	short *indices = mesh->m_indices;

	for (int i = 0; i < triangleCount; ++i) {
		BfmeTriangle1290 triangle;
		const BfmeVector2_1290 &source0 = vertices[indices[0]];
		triangle.points[0].x = source0.x * transform->m00 +
			source0.y * transform->m01 + transform->tx;
		triangle.points[0].y = source0.x * transform->m10 +
			source0.y * transform->m11 + transform->ty;
		const BfmeVector2_1290 &source1 = vertices[indices[1]];
		triangle.points[1].x = source1.x * transform->m00 +
			source1.y * transform->m01 + transform->tx;
		triangle.points[1].y = source1.x * transform->m10 +
			source1.y * transform->m11 + transform->ty;
		const BfmeVector2_1290 &source2 = vertices[indices[2]];
		triangle.points[2].x = source2.x * transform->m00 +
			source2.y * transform->m01 + transform->tx;
		triangle.points[2].y = source2.x * transform->m10 +
			source2.y * transform->m11 + transform->ty;
		if (bfmeContains1283(&triangle, x, y))
			return true;
		indices += 3;
	}
	return false;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
