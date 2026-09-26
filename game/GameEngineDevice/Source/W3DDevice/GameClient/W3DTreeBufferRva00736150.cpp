// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// W3DTreeBuffer method at retail 0x00736150: gives a tree its type's model and the model of type +0xD0 at the
// tree's position and rotation, starts the +0xD4 countdown and plays the type's effect.

#include "matrix3.h"
#include "rendobj.h"
#include "scene.h"
#include "ascii_string.h"

template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int Int;
typedef float Real;

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

class TerrainLogicP48Owner
{
public:
	void find(Int id);
};

extern TerrainLogicP48Owner *TheTerrainLogic;
extern SceneClass *g_Va012F8058;

RenderObjClass *Create_Render_Obj(const char *name);
void Rva00739B30(RenderObjClass *object, bool geometry);
void Rva00739900Forward(void *object, Real value);

struct Rva00736150TypeData
{
	unsigned char m_pad00[8];
	AsciiString m_modelName;
	unsigned char m_pad0c[0x4c - 0x0c];
	Int m_duration;
	const FXList *m_effect;
	bool m_flag54;
};

struct Rva00736150Type
{
	unsigned char m_pad00[0x20];
	const Rva00736150TypeData *m_data;
	unsigned char m_pad24[0x4c - 0x24];
	AsciiString m_modelName;
	unsigned char m_pad50[0x58 - 0x50];
	Int m_field58;
};

struct Rva00736150Tree
{
	Coord3D m_location;
	Real m_scale;
	Matrix3D m_transform;
	Int m_treeType;
	unsigned char m_pad44[0x58 - 0x44];
	Int m_drawableID;
	unsigned char m_pad5c[0x80 - 0x5c];
	Int m_field80;
	unsigned char m_pad84[0xc4 - 0x84];
	bool m_flagc4;
	unsigned char m_padc5[0xc8 - 0xc5];
	Int m_fieldc8;
	unsigned char m_padcc[0xd0 - 0xcc];
	Int m_fieldd0;
	Int m_fieldd4;
	RenderObjClass *m_fieldd8;
	RenderObjClass *m_fielddc;
	unsigned char m_pade0[0xe8 - 0xe0];
};

class W3DTreeBuffer
{
public:
	void rva00736150(Int index, Int request);

private:
	unsigned char m_pad0000[0x1b0];
	Rva00736150Tree m_trees[12000];
	Int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad2a7cb5[0x2a7cbc - 0x2a7cb5];
	Rva00736150Type m_treeTypes[64];
};

// ?rva00736150@W3DTreeBuffer@@QAEXHH@Z
void W3DTreeBuffer::rva00736150(Int index, Int request)
{
	if (index >= m_numTrees)
		return;
	Int type = m_trees[index].m_treeType;
	if (type < 0)
		return;
	if (request == 1) {
		if (m_treeTypes[type].m_data->m_flag54)
			return;
	} else if (request == 2) {
		if (!m_treeTypes[type].m_data->m_flag54)
			return;
	}
	if (!m_trees[index].m_flagc4 && m_trees[index].m_field80 != 0) {
		TheTerrainLogic->find(m_trees[index].m_drawableID);
		return;
	}
	if (m_trees[index].m_flagc4 || m_trees[index].m_field80 != 0)
		return;

	m_trees[index].m_fieldd4 = m_treeTypes[type].m_data->m_duration;
	m_trees[index].m_fieldc8 = request;
	if (m_trees[index].m_fieldd8 != 0) {
		m_trees[index].m_fieldd8->Release_Ref();
		m_trees[index].m_fieldd8 = 0;
	}
	m_trees[index].m_fieldd8 = Create_Render_Obj(m_treeTypes[type].m_modelName.str());
	Rva00739B30(m_trees[index].m_fieldd8, false);
	g_Va012F8058->Add_Render_Object(m_trees[index].m_fieldd8);
	Matrix3D transform = m_trees[index].m_fieldd8->Get_Transform();
	transform[0][3] = m_trees[index].m_location.x;
	transform[1][3] = m_trees[index].m_location.y;
	transform[2][3] = m_trees[index].m_location.z;
	Matrix3 rotation(m_trees[index].m_transform);
	transform.Set_Rotation(rotation);
	m_trees[index].m_fieldd8->Set_Transform(transform);

	if (m_trees[index].m_fielddc != 0) {
		m_trees[index].m_fielddc->Release_Ref();
		m_trees[index].m_fielddc = 0;
	}
	if (m_treeTypes[type].m_field58 != -2) {
		m_trees[index].m_fielddc = Create_Render_Obj(m_treeTypes[m_trees[index].m_fieldd0].m_data->m_modelName.str());
		Rva00739B30(m_trees[index].m_fielddc, false);
		g_Va012F8058->Add_Render_Object(m_trees[index].m_fielddc);
		transform = m_trees[index].m_fielddc->Get_Transform();
		transform[0][3] = m_trees[index].m_location.x;
		transform[1][3] = m_trees[index].m_location.y;
		transform[2][3] = m_trees[index].m_location.z;
		transform.Set_Rotation(rotation);
		m_trees[index].m_fielddc->Set_Transform(transform);
	}
	if (m_trees[index].m_fieldd8 != 0)
		Rva00739900Forward(m_trees[index].m_fieldd8, 1.0f);
	if (m_trees[index].m_fielddc != 0)
		Rva00739900Forward(m_trees[index].m_fielddc, 0.0f);
	if (m_treeTypes[type].m_data->m_effect != 0) {
		Coord3D position;
		position.x = m_trees[index].m_location.x;
		position.y = m_trees[index].m_location.y;
		position.z = m_trees[index].m_location.z;
		FXList::doFXPos(m_treeTypes[type].m_data->m_effect, &position, 0, 0.0f, 0);
	}
	m_anythingChanged = true;
}
