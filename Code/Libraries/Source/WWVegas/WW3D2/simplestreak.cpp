// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug
//
// Bitmap2DObjClass::Render, retail 0x00955C40 (171 bytes).
//
// The copy constructor at 0x00956140 installs the Bitmap2DObjClass table and
// lays out the two SimpleDynVecClass members at +0xC8/+0xD8, followed by the
// BFME renderer object at +0xE8.  The table's Render slot is +0x30, while the
// calls at +0x108 and +0x180 are RenderObjClass's bounding-sphere and hidden
// predicates in the BFME ABI.  The call at 0x00975100 receives that renderer
// object and its seven render arguments, which identifies BfmeThingVGX::Render.

#include "rendobj.h"
#include "rinfo.h"
#include "simplevec.h"
#include "ww3d.h"

class BfmeTexVGX;

class TextureRef
{
	BfmeTexVGX *m_ptr;
};

class BfmeThingVGX
{
public:
	void Render(RenderInfoClass &, const Matrix3D &, unsigned int, Vector3 *, float *,
		const SphereClass &);
	ShaderClass Get_Shader() const { return m_shader; }

	TextureRef m_tex;
	ShaderClass m_shader;
	float m_width;
	Vector3 m_color;
	float m_opacity;
	float m_1c;
	char m_20;
};

class Bitmap2DObjClass : public RenderObjClass
{
public:
	virtual void Render(RenderInfoClass &rinfo);

private:
	SimpleDynVecClass<Vector3> m_vertices;
	SimpleDynVecClass<float> m_widths;
	BfmeThingVGX m_vgx;
};

void Bitmap2DObjClass::Render(RenderInfoClass &rinfo)
{
	if (!Is_Not_Hidden_At_All()) {
		return;
	}

	unsigned int sort_level = 0;
	if (!WW3D::Is_Sorting_Enabled()) {
		sort_level = m_vgx.Get_Shader().Guess_Sort_Level();
	}

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != 0) {
		WW3D::Add_To_Static_Sort_List(this, sort_level);
		return;
	}

	if (m_vertices.Count() < 2) {
		return;
	}
	if (m_vertices.Count() != m_widths.Count()) {
		return;
	}

	SphereClass bounding_sphere;
	Get_Obj_Space_Bounding_Sphere(bounding_sphere);
	m_vgx.Render(rinfo, Transform, m_vertices.Count(), &m_vertices[0], &m_widths[0],
		bounding_sphere);
}
