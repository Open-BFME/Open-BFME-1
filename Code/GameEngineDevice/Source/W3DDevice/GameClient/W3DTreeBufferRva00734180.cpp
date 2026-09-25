// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug
// W3DTreeBuffer method at retail 0x00734180: Zero Hour's cull without the sort keys; stores the camera's
// look-at vector and each tree's visibility, stepping through the trees by the tree index step.
#include "camera.h"

typedef int Int;
typedef bool Bool;

struct Rva00734180Tree
{
	char m_unreconstructed_000[0x44];
	Bool m_visible;
	char m_unreconstructed_045[3];
	SphereClass m_bounds;
	char m_unreconstructed_058[0xe8 - 0x58];
};

class W3DTreeBuffer
{
public:
	void rva00734180(const CameraClass *camera);

private:
	char m_unreconstructed_000000[0x1b0];
	Rva00734180Tree m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	char m_unreconstructed_2a7cb7[0x2a93c0 - 0x2a7cb7];
	Vector3 m_cameraLookAtVector;
	char m_unreconstructed_2a93cc[0x2a9900 - 0x2a93cc];
	Int m_treeIndexStep;
};

// ?rva00734180@W3DTreeBuffer@@QAEXPBVCameraClass@@@Z
void W3DTreeBuffer::rva00734180(const CameraClass *camera)
{
	Matrix3D camera_matrix = camera->Get_Transform();
	float zmod = -1;
	float x = zmod * camera_matrix[0][2];
	float y = zmod * camera_matrix[1][2];
	float z = zmod * camera_matrix[2][2];
	m_cameraLookAtVector.Set(x, y, z);

	Int curTree;
	for (curTree = 0; curTree < m_numTrees; curTree += m_treeIndexStep) {
		Bool visible = !camera->Cull_Sphere(m_trees[curTree].m_bounds);
		if (visible != m_trees[curTree].m_visible) {
			m_trees[curTree].m_visible = visible;
			m_anythingChanged = true;
		}
	}
	m_updateAllKeys = false;
}
