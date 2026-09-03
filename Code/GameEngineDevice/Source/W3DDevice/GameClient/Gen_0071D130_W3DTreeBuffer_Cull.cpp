// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME's W3DTreeBuffer layout is offset-based here; the ZH cull body is the
// source twin, while BFME inserted fields before the tree records and tail.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "always.h"
#include "rendobj.h"
#include "WW3D2/Camera.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

struct BFME_TREE
{
	Vector3 location;
	char m_pad0c[0x34];
	Int treeType;
	Bool visible;
	char m_pad45[3];
	SphereClass bounds;
	Real sortKey;
	char m_pad5c[0x48];
};

class W3DTreeBuffer
{
protected:
	void cull(const CameraClass *camera);

private:
	char m_pad00[0x1548];
	BFME_TREE m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	char m_pad1e1ccf[0x1709];
	Vector3 m_cameraLookAtVector;
	char m_pad1e33e4[0x53c];
	Int m_treeIndexStep;
};

void W3DTreeBuffer::cull(const CameraClass *camera)
{
	// Calulate the vector direction that the camera is looking at.
	Matrix3D camera_matrix = camera->Get_Transform();
	float zmod = -1;
	float x = zmod * camera_matrix[0][2] ;
	float y = zmod * camera_matrix[1][2] ;
	float z = zmod * camera_matrix[2][2] ;
	m_cameraLookAtVector.Set(x,y,z);

	Int curTree;
	for (curTree=0; curTree<m_numTrees; ) {
		Bool doKey = false;
		Bool visible = !camera->Cull_Sphere(m_trees[curTree].bounds);
		if (visible != m_trees[curTree].visible) {
			m_trees[curTree].visible = visible;
			m_anythingChanged = true;
			if (visible) {
				doKey = true;
			}
		}
		if (doKey || (visible && m_updateAllKeys)) {
			m_trees[curTree].sortKey = Vector3::Dot_Product(
				m_trees[curTree].location, m_cameraLookAtVector);
		}
		curTree += m_treeIndexStep;
	}
	m_updateAllKeys = false;
}
