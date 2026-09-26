// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "W3DDevice/GameClient/W3DTreeBuffer.h"

#include <stdio.h>
#include <string.h>
#include <assetmgr.h>
#include <texture.h>
#include "Common/MapReaderWriterInfo.h"
#include "Common/FileSystem.h" 
#include "Common/file.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameClient/ClientRandomValue.h"
#include "GameClient/FXList.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/Module/W3DTreeDraw.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "W3DDevice/GameClient/W3DProjectedShadow.h"
#include "WW3D2/Camera.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Matinfo.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "d3dx8tex.h"

// BFME's shrub buffer (vtable 0x01120F94, terrain +0x3098) keeps Zero Hour's tree-buffer
// code; W3DShrubBuffer.cpp's __FILE__ literal binds to this run of retail bodies.

// upstream layout of the tree-buffer twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DShrubBuffer
{
public:
	void pushAsideTree(DrawableID id, const Coord3D *pusherPos,
		const Coord3D *pusherDirection, ObjectID pusherID);

protected:
	void cull(const CameraClass *camera);
	Int getPartitionBucket(const Coord3D &pos) const;
	UnsignedInt doLighting(const Vector3 *normal, const GlobalData::TerrainLighting *objectLighting,
		const Vector3 *emissive, UnsignedInt vertDiffuse, Real scale) const;
};

// BFME inserted fields before the tree records and in the tail, so the Zero Hour
// header cannot describe the offsets used by retail's otherwise shared cull body.
struct BFMETreeCullTree
{
	Vector3 m_location;
	char m_unreconstructed_00c[0x34];
	Int m_treeType;
	Bool m_visible;
	char m_unreconstructed_045[3];
	SphereClass m_bounds;
	Real m_sortKey;
	DrawableID m_drawableID;
	Real m_pushAside;
	Real m_pushAsideDelta;
	Real m_pushAsideSin;
	Real m_pushAsideCos;
	ObjectID m_pushAsideSource;
	UnsignedInt m_lastFrameUpdated;
	char m_unreconstructed_078[0x2c];
};

struct BFMETreePushData
{
	char m_unreconstructed_000[0x10];
	UnsignedInt m_framesToMoveOutward;
};

struct BFMETreePushType
{
	BFMETreePushData *m_data;
	char m_unreconstructed_004[0x58];
};

struct BFMETreeCullView
{
	char m_unreconstructed_000000[0x1548];
	BFMETreeCullTree m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	char m_unreconstructed_1e1ccf[0x1709];
	Vector3 m_cameraLookAtVector;
	char m_unreconstructed_1e33e4[0x53c];
	Int m_treeIndexStep;
};

struct BFMETreePushView
{
	char m_unreconstructed_000000[0x1548];
	BFMETreeCullTree m_trees[12000];
	Int m_numTrees;
	Bool m_anythingChanged;
	Bool m_anyPushChanged;
	Bool m_updateAllKeys;
	char m_unreconstructed_1e1ccf[0x25];
	BFMETreePushType m_treeTypes[64];
};

extern GameLogic *TheBfmeGameLogic;

//=============================================================================
// W3DShrubBuffer::cull
//=============================================================================
/** Culls the trees, marking the visible flag.  If a tree becomes visible, it sets
it's sortKey */
//=============================================================================
// ?cull@W3DShrubBuffer@@IAEXPBVCameraClass@@@Z
void W3DShrubBuffer::cull(const CameraClass * camera)
{
	BFMETreeCullView *self = (BFMETreeCullView *)this;

	// Calulate the vector direction that the camera is looking at.
	Matrix3D camera_matrix = camera->Get_Transform();
	float zmod = -1;
	float x = zmod * camera_matrix[0][2] ;
	float y = zmod * camera_matrix[1][2] ;
	float z = zmod * camera_matrix[2][2] ;
	self->m_cameraLookAtVector.Set(x,y,z);

	Int curTree;
	for (curTree=0; curTree<self->m_numTrees; ) {
		Bool doKey = false;
		Bool visible = !camera->Cull_Sphere(self->m_trees[curTree].m_bounds);
		if (visible != self->m_trees[curTree].m_visible) {
			self->m_trees[curTree].m_visible = visible;
			self->m_anythingChanged = true;
			if (visible) {
				doKey = true;
			}
		}
		if (doKey || (visible && self->m_updateAllKeys)) {
			// The scoped view otherwise reverses three equivalent x87 loads under MSVC 7.1.
			const volatile Real &locationX = self->m_trees[curTree].m_location.X;
			const volatile Real &lookAtY = self->m_cameraLookAtVector.Y;
			const volatile Real &lookAtZ = self->m_cameraLookAtVector.Z;
			self->m_trees[curTree].m_sortKey =
				locationX * self->m_cameraLookAtVector.X +
				self->m_trees[curTree].m_location.Y * lookAtY +
				self->m_trees[curTree].m_location.Z * lookAtZ;
		}
		curTree += self->m_treeIndexStep;
	}
	self->m_updateAllKeys = false;
}
//=============================================================================
// W3DShrubBuffer::getPartitionBucket
//=============================================================================
/** Returns the bucket index into m_areaPartition for a given location. */
//=============================================================================
// Defined in W3DShrubBufferRva00720D10.cpp so the append caller can see
// that this partition lookup does not retain or modify its position argument.

//=============================================================================
// W3DShrubBuffer::doLighting
//=============================================================================
/** Calculates the diffuse lighting as affected by dynamic lighting. */
//=============================================================================
UnsignedInt W3DShrubBuffer::doLighting(const Vector3 *normal,  
															const GlobalData::TerrainLighting	*objectLighting, 
															const Vector3 *emissive, UnsignedInt vertDiffuse, Real scale) const
{

	Real shadeR, shadeG, shadeB;
	Real shade;
	shadeR = objectLighting[0].ambient.red+emissive->X;	//only the first light contributes to ambient
	shadeG = objectLighting[0].ambient.green+emissive->Y;
	shadeB = objectLighting[0].ambient.blue+emissive->Z;

	Int i;
	for	(i=0; i<MAX_GLOBAL_LIGHTS; i++) {
		Vector3 lightDirection(objectLighting[i].lightPos.x, objectLighting[i].lightPos.y, objectLighting[i].lightPos.z);
		lightDirection.Normalize();
		Vector3 lightRay(-lightDirection.X, -lightDirection.Y, -lightDirection.Z);
		shade = WWMath::Fabs(Vector3::Dot_Product(lightRay, *normal));

		if (shade > 1.0) shade = 1.0;
		if(shade < 0.0f) shade = 0.0f;
		shadeR += shade*objectLighting[i].diffuse.red;
		shadeG += shade*objectLighting[i].diffuse.green;
		shadeB += shade*objectLighting[i].diffuse.blue;	
	}

	if (vertDiffuse!=0xFFFFFFFF) {
		shade = vertDiffuse&0xff; //blue;
		shadeB *= shade/255.0f;
		shade = (vertDiffuse>>8)&0xFF; // green;
		shadeG *= shade/255.0f;
		shade = (vertDiffuse>>16)&0xFF; // red;
		shadeR *= shade/255.0f;
	}

	shadeR *= scale;
	shadeG *= scale;
	shadeB *= scale;
	
	if (shadeR > 1.0) shadeR = 1.0;
	if(shadeR < 0.0f) shadeR = 0.0f;
	if (shadeG > 1.0) shadeG = 1.0;
	if(shadeG < 0.0f) shadeG = 0.0f;
	if (shadeB > 1.0) shadeB = 1.0;
	if(shadeB < 0.0f) shadeB = 0.0f;

	const Real alpha = 255.0;
	return (UnsignedInt)(shadeB*255.0f) | ((Int)(shadeG*255.0f) << 8) | ((Int)(shadeR*255.0f) << 16) | ((Int)alpha << 24);
	
}

//=============================================================================
// W3DShrubBuffer::pushAsideTree
//=============================================================================
/** Push sideways tree or grass. */
//=============================================================================
void W3DShrubBuffer::pushAsideTree(DrawableID id, const Coord3D *pusherPos, 
																	const Coord3D *pusherDirection, ObjectID pusherID )
{
	if (*(const UnsignedByte *)((const char *)TheWritableGlobalData + 0x18) == 0)
		return;

	BFMETreePushView *self = reinterpret_cast<BFMETreePushView *>(this);
	for (Int i = 0; i < self->m_numTrees; ++i) {
		BFMETreeCullTree *tree = &self->m_trees[i];
		if (tree->m_drawableID == id) {
			UnsignedInt lastFrame = tree->m_lastFrameUpdated;
			tree->m_lastFrameUpdated = TheBfmeGameLogic->getFrame();
			if (tree->m_pushAsideSource == pusherID) {
				if (tree->m_lastFrameUpdated - lastFrame < 3)
					return;
			}

			if (tree->m_pushAside != 0.0f)
				return;

			tree->m_pushAsideSource = pusherID;
			Coord3D delta;
			delta.set(tree->m_location.X, tree->m_location.Y, tree->m_location.Z);
			delta.sub(pusherPos);
			if (pusherDirection->x * delta.y - pusherDirection->y * delta.x > 0.0f) {
				tree->m_pushAsideCos = -pusherDirection->y;
				tree->m_pushAsideSin = pusherDirection->x;
			} else {
				tree->m_pushAsideCos = pusherDirection->y;
				tree->m_pushAsideSin = -pusherDirection->x;
			}

			self->m_anyPushChanged = true;
			tree->m_pushAsideDelta = 1.0f /
				((Real)self->m_treeTypes[tree->m_treeType].m_data->m_framesToMoveOutward *
				*(Real *)((char *)this + 0x1e3910));
		}
	}
}
