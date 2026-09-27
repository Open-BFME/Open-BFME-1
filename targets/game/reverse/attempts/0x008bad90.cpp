// ?d_008bad90@@YAXXZ
// partial score=0.97 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /FAsc
// The caller at 0x008BAEA0 and the symbol pin at 0x008BAD90 identify this as
// BfmePicker1284::bfmeMeshHitTest1290.
// The 272-byte draft still differs in eight byte values.
// Those values change the final floating-point operations and the y argument load.
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

class BfmePicker1284
{
public:
	bool bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform,
		int pointX, int pointY);
};

bool BfmePicker1284::bfmeMeshHitTest1290(BfmeMesh1290 *mesh,
	const BfmeTransform2_1290 *transform, int pointX, int pointY)
{
	float x = pointX;
	BfmeMesh1290 *meshView = mesh;
	int triangleCount = meshView->m_triangleCount;
	float y = pointY;
	int i = 0;
	mesh = reinterpret_cast<BfmeMesh1290 *>(triangleCount);
	if ((int)mesh > 0) {
		BfmeVector2_1290 *vertices = meshView->m_vertices;
		const BfmeTransform2_1290 *transformView = *reinterpret_cast<const BfmeTransform2_1290 * volatile *>(&transform);
		short *indices = meshView->m_indices;
		do {
			BfmeTriangle1290 triangle;
			const BfmeVector2_1290 &source0 = vertices[indices[0]];
			float x0 = *(volatile const float *)&transformView->m01;
			x0 = x0 * source0.y;
			x0 = x0 + *(volatile const float *)&transformView->m00 * source0.x;
			triangle.points[0].x = x0 + transformView->tx;
			float y0 = source0.x * transformView->m10;
			y0 = y0 + source0.y * transformView->m11;
			triangle.points[0].y = y0 + transformView->ty;
			const BfmeVector2_1290 &source1 = vertices[indices[1]];
			float x1 = source1.x * transformView->m00;
			x1 = x1 + source1.y * transformView->m01;
			triangle.points[1].x = x1 + transformView->tx;
			float y1 = source1.y * transformView->m11;
			y1 = y1 + source1.x * transformView->m10;
			triangle.points[1].y = y1 + transformView->ty;
			const BfmeVector2_1290 &source2 = vertices[indices[2]];
			float x2 = source2.x * transformView->m00;
			x2 = x2 + *(volatile const float *)&transformView->m01 * source2.y;
			triangle.points[2].x = x2 + transformView->tx;
			float y2 = source2.y * transformView->m11;
			y2 = y2 + source2.x * transformView->m10;
			triangle.points[2].y = y2 + transformView->ty;
			if (bfmeContains1283(&triangle, x, y))
				return true;
			++i;
			indices += 3;
		} while (i < (int)mesh);
	}
	return false;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /FAsc
