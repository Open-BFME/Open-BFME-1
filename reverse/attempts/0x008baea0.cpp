// ?bfmePick1284@BfmePicker1284@@QAEPAUBfmePickNode1284@@HH@Z
// partial score=0.72 date=2026-08-30
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

struct BfmeMesh1290;
struct BfmeTransform2_1290
{
	float m00;
	float m10;
	float m01;
	float m11;
	float tx;
	float ty;
};
bool __stdcall bfmeMeshHitTest1290(
	BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform, int pointX, int pointY);

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

struct BfmePickDescriptor1284
{
	char m_padding00[8];
	char m_mesh08[0x2c - 8];
	int m_count2c;
	BfmePickElement1284 *m_elements30;
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
	BfmePickNode1284 *bfmePick1284(int pointX, int pointY);
};

BfmePickNode1284 *BfmePicker1284::bfmePick1284(int pointX, int pointY)
{
	int visited = 0;
	for (int entryIndex = g_bfmeHolderBU->m_count818 - 1;
		entryIndex >= 0 && visited != g_bfmeHolderBU->m_count818;
		--entryIndex, ++visited) {
		BfmePickEntry1284 *entry = &g_bfmeHolderBU->m_entries81c[entryIndex];
		BfmePickNode1284 *node = entry->m_node00;
		if (((unsigned char)(~(node->m_flags04 >> 15)) & 1) != 0)
			continue;

		BfmePickDescriptor1284 *descriptor = node->m_info50->m_descriptor0c;
		for (int elementIndex = 0; elementIndex < descriptor->m_count2c; ++elementIndex) {
			BfmePickElement1284 *element = &descriptor->m_elements30[elementIndex];
			if ((element->m_flags & 8) == 0)
				continue;

			BfmeM1208 transform = element->m_transform0c;
			bfmeMul1208(&entry->m_transform04, &transform, &transform);
			BfmePickObject1284 *object = element->m_object04;
			if (object->m_type == 1) {
				if (bfmeMeshHitTest1290((BfmeMesh1290 *)&descriptor->m_mesh08,
					(const BfmeTransform2_1290 *)&transform, pointX, pointY))
					return node;
			} else if (object->m_type == 2) {
				float xA = transform.m10 * object->m_yA0c +
					transform.m00 * object->m_xA08 + transform.tx;
				float xB = transform.m10 * object->m_yB14 +
					transform.m00 * object->m_xB10 + transform.tx;
				if ((float)pointX > xA && (float)pointX >= xB) {
					float yA = transform.m11 * object->m_yA0c +
						transform.m01 * object->m_xA08 + transform.ty;
					float yB = transform.m11 * object->m_yB14 +
						transform.m01 * object->m_xB10 + transform.ty;
					if ((float)pointY > yA && (float)pointY >= yB)
						return node;
				}
			}
		}
	}
	return 0;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
