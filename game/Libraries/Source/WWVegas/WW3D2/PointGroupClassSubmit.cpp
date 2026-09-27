// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "pointgr.h"
#include "vector.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;
extern VectorClass<Vector4> VertexDiffuse;
extern DX8IndexBufferClass *Tris;
extern DX8IndexBufferClass *Quads;
extern SortingIndexBufferClass *SortingTris;
extern SortingIndexBufferClass *SortingQuads;
extern bool Rva012D6D75;

class BoxDynamicVBAccessClass
{
	const FVFInfoClass &FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass *VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type, unsigned fvf, unsigned short vertex_count, unsigned buffer);
	~BoxDynamicVBAccessClass();

	const FVFInfoClass &FVF_Info() const { return FVFInfo; }

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

struct Rva0093B340Center
{
	float X, Y, Z;
	Rva0093B340Center() : X(0.0f), Y(0.0f), Z(0.0f) {}
};

static __forceinline void InsertPointTriangles(
	unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
	Rva0093B340Center center;
	SortingRendererClass::Insert_Triangles(
		reinterpret_cast<const SphereClass &>(center), a, b, c, d);
}

static __forceinline void ClampPointColor(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	// This CMOV branch matches the 94-byte sequence in the matched clamp at 0x0090F310.
	__asm
	{
		mov esi, dword ptr color
		mov edx, 0x3f800000

		mov edi, dword ptr [esi]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi], edi

		mov edi, dword ptr [esi+4]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+4], edi

		mov edi, dword ptr [esi+8]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+8], edi

		mov edi, dword ptr [esi+12]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+12], edi
	}
}

static __forceinline unsigned ConvertPointColor(const Vector4 &color)
{
	Vector4 clamped_color = color;
	ClampPointColor(clamped_color);
	return DX8Wrapper::Convert_Color(
		reinterpret_cast<const Vector3 &>(clamped_color), clamped_color[3]);
}

static __forceinline unsigned ConvertDefaultPointColor(Vector4 color)
{
	ClampPointColor(color);
	return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3 &>(color), color.W);
}

void PointGroupClass::rva00913AF0(int vnum, bool no_diffuse)
{
	Matrix4 world, view;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Matrix4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);
	DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	DX8Wrapper::Set_Material(PointMaterial);
	DX8Wrapper::Set_Shader(Shader);
	BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(Texture));
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
		&& (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE)
		&& WW3D::Is_Sorting_Enabled() && Rva012D6D75;
	IndexBufferClass *indexbuffer;
	int verticesperprimitive;
	if (PointMode == QUADS) {
		verticesperprimitive = 2;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingQuads)
			: static_cast<IndexBufferClass *>(Quads);
	} else {
		verticesperprimitive = 3;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingTris)
			: static_cast<IndexBufferClass *>(Tris);
	}
	unsigned default_color = ConvertDefaultPointColor(Vector4(
		DefaultPointColor.X, DefaultPointColor.Y, DefaultPointColor.Z, DefaultPointAlpha));
	int current = 0;
	while (current < vnum) {
		int delta = MIN(vnum - current, 2048);
		BoxDynamicVBAccessClass PointVerts(
			sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8, 5, delta, 0);
		{
			BoxDynamicVBAccessClass::WriteLockClass Lock(&PointVerts);
			unsigned char *vb = (unsigned char *)Lock.Get_Formatted_Vertex_Array();
			const FVFInfoClass &fvfinfo = PointVerts.FVF_Info();
			unsigned stride = fvfinfo.Get_FVF_Size();
			unsigned char *position = vb + fvfinfo.Get_Location_Offset();
			unsigned char *uv = vb + fvfinfo.Get_Tex_Offset(0);
			unsigned char *color = vb + fvfinfo.Get_Diffuse_Offset();
			if (no_diffuse) {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = default_color;
					position += stride;
					uv += stride;
					color += stride;
				}
			} else {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = ConvertPointColor(VertexDiffuse[i]);
					position += stride;
					uv += stride;
					color += stride;
				}
			}
		}
		DX8Wrapper::Set_Index_Buffer(indexbuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&PointVerts));
		if (sort) {
			InsertPointTriangles(0, delta / verticesperprimitive, 0, delta);
		} else {
			DX8Wrapper::Draw_Triangles(0, delta / verticesperprimitive, 0, delta);
		}
		current += delta;
	}
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, world);
}
