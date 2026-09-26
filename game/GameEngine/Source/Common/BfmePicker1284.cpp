// Reverse-order point pick over the holder's node entries at 0x008BAEA0: each active node's
// flagged elements are composed with the entry transform, then hit-tested as a mesh (type 1,
// thiscall helper 0x008BAD90) or as an open rectangle (type 2).
struct BfmeM1208
{
	float m00;
	float m10;
	float m01;
	float m11;
	float tx;
	float ty;
};

void bfmeMul1208(const BfmeM1208 *left, const BfmeM1208 *right, BfmeM1208 *out);

struct BfmeTransform2_1290
{
	float m00;
	float m10;
	float m01;
	float m11;
	float tx;
	float ty;
};

struct BfmePickObject1284
{
	int m_type;
	int m_unused04;
	float m_xA08;
	float m_yA0c;
	float m_xB10;
	float m_yB14;
};

struct BfmePickElement1284
{
	unsigned char m_flags;
	char m_padding01[3];
	BfmePickObject1284 *m_object04;
	char m_padding08[4];
	BfmeM1208 m_transform0c;
	char m_padding24[0x44 - 0x24];
};

struct BfmeMesh1290
{
	char m_padding00[0x24];
	int m_count24;
	BfmePickElement1284 *m_elements28;
};

struct BfmePickDescriptor1284
{
	char m_padding00[8];
	BfmeMesh1290 m_mesh08;
};

struct BfmePickInfo1284
{
	char m_padding00[0x0c];
	BfmePickDescriptor1284 *m_descriptor0c;
};

struct BfmePickNode1284
{
	void *m_vtable;
	unsigned int m_flags04;
	char m_padding08[0x50 - 8];
	BfmePickInfo1284 *m_info50;
};

struct BfmePickEntry1284
{
	BfmePickNode1284 *m_node00;
	BfmeM1208 m_transform04;
};

struct BfmePickWorld1284
{
	char m_padding000[0x818];
	int m_count818;
	BfmePickEntry1284 *m_entries81c;
};

extern BfmePickWorld1284 *g_bfmeHolderBU;

class BfmePicker1284
{
public:
	bool bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform,
		int pointX, int pointY);
	BfmePickNode1284 *bfmePick1284(int pointX, int pointY);
};

BfmePickNode1284 *BfmePicker1284::bfmePick1284(int pointX, int pointY)
{
	int visited = 0;
	for (int entryIndex = g_bfmeHolderBU->m_count818 - 1; entryIndex >= 0; --entryIndex) {
		BfmePickNode1284 *node = g_bfmeHolderBU->m_entries81c[entryIndex].m_node00;
		if (((unsigned char)(~(node->m_flags04 >> 15)) & 1) != 0)
			continue;

		BfmeMesh1290 *mesh = &node->m_info50->m_descriptor0c->m_mesh08;
		for (int elementIndex = 0; elementIndex < mesh->m_count24; ++elementIndex) {
			if ((mesh->m_elements28[elementIndex].m_flags & 8) == 0)
				continue;

			BfmeM1208 transform = mesh->m_elements28[elementIndex].m_transform0c;
			bfmeMul1208(&g_bfmeHolderBU->m_entries81c[entryIndex].m_transform04,
				&transform, &transform);
			BfmePickObject1284 *object = mesh->m_elements28[elementIndex].m_object04;
			if (object->m_type == 1) {
				if (bfmeMeshHitTest1290(mesh, (const BfmeTransform2_1290 *)&transform,
					pointX, pointY))
					return g_bfmeHolderBU->m_entries81c[entryIndex].m_node00;
			} else if (object->m_type == 2) {
				float xA = object->m_xA08;
				float xB = object->m_xB10;
				float yA = object->m_yA0c;
				float yB = object->m_yB14;
				if ((float)pointX > transform.m10 * yA + transform.m00 * xA + transform.tx &&
					(float)pointX < transform.m10 * yB + transform.m00 * xB + transform.tx &&
					(float)pointY > transform.m11 * yA + transform.m01 * xA + transform.ty &&
					(float)pointY < transform.m11 * yB + transform.m01 * xB + transform.ty)
					return g_bfmeHolderBU->m_entries81c[entryIndex].m_node00;
			}
		}
		if (++visited == g_bfmeHolderBU->m_count818)
			return 0;
	}
	return 0;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
