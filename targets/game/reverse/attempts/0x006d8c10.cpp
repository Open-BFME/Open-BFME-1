// ?load@W3DBridge@@QAE_NW4BodyDamageType@@@Z
// partial score=0.9941679626749611 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// Native bank: W3DBridge::load, RVA006D8C10,2836 bytes including four switch entries.
// The 0x114-byte bridge layout is witnessed by its landed constructor and vertex methods.
// Rva006D8C10GeometryView preserves the witnessed count/vertex slots +28/+30;
// the shared geometry header has +2C/+34 and is not changed here.
// The +14 virtual returns a MeshClass pointer: MeshClass table0113C390 selects
// body0092C710 (mov eax,ecx;ret), and this caller subsequently reads model+C8.
// Existing direct callees and the four switch destinations are independently checked.

#include "ascii_string.h"
#include "matrix3d.h"
#include "rendobj.h"
#include "mesh.h"
#include "meshmdl.h"
#include "texture.h"
#include <string.h>
#include <stdlib.h>
#include <float.h>
typedef bool Bool;
typedef int Int;
typedef float Real;
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
enum BodyDamageType {BODY_PRISTINE,BODY_DAMAGED,BODY_REALLYDAMAGED,BODY_RUBBLE};
class TerrainRoadType {
public:
 AsciiString getTexture(); AsciiString getBridgeModel();
 AsciiString getTextureDamaged(); AsciiString getBridgeModelNameDamaged();
 AsciiString getTextureReallyDamaged(); AsciiString getBridgeModelNameReallyDamaged();
 AsciiString getTextureBroken(); AsciiString getBridgeModelNameBroken();
 float getBridgeScale() {return m_bridgeScale;}
 char pad[0x1c];float m_bridgeScale;
};
class TerrainRoadCollection {public: TerrainRoadType *findBridge(AsciiString);};
extern TerrainRoadCollection *TheTerrainRoads;
extern RenderObjClass *Create_Render_Obj(const char*);
class BFMEWaterTrackTextureHandle {
public:
 TextureClass *m_texture;
 ~BFMEWaterTrackTextureHandle() {if(m_texture)m_texture->Release_Ref();}
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
inline void AssignTexture(TextureClass *&dest,const BFMEWaterTrackTextureHandle& value) {
 if(value.m_texture)value.m_texture->Add_Ref();
 if(dest)dest->Release_Ref();
 dest=value.m_texture;
}
struct Rva006D8C10GeometryView {
 char pad[0x28]; int vertexCount; void *polygons; ShareBufferClass<Vector3> *vertices;
};
inline int BridgeVertexCount(MeshClass *mesh) { return ((Rva006D8C10GeometryView*)mesh->Peek_Model())->vertexCount; }
inline Vector3 *BridgeVertices(MeshClass *mesh) { return ((Rva006D8C10GeometryView*)mesh->Peek_Model())->vertices->Get_Array(); }
class Rva006D8C10MeshSlotView {
public:
 virtual void slot0()=0; virtual void slot1()=0; virtual void slot2()=0;
 virtual void slot3()=0; virtual void slot4()=0;
 virtual MeshClass *slot14()=0;
};
inline MeshClass *BridgeMesh(RenderObjClass *object) { return ((Rva006D8C10MeshSlotView*)object)->slot14(); }
class W3DBridge {
public:
 Bool load(BodyDamageType);
 void clearBridge();
 enum {FIXED_BRIDGE,SECTIONAL_BRIDGE};
 Vector3 m_start,m_end;
 float m_scale,m_length;
 int m_bridgeType;
 float m_bounds[4];
 TextureClass *m_bridgeTexture;
 MeshClass *m_leftMesh;
 Matrix3D m_leftMtx;
 float m_minY,m_maxY,m_leftMinX,m_leftMaxX;
 MeshClass *m_sectionMesh;
 Matrix3D m_sectionMtx;
 float m_sectionMinX,m_sectionMaxX;
 MeshClass *m_rightMesh;
 Matrix3D m_rightMtx;
 float m_rightMinX,m_rightMaxX;
 int m_firstIndex,m_numVertex,m_firstVertex,m_numPolygons;
 bool m_visible;char pad[3];
 AsciiString m_templateName;
 BodyDamageType m_curDamageState;
 bool m_enabled;
};
Bool W3DBridge::load(enum BodyDamageType curDamageState)
{
	REF_PTR_RELEASE(m_bridgeTexture);
	REF_PTR_RELEASE(m_leftMesh);
	REF_PTR_RELEASE(m_sectionMesh);
	REF_PTR_RELEASE(m_rightMesh);

	Real scale, width, length;
	char textureFile[_MAX_PATH] = "No Texture";
	char modelName[_MAX_PATH] = "BRIDGESECTIONAL";

	/// @todo, should these be defaults in INI??? CBD
	scale = 0.7f;
	width = 34;
	length = 170;

	// try to find bridge in INI
	TerrainRoadType *bridge = TheTerrainRoads->findBridge( m_templateName );
	if (!bridge) return false;

	scale = bridge->getBridgeScale();
	switch (curDamageState) {
		default: return false;

		case 	BODY_PRISTINE:
			strcpy( textureFile, bridge->getTexture().str() );
			strcpy( modelName, bridge->getBridgeModel().str() );
			break;
		case BODY_DAMAGED:
			strcpy( textureFile, bridge->getTextureDamaged().str() );
			strcpy( modelName, bridge->getBridgeModelNameDamaged().str() );
			break;
		case BODY_REALLYDAMAGED:
			strcpy( textureFile, bridge->getTextureReallyDamaged().str() );
			strcpy( modelName, bridge->getBridgeModelNameReallyDamaged().str() );
			break;
		case BODY_RUBBLE:
			strcpy( textureFile, bridge->getTextureBroken().str() );
			strcpy( modelName, bridge->getBridgeModelNameBroken().str() );
			break;
	}

	
	char left[_MAX_PATH];
	char section[_MAX_PATH];
	char right[_MAX_PATH];

	strcpy(left, modelName);
	strcat(left, ".BRIDGE_LEFT");
	strcpy(section, modelName);
	strcat(section, ".BRIDGE_SPAN");
	strcpy(right, modelName);
	strcat(right, ".BRIDGE_RIGHT");

	AssignTexture(m_bridgeTexture, BFMEGetWaterTrackTexture(textureFile, 3, 0)); 
	m_leftMtx.Make_Identity();
	m_rightMtx.Make_Identity();
	m_sectionMtx.Make_Identity();

	RenderObjClass *pObj = Create_Render_Obj(modelName );
	if (!pObj) return false;
	Int i;
	for (i=0; i<pObj->Get_Num_Sub_Objects(); i++) {
		RenderObjClass *pSub = pObj->Get_Sub_Object(i);
		Matrix3D mtx = pSub->Get_Transform();
		if (0==strnicmp(left, pSub->Get_Name(), strlen(left))) {
			m_leftMtx = mtx;
			strcpy(left, pSub->Get_Name());
		}
		if (0==strnicmp(section, pSub->Get_Name(), strlen(section))) {
			m_sectionMtx = mtx;
			strcpy(section, pSub->Get_Name());
		}
		if (0==strnicmp(right, pSub->Get_Name(), strlen(right))) {
			m_rightMtx = mtx;
			strcpy(right, pSub->Get_Name());
		}
		REF_PTR_RELEASE(pSub);
		//DEBUG_LOG(("Sub obj name %s\n", pSub->Get_Name()));
	}

	REF_PTR_RELEASE(pObj);

	m_leftMesh = BridgeMesh(Create_Render_Obj(left));
	m_sectionMesh = BridgeMesh(Create_Render_Obj(section));
	m_rightMesh = BridgeMesh(Create_Render_Obj(right));
	m_scale = scale;


	if (m_leftMesh == NULL) {
		clearBridge();
		return(false);
	}
	m_bridgeType = SECTIONAL_BRIDGE;

	if (m_rightMesh == NULL || m_sectionMesh == NULL) {
		m_bridgeType = FIXED_BRIDGE;
	}

	const Int numVertex = BridgeVertexCount(m_leftMesh);
	Vector3 *pVert = BridgeVertices(m_leftMesh);
	m_leftMinX = FLT_MAX;
	m_leftMaxX = -FLT_MAX;
	m_minY = FLT_MAX;
	m_maxY = -FLT_MAX;
	for (i=0; i++ < numVertex;) {
		Vector3 vert;
		Matrix3D::Transform_Vector(m_leftMtx, *pVert, &vert);
		if (m_leftMinX > vert.X) m_leftMinX = vert.X;
		if (m_minY > vert.Y) m_minY = vert.Y;
		if (vert.X > m_leftMaxX) m_leftMaxX = vert.X;
		if (vert.Y > m_maxY) m_maxY = vert.Y;
        ++pVert;	 // Note - we assume all sections are the same width, so we only do maxY for first section.
	}
	if (m_bridgeType == SECTIONAL_BRIDGE) {
		const Int sectionCount = BridgeVertexCount(m_sectionMesh);
		pVert = BridgeVertices(m_sectionMesh);
		m_sectionMinX = FLT_MAX;
		m_sectionMaxX = -FLT_MAX;
		for (i=sectionCount; i-- > 0;) {
			Vector3 vert;
			Matrix3D::Transform_Vector(m_sectionMtx, *pVert, &vert);
			if (m_sectionMinX > vert.X) m_sectionMinX = vert.X;
			if (vert.X > m_sectionMaxX) m_sectionMaxX = vert.X;
        ++pVert;
		}

		const Int rightCount = BridgeVertexCount(m_rightMesh);
		pVert = BridgeVertices(m_rightMesh);
		m_rightMinX = FLT_MAX;
		m_rightMaxX = -FLT_MAX;
		for (i=rightCount; i-- > 0;) {
			Vector3 vert;
			Matrix3D::Transform_Vector(m_rightMtx, *pVert, &vert);
			if (m_rightMinX > vert.X) m_rightMinX = vert.X;
			if (vert.X > m_rightMaxX) m_rightMaxX = vert.X;
        ++pVert;
		}
	} else {
		m_sectionMinX = m_leftMaxX;
		m_sectionMaxX = m_leftMaxX;
		m_rightMinX = m_leftMaxX;
		m_rightMaxX = m_leftMaxX;
	}
	length = m_rightMaxX - m_leftMinX;
	if (length < 1) length = 1;
	m_length = length;
	if (m_bridgeType == SECTIONAL_BRIDGE) {
		Real allowableError = 0.05f*length;
		// make sure the sections align.

		if (m_leftMaxX>m_sectionMinX+allowableError) {
			m_bridgeType = FIXED_BRIDGE;
		}

		if (m_rightMinX<m_sectionMaxX-allowableError) {
			m_bridgeType = FIXED_BRIDGE;
		}

	}
	return(true);
}


