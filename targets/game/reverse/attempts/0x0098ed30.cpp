// ?Render@LineGroupClass@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.9914634146341463 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4; neutralize the old name in this TU.
#define Matrix4x4 Matrix4
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Linegroup.cpp                                                *
 *                                                                                             *
 *                     $Archive::                                                             $*
 *                                                                                             *
 *              Original Author:: Hector Yee                                                   *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 2                                                            $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "sharebuf.h"
#include "linegrp.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8wrapper.h"
#include "wwmath.h"
class CameraClass;
#include "rinfo.h"
#include "camera.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
// The retail five-argument sorting callee receives a 12-byte center,
// independently witnessed by the 0x009037D0 wrapper and its accesses at
// 0x0093B340. This local ABI view avoids the legacy SphereClass declaration.

// Line groups are a rendering primitive similar to point groups
// They are tetrahedra which are aligned with the view plane with their centers
// at StartLineLoc. The apex of the tetrahedron is at EndLineLoc.
// They can be individually colored LineDiffuse
// and the LineUCoord determines the U coordinate of the texture to use
// the V coordinate is always 0 at the flat end of the tetrahedron
// and 1 at the apex
class BoxDynamicVBAccessClass
{
	const FVFInfoClass & FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass * VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned buffer);
	~BoxDynamicVBAccessClass();

	const FVFInfoClass & FVF_Info() const { return FVFInfo; }

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

extern void BoxSetTexture(unsigned stage,TextureBaseClass *& texture);

struct Rva0093B340Center
{
 float X, Y, Z;
 Rva0093B340Center() : X(0.0f), Y(0.0f), Z(0.0f) {}
};
extern void rva0093B340(const Rva0093B340Center &, unsigned short, unsigned short, unsigned short, unsigned short);
static __forceinline void InsertLineGroupTriangles(unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
 Rva0093B340Center center;
 rva0093B340(center,a,b,c,d);
}

static __forceinline void TransformLineOffset(const Matrix3D & A,const Vector3 & in,Vector3 * out)
{
	Vector3 tmp;
	Vector3 * v;

	// check for aliased parameters
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;		// whats the right way to do this...
	}

	out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
	out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
	float product = A[2][2] * v->Z; out->Z = product + A[2][0] * v->X + A[2][1] * v->Y + A[2][3];
}


void	LineGroupClass::Render(RenderInfoClass &rinfo)
{
	int i;

	// If no lines, do nothing:
	if (LineCount == 0) return;

	// Shader handling
	Shader.Set_Cull_Mode(ShaderClass::CULL_MODE_ENABLE);

	// If there is a color or alpha array enable gradient in shader - otherwise disable.
   float value_255 = 0.9961f;	//254 / 255
	bool default_white_opaque = (	DefaultLineColor.X > value_255 &&
											DefaultLineColor.Y > value_255 &&
											DefaultLineColor.Z > value_255 &&
											DefaultLineAlpha > value_255);

	if (LineDiffuse || !default_white_opaque || !Texture) {
		Shader.Set_Primary_Gradient(static_cast<ShaderClass::PriGradientType>(6));
	} else {
		Shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
	}

	// If Texture is non-NULL enable texturing in shader - otherwise disable.
	if (Texture) {
		Shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
	} else {
		Shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
	}

	VertexMaterialClass * linemat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(linemat);
	DX8Wrapper::Set_Shader(Shader);
	BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(Texture));
	REF_PTR_RELEASE(linemat);

	WWASSERT(StartLineLoc && StartLineLoc->Get_Array());
	WWASSERT(EndLineLoc && EndLineLoc->Get_Array());

	// Enable sorting if the primitives are translucent and alpha testing is not enabled.
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) && (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) && (WW3D::Is_Sorting_Enabled());

	// the 3 offsets in view space
	const static Vector3 offset_a = Vector3(WWMath::Cos(WWMATH_PI / 2),			WWMath::Sin(WWMATH_PI /2 ), 0);
	const static Vector3 offset_b = Vector3(WWMath::Cos(7 * WWMATH_PI / 6),		WWMath::Sin(7 * WWMATH_PI / 6), 0);
	const static Vector3 offset_c = Vector3(WWMath::Cos(11 * WWMATH_PI / 6),	WWMath::Sin(11 * WWMATH_PI / 6), 0);

	static Vector3 offset[3];
	
	offset[0].Set(offset_a);
	offset[1].Set(offset_b);
	offset[2].Set(offset_c);

	// Save off the view matrix
	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);	

	// if the points are in world space, transform the offsets
	if (Flags & (1 << TRANSFORM)) {
		Matrix3D xform_mat;
		xform_mat = rinfo.Camera.Get_Transform();
		xform_mat.Set_Translation(Vector3(0, 0, 0));
		xform_mat.Get_Orthogonal_Inverse(xform_mat);
		for (i = 0; i < 3; i++) {
			TransformLineOffset(xform_mat, offset[i], &offset[i]);
		}
	} else {
		DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	}
	
	int num_tris=0;
	int num_indices=0;
	int num_vertices=0;

	switch (LineMode)	{
		case TETRAHEDRON:
			num_tris			=4 * LineCount;
			num_indices		=3 * num_tris;
			num_vertices	=4 * LineCount;
			break;
		case PRISM:
			num_tris			=8 * LineCount;
			num_indices		=3 * num_tris;
			num_vertices	=6 * LineCount;
			break;
	}	

	// construct the tetrahedra in the index buffers
	// assume first vertex is the apex, followed by offset[0-3]	

	DynamicIBAccessClass iba(sort?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,num_indices);

	{
		DynamicIBAccessClass::WriteLockClass lock(&iba);
		unsigned short *ibptr = lock.Get_Index_Array();
		unsigned short j, idx;
		{
		switch (LineMode)	{
			case TETRAHEDRON:
				for (j=0; j<LineCount; j++) {
					idx = 4 * j;
					// apex, offset[1], offset[0]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 2;
					*ibptr++	= idx + 1;			
					// apex, offset[2], offset[1]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 3;
					*ibptr++	= idx + 2;
					// apex, offset[0], offset[2]
					*ibptr++	= idx + 0;
					*ibptr++	= idx + 1;
					*ibptr++	= idx + 3;
					// offset[0-3]
					*ibptr++	= idx + 1;
					*ibptr++	= idx + 2;
					*ibptr++	= idx + 3;
				}
				break;
			case PRISM:
				for (j=0; j<LineCount; j++) {
					idx = 6 * j;
					// starting cap 0,1,2
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 2;
					// left side
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 4;
					// bottom side
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 4;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 1;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 2;
					// right side
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 2;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 0;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 3;
					// end cap
					*ibptr++ = idx + 3;
					*ibptr++ = idx + 5;
					*ibptr++ = idx + 4;
				}			
				break;
		}

		}
	}	// writing to ib

	// make the vertex buffers	

	BoxDynamicVBAccessClass vba(sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8,5,num_vertices,0);

	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&vba);

		VertexFormatXYZNDUV2 *vb = lock.Get_Formatted_Vertex_Array();

		Vector3 loc, start, end;
		int point, j;
		float size = DefaultLineSize;
		Vector4 diffuse(DefaultLineColor.X, DefaultLineColor.Y, DefaultLineColor.Z, DefaultLineAlpha);		
		float ucoord = DefaultLineUCoord;
		Vector4 taildiffuse = DefaultTailDiffuse;

		for (i = 0; i < LineCount; i++)
		{
			point = (ALT) ? ALT->Get_Element(i) : i;
			if (LineSize)		size			= LineSize->Get_Element(point);
			if (LineDiffuse)	diffuse		= LineDiffuse->Get_Element(point);
			if (LineUCoord)	ucoord		= LineUCoord->Get_Element(point);
			if (TailDiffuse)	taildiffuse	= TailDiffuse->Get_Element(point);

			end.Set(EndLineLoc->Get_Element(point));
			start.Set(StartLineLoc->Get_Element(point));

			switch (LineMode) {
				case TETRAHEDRON:
					// apex
					vb->x			= end.X;
					vb->y			= end.Y;
					vb->z			= end.Z;
					vb->diffuse	= DX8Wrapper::Convert_Color(taildiffuse);
					vb->u1		= ucoord;
					vb->v1		= 1.0f;
					vb++;

					for (j=0; j<3; j++) {
						loc.Set(start + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(diffuse);
						vb->u1		= ucoord;
						vb->v1		= 0.0f;
						vb++;				
					}
					break;
			case PRISM:
					// start cap
					for (j = 0; j < 3; j++) {
						loc.Set(start + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(diffuse);
						vb->u1		= ucoord;
						vb->v1		= 0.0f;
						vb++;				
					}
					// Do not merge loops. The vb has to be written in a specific order
					// (This is to optimize AGP memory write)

					// end cap 
					for (j=0; j<3; j++) {
						loc.Set(end + size * offset[j]);
						vb->x			= loc.X;
						vb->y			= loc.Y;
						vb->z			= loc.Z;
						vb->diffuse	= DX8Wrapper::Convert_Color(taildiffuse);
						vb->u1		= ucoord;
						vb->v1		= 1.0f;
						vb++;				
					}
					break;
			}

		}
	} // writing to vb

	DX8Wrapper::Set_Index_Buffer(iba, 0);
	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vba));
	
	if (sort) {
		InsertLineGroupTriangles(0, num_tris, 0, num_vertices);
	} else {
		DX8Wrapper::Draw_Triangles(0, num_tris, 0, num_vertices);
	}		
	
	// restore the matrices
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
}
