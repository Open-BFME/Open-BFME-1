// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug
// W3DShrubBuffer method at retail 0x007202F0, twin of W3DTreeBuffer's at 0x00736150: gives a shrub its type's
// model and the model of type +0x90 at its position and rotation, starts the +0x94 countdown and plays the effect.

#include "matrix3.h"
#include "rendobj.h"
#include "scene.h"
#include "ascii_string.h"

template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern SceneClass *g_Va012F8058;

RenderObjClass *Create_Render_Obj(const char *name);
void Rva00739B30(RenderObjClass *object, bool geometry);
void Rva00739900Forward(void *object, Real value);

struct Coord3D
{
	Real x, y, z;
};

class FXList
{
public:
	static void doFXPos(const FXList *list, const Coord3D *position, const Matrix3D *matrix, Real speed,
		const Coord3D *direction);
};

struct Rva007202F0TypeData
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	unsigned char m_pad0c[0x4c - 0x0c];
	Int m_toppleFrames;
	const FXList *m_effect;
	bool m_doShadow;
};

struct Rva007202F0Type
{
	unsigned char m_pad00[0x20];
	const Rva007202F0TypeData *m_data;
	unsigned char m_pad24[0x4c - 0x24];
	AsciiString m_modelName;
	unsigned char m_pad50[0x58 - 0x50];
	Int m_state;
};

struct Rva007202F0Tree
{
	Coord3D m_location;
	Real m_scale;
	Matrix3D m_transform;
	Int m_treeType;
	unsigned char m_pad44[0x88 - 0x44];
	Int m_toppleState;
	Int m_uprightType;
	Int m_toppledType;
	UnsignedInt m_sinkFrames;
	RenderObjClass *m_toppleObject;
	RenderObjClass *m_pushAsideObject;
	unsigned char m_pada0[0xa4 - 0xa0];
};

class W3DShrubBuffer
{
public:
	void dispatch(Int index, Int request);

private:
	unsigned char m_pad0000[0x1548];
	Rva007202F0Tree m_trees[12000];
	Int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad1e1ccd[0x1e1cd4 - 0x1e1ccd];
	Rva007202F0Type m_treeTypes[64];
};

// ?dispatch@W3DShrubBuffer@@QAEXHH@Z
void W3DShrubBuffer::dispatch(Int index, Int request)
{
	Int type = m_trees[index].m_treeType;
	if (index >= m_numTrees)
		return;
	if (type < 0)
		return;
	if (request == 1) {
		if (m_treeTypes[type].m_data->m_doShadow)
			return;
	} else if (request == 2) {
		if (!m_treeTypes[type].m_data->m_doShadow)
			return;
	}
	m_trees[index].m_sinkFrames = m_treeTypes[type].m_data->m_toppleFrames;
	m_trees[index].m_toppleState = request;
	if (m_trees[index].m_toppleObject != 0) {
		m_trees[index].m_toppleObject->Release_Ref();
		m_trees[index].m_toppleObject = 0;
	}
	m_trees[index].m_toppleObject = Create_Render_Obj(m_treeTypes[type].m_modelName.str());
	Rva00739B30(m_trees[index].m_toppleObject, false);
	g_Va012F8058->Add_Render_Object(m_trees[index].m_toppleObject);
	Matrix3D transform = m_trees[index].m_toppleObject->Get_Transform();
	transform[0][3] = m_trees[index].m_location.x;
	transform[1][3] = m_trees[index].m_location.y;
	transform[2][3] = m_trees[index].m_location.z;
	Matrix3 rotation(m_trees[index].m_transform);
	transform.Set_Rotation(rotation);
	m_trees[index].m_toppleObject->Set_Transform(transform);

	if (m_trees[index].m_pushAsideObject != 0) {
		m_trees[index].m_pushAsideObject->Release_Ref();
		m_trees[index].m_pushAsideObject = 0;
	}
	if (m_treeTypes[type].m_state != -2) {
		m_trees[index].m_pushAsideObject = Create_Render_Obj(m_treeTypes[m_trees[index].m_toppledType].m_data->m_modelName.str());
		Rva00739B30(m_trees[index].m_pushAsideObject, false);
		g_Va012F8058->Add_Render_Object(m_trees[index].m_pushAsideObject);
		transform = m_trees[index].m_pushAsideObject->Get_Transform();
		transform[0][3] = m_trees[index].m_location.x;
		transform[1][3] = m_trees[index].m_location.y;
		transform[2][3] = m_trees[index].m_location.z;
		transform.Set_Rotation(rotation);
		m_trees[index].m_pushAsideObject->Set_Transform(transform);
	}
	if (m_trees[index].m_toppleObject != 0)
		Rva00739900Forward(m_trees[index].m_toppleObject, 1.0f);
	if (m_trees[index].m_pushAsideObject != 0)
		Rva00739900Forward(m_trees[index].m_pushAsideObject, 0.0f);
	if (m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = m_trees[index].m_location.x;
		position.y = m_trees[index].m_location.y;
		position.z = m_trees[index].m_location.z;
		FXList::doFXPos(m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
