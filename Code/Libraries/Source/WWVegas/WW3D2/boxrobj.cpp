// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?Set_Shader@DX8Wrapper@@SAXABVShaderClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp
// readable body of ?Set_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@ABVMatrix3D@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
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
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/boxrobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/19/02 12:57p                                              $*
 *                                                                                             *
 *                    $Revision:: 35                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   BoxRenderObjClass::BoxRenderObjClass -- Constructor                                       *
 *   BoxRenderObjClass::BoxRenderObjClass -- Constructor - init from a definition              *
 *   BoxRenderObjClass::BoxRenderObjClass -- Copy constructor                                  *
 *   BoxRenderObjClass::operator -- assignment operator                                        *
 *   BoxRenderObjClass::Get_Num_Polys -- returns number of polygons                            *
 *   BoxRenderObjClass::Get_Name -- returns name                                               *
 *   BoxRenderObjClass::Set_Name -- sets the name                                              *
 *   BoxRenderObjClass::Set_Color -- Sets the color of the box                                 *
 *   BoxRenderObjClass::Init_Box_Render_System -- global initialization needed for boxes to wo *
 *   BoxRenderObjClass::Shutdown_Box_Render_System -- cleanup box render system                *
 *   BoxRenderObjClass::Set_Box_Display_Mask -- Sets global display mask for all boxes         *
 *   BoxRenderObjClass::Get_Box_Display_Mask -- returns the display mask                       *
 *   BoxRenderObjClass::render_box -- submits the box to the GERD                              *
 *   BoxRenderObjClass::vis_render_box -- submits box to the GERD for VIS                      *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- constructor                                   *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- Constructor - init from a definition          *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- copy constructor                              *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- Constructor from a wwmath aabox               *
 *   AABoxRenderObjClass::operator -- assignment operator                                      *
 *   AABoxRenderObjClass::Clone -- clones the box                                              *
 *   AABoxRenderObjClass::Class_ID -- returns the class-id for AABox's                         *
 *   AABoxRenderObjClass::Render -- render this box                                            *
 *   AABoxRenderObjClass::Special_Render -- special render this box (vis)                      *
 *   AABoxRenderObjClass::Set_Transform -- set the transform for this box                      *
 *   AABoxRenderObjClass::Set_Position -- Set the position of this box                         *
 *   AABoxRenderObjClass::update_cached_box -- update the world-space version of this box      *
 *   AABoxRenderObjClass::Cast_Ray -- cast a ray against this box                              *
 *   AABoxRenderObjClass::Cast_AABox -- cast an AABox against this box                         *
 *   AABoxRenderObjClass::Cast_OBBox -- cast an OBBox against this box                         *
 *   AABoxRenderObjClass::Intersect_AABox -- intersect this box with an AABox                  *
 *   AABoxRenderObjClass::Intersect_OBBox -- Intersect this box with an OBBox                  *
 *   AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sp *
 *   AABoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box     *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor                                   *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor - initiallize from a definition   *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- copy constructor                              *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- constructor - initialize from a wwmath obbox  *
 *   OBBoxRenderObjClass::operator -- assignment operator                                      *
 *   OBBoxRenderObjClass::Clone -- clone this obbox                                            *
 *   OBBoxRenderObjClass::Class_ID -- returns the class ID of OBBoxRenderObjClass              *
 *   OBBoxRenderObjClass::Render -- render this obbox                                          *
 *   OBBoxRenderObjClass::Special_Render -- special render (vis)                               *
 *   OBBoxRenderObjClass::Set_Transform -- set the transform for this box                      *
 *   OBBoxRenderObjClass::Set_Position -- set the position of this box                         *
 *   OBBoxRenderObjClass::update_cached_box -- update the cached world-space box               *
 *   OBBoxRenderObjClass::Cast_Ray -- cast a ray against this box                              *
 *   OBBoxRenderObjClass::Cast_AABox -- cast a swept aabox against this box                    *
 *   OBBoxRenderObjClass::Cast_OBBox -- cast a swept obbox against this bo                     *
 *   OBBoxRenderObjClass::Intersect_AABox -- test this box for intersection with an AAbox      *
 *   OBBoxRenderObjClass::Intersect_OBBox -- test this box for intersection with an OBBox      *
 *   OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the obj-space bounding spher *
 *   OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box     *
 *   OBBoxRenderObjClass::Get_Box -- returns the cached world-space box                        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "boxrobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"
#include "sortingrenderer.h"
#include "visrasterizer.h"
#include "meshgeometry.h"

extern void W3DRadarResetLock(void);
extern void BFME_DX8_Thread_Assert(void);
extern void _bfme_debugRecordCallsite(int kind);

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;

static __forceinline void BFME_DX8_ErrorCode(unsigned result)
{
	if (result != D3D_OK) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream(NULL, NULL);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}


#define NUM_BOX_VERTS	8
#define NUM_BOX_FACES	12

// Face Connectivity
static TriIndex					_BoxFaces[NUM_BOX_FACES] = 
{
	TriIndex( 0,1,2 ),		// +z faces
	TriIndex( 0,2,3 ),		
	TriIndex( 4,7,6 ),		// -z faces
	TriIndex( 4,6,5 ),
	TriIndex( 0,3,7 ),		// +x faces
	TriIndex( 0,7,4 ),
	TriIndex( 1,5,6 ),		// -x faces
	TriIndex( 1,6,2 ),
	TriIndex( 4,5,1 ),		// +y faces
	TriIndex( 4,1,0 ),
	TriIndex( 3,2,6 ),		// -y faces
	TriIndex( 3,6,7 )
};

// Vertex Positions as a function of the box extents
static Vector3						_BoxVerts[NUM_BOX_VERTS] = 
{
	Vector3(  1.0f, 1.0f, 1.0f ),		// +z ring of 4 verts
	Vector3( -1.0f, 1.0f, 1.0f ),
	Vector3( -1.0f,-1.0f, 1.0f ),
	Vector3(  1.0f,-1.0f, 1.0f ),

	Vector3(  1.0f, 1.0f,-1.0f ),		// -z ring of 4 verts;
	Vector3( -1.0f, 1.0f,-1.0f ),
	Vector3( -1.0f,-1.0f,-1.0f ),
	Vector3(  1.0f,-1.0f,-1.0f ),
};

// Vertex Normals
static Vector3						_BoxVertexNormals[NUM_BOX_VERTS] =
{
	Vector3( WWMATH_OOSQRT3, WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3, WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3,-WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3( WWMATH_OOSQRT3,-WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),

	Vector3( WWMATH_OOSQRT3, WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3, WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3,-WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3( WWMATH_OOSQRT3,-WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
};



bool										BoxRenderObjClass::IsInitted			= false;
int										BoxRenderObjClass::DisplayMask		= 0;
static VertexMaterialClass *		_BoxMaterial								= NULL;
static ShaderClass					_BoxShader;


/*
** BoxRenderObjClass Implementation
*/

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

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		__declspec(noinline) WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		__declspec(noinline) ~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

// BFME's vertex-buffer base carries an extra field at +0x18 that Zero Hour
// removed, so the derived API buffer lives at +0x1C in the retail ABI.
class BoxVertexBufferClass
{
protected:
	unsigned Fields[5];
	FVFInfoClass * FVFInfo;
	unsigned BfmeField18;

public:
	const FVFInfoClass & FVF_Info() const { return *FVFInfo; }
};

class BoxSortingVertexBufferClass : public BoxVertexBufferClass
{
	VertexFormatXYZNDUV2 * VertexBuffer;

public:
	VertexFormatXYZNDUV2 * Get_Vertex_Buffer() const { return VertexBuffer; }
};

class BoxDX8VertexBufferClass : public BoxVertexBufferClass
{
	IDirect3DVertexBuffer8 * VertexBuffer;

public:
	IDirect3DVertexBuffer8 * Get_DX8_Vertex_Buffer() const { return VertexBuffer; }
};

BoxDynamicVBAccessClass::WriteLockClass::WriteLockClass(BoxDynamicVBAccessClass * dynamic_vb_access)
	: DynamicVBAccess(dynamic_vb_access)
{
	W3DRadarResetLock();
	switch (DynamicVBAccess->Type) {
	case BUFFER_TYPE_DYNAMIC_DX8:
	{
		DX8_Assert();
		// BFME fetches the ABI buffer before the count; preserve that observable load order.
		BoxVertexBufferClass * volatile *vertex_buffer_slot = &DynamicVBAccess->VertexBuffer;
		BoxDX8VertexBufferClass *vertex_buffer = static_cast<BoxDX8VertexBufferClass *>(*vertex_buffer_slot);
		unsigned short vertex_count = DynamicVBAccess->VertexCount;
		BFME_DX8_ErrorCode(vertex_buffer->Get_DX8_Vertex_Buffer()->Lock(
			DynamicVBAccess->VertexBufferOffset * DynamicVBAccess->VertexBuffer->FVF_Info().Get_FVF_Size(),
			vertex_count * DynamicVBAccess->VertexBuffer->FVF_Info().Get_FVF_Size(),
			(unsigned char **)&Vertices,
			D3DLOCK_NOSYSLOCK | (!DynamicVBAccess->VertexBufferOffset ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE)));
		break;
	}
	case BUFFER_TYPE_DYNAMIC_SORTING:
		Vertices = static_cast<BoxSortingVertexBufferClass *>(DynamicVBAccess->VertexBuffer)->Get_Vertex_Buffer();
		Vertices += DynamicVBAccess->VertexBufferOffset;
		break;
	}
}

BoxDynamicVBAccessClass::WriteLockClass::~WriteLockClass()
{
	DX8_THREAD_ASSERT();
	switch (DynamicVBAccess->Type) {
	case BUFFER_TYPE_DYNAMIC_DX8:
		DX8_Assert();
		BFME_DX8_ErrorCode(static_cast<BoxDX8VertexBufferClass *>(DynamicVBAccess->VertexBuffer)->Get_DX8_Vertex_Buffer()->Unlock());
		break;
	case BUFFER_TYPE_DYNAMIC_SORTING:
		break;
	}
	BFME_DX8_Thread_Assert();
}

void BoxSetTexture(unsigned stage,TextureBaseClass *& texture);

class BoxTextureRef
{
	TextureBaseClass *Texture;

public:
	BoxTextureRef() : Texture(NULL) {}
	~BoxTextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return Texture; }
};


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Constructor                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/BoxRenderObjClassConstructorThunk.cpp
// ??0BoxRenderObjClass@@ present-unmatched
BoxRenderObjClass::BoxRenderObjClass(void)
{
	memset(Name,0,sizeof(Name));
	Color.Set(1,1,1);
	Opacity = 0.25f;
	ObjSpaceCenter.Set(0,0,0);
	ObjSpaceExtent.Set(1,1,1);
}


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Constructor - init from a definition                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/BoxRenderObjClassConstructorThunk.cpp
// ??0BoxRenderObjClass@@ present-unmatched
BoxRenderObjClass::BoxRenderObjClass(const W3dBoxStruct & def)
{
	Set_Name(def.Name);
	W3dUtilityClass::Convert_Color(def.Color,&Color);
	W3dUtilityClass::Convert_Vector(def.Center,&ObjSpaceCenter);
	W3dUtilityClass::Convert_Vector(def.Extent,&ObjSpaceExtent);
	int col_bits = (def.Attributes & W3D_BOX_ATTRIBUTE_COLLISION_TYPE_MASK) >> W3D_BOX_ATTRIBUTE_COLLISION_TYPE_SHIFT;
	Set_Collision_Type(col_bits<<1);
	Opacity = 0.25f;
}


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Copy constructor                                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/BoxRenderObjClassConstructorThunk.cpp
// ??0BoxRenderObjClass@@ present-unmatched
BoxRenderObjClass::BoxRenderObjClass(const BoxRenderObjClass & src)
{
	*this = src;
}


/***********************************************************************************************
 * BoxRenderObjClass::operator -- assignment operator                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
BoxRenderObjClass & BoxRenderObjClass::operator = (const BoxRenderObjClass & that)
{
	if (this != &that) {
		RenderObjClass::operator = (that);
		Set_Name(that.Get_Name());
		Color.Set(that.Color);
		ObjSpaceCenter.Set(that.ObjSpaceCenter);
		ObjSpaceExtent.Set(that.ObjSpaceExtent);
	}
	return *this;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Num_Polys -- returns number of polygons                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Get_Num_Polys@BoxRenderObjClass@@UBEHXZ present-unmatched
int BoxRenderObjClass::Get_Num_Polys(void) const
{
	return 12;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Name -- returns name                                                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Get_Name@BoxRenderObjClass@@UBEPBDXZ present-unmatched
const char * BoxRenderObjClass::Get_Name(void) const
{
	return Name;
}


/***********************************************************************************************
 * BoxRenderObjClass::Set_Name -- sets the name                                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void BoxRenderObjClass::Set_Name(const char * name)
{
	WWASSERT(name != NULL);
	WWASSERT(strlen(name) < 2*W3D_NAME_LEN);
	strcpy(Name,name);
}


/***********************************************************************************************
 * BoxRenderObjClass::Set_Color -- Sets the color of the box                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void BoxRenderObjClass::Set_Color(const Vector3 & color)
{
	Color = color;
}


/***********************************************************************************************
 * BoxRenderObjClass::Init_Box_Render_System -- global initialization needed for boxes to work *
 *                                                                                             *
 * Allocates materials which all boxes share.  Initializes vertex tables, etc                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Init@BoxRenderObjClass@@SAXXZ present-unmatched
void BoxRenderObjClass::Init(void)
{
	WWASSERT(IsInitted == false);

	/*
	** Set up the materials
	*/
	WWASSERT(_BoxMaterial == NULL);
	_BoxMaterial = NEW_REF(VertexMaterialClass,());
	_BoxMaterial->Set_Ambient(0,0,0);
	_BoxMaterial->Set_Diffuse(0,0,0);
	_BoxMaterial->Set_Specular(0,0,0);
	_BoxMaterial->Set_Emissive(1,1,1);
	_BoxMaterial->Set_Opacity(1.0f);		// uses vertex alpha...
	_BoxMaterial->Set_Shininess(0.0f);

	_BoxShader = ShaderClass::_PresetAlphaSolidShader; //_PresetAdditiveSolidShader;

	IsInitted = true;
}


/***********************************************************************************************
 * BoxRenderObjClass::Shutdown -- cleanup box render system                                    *
 *                                                                                             *
 * Releases resources allocated in Init                                                        *
 * NOTE: this is a static function that should only be called by the system                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Shutdown@BoxRenderObjClass@@SAXXZ present-unmatched
void BoxRenderObjClass::Shutdown(void)
{
	WWASSERT(IsInitted == true);
	REF_PTR_RELEASE(_BoxMaterial);
	
	IsInitted = false;
}


/***********************************************************************************************
 * BoxRenderObjClass::Set_Box_Display_Mask -- Sets global display mask for all boxes           *
 *                                                                                             *
 * Boxes are debug objects and usually used for collision.  This mask is 'AND'ed with each     *
 * box's collision type to determine whether the box should be rendered.                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Set_Box_Display_Mask@BoxRenderObjClass@@SAXH@Z present-unmatched
void BoxRenderObjClass::Set_Box_Display_Mask(int mask)
{
	DisplayMask = mask;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Box_Display_Mask -- returns the display mask                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Get_Box_Display_Mask@BoxRenderObjClass@@SAHXZ present-unmatched
int BoxRenderObjClass::Get_Box_Display_Mask(void)
{
	return DisplayMask;
}


/***********************************************************************************************
 * BoxRenderObjClass::render_box -- submits the box to the GERD                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void BoxRenderObjClass::render_box(RenderInfoClass & rinfo,const Vector3 & center,const Vector3 & extent)
{
	if (!IsInitted) return;
	if (DisplayMask & Get_Collision_Type()) {

		static Vector3 verts[NUM_BOX_VERTS];

		// compute the vertex positions
		for (int ivert=0; ivert<NUM_BOX_VERTS; ivert++) {
			verts[ivert].X = center.X + _BoxVerts[ivert][0] * extent.X;
			verts[ivert].Y = center.Y + _BoxVerts[ivert][1] * extent.Y;
			verts[ivert].Z = center.Z + _BoxVerts[ivert][2] * extent.Z;
		}

		/*
		** Dump the box vertices into the sorting dynamic vertex buffer. 
		*/
		DWORD color = DX8Wrapper::Convert_Color(Color,Opacity);
		
		int buffer_type = BUFFER_TYPE_DYNAMIC_DX8;

		BoxDynamicVBAccessClass vbaccess(buffer_type,5,NUM_BOX_VERTS,0);
		{
			BoxDynamicVBAccessClass::WriteLockClass lock(&vbaccess);
			//unsigned char *vb=(unsigned char *) lock.Get_Vertex_Array();
			VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

			for (int i=0; i<NUM_BOX_VERTS; i++) {

				// Locations
				vb->x=verts[i][0];
				vb->y=verts[i][1];
				vb->z=verts[i][2];
				
				// Normals
				vb->nx=_BoxVertexNormals[i][0];
				vb->ny=_BoxVertexNormals[i][1];
				vb->nz=_BoxVertexNormals[i][2];

				// Colors
				vb->diffuse=color;

				vb++;
			}
		}

		/*
		** Dump the faces into the sorting dynamic index buffer.
		*/
		DynamicIBAccessClass ibaccess(buffer_type,NUM_BOX_FACES*3);
		{
			DynamicIBAccessClass::WriteLockClass lock(&ibaccess);
			unsigned short * indices = lock.Get_Index_Array();
			for (int i=0; i<NUM_BOX_FACES; i++) {
				indices[3*i] = _BoxFaces[i][0];
				indices[3*i+1] = _BoxFaces[i][1];
				indices[3*i+2] = _BoxFaces[i][2];
			}
		}

		/*
		** Apply the shader and material
		*/
		DX8Wrapper::Set_Material(_BoxMaterial);
		DX8Wrapper::Set_Shader(_BoxShader);
		{
			BoxTextureRef texture;
			BoxSetTexture(0,texture);
		}
		
		DX8Wrapper::Set_Index_Buffer(ibaccess,0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vbaccess));

		SphereClass sphere;
		Get_Obj_Space_Bounding_Sphere(sphere); 

		DX8Wrapper::Draw_Triangles(buffer_type,0,NUM_BOX_FACES,0,NUM_BOX_VERTS);
	}
}


/***********************************************************************************************
 * BoxRenderObjClass::vis_render_box -- submits box to the GERD for VIS                        *
 *                                                                                             *
 * this renders the box with the specified VIS-ID.                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// Body in boxrobj_vis_render_box.asm (exact 590B retail): ?vis_render_box@BoxRenderObjClass@@IAEXAAVSpecialRenderInfoClass@@ABVVector3@@1@Z
// (one line, and prose-first: a `// ?` line binds to the NEXT definition, and
// this one documents a body in another file, not the ctor below.)

/*
** AABoxRenderObjClass Implementation
*/

/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- constructor                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
AABoxRenderObjClass::AABoxRenderObjClass(void)
{
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- Constructor - init from a definition            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/AABoxRenderObjClassCtorThunk.cpp
// ??0AABoxRenderObjClass@@ present-unmatched
AABoxRenderObjClass::AABoxRenderObjClass(const W3dBoxStruct & def) :
	BoxRenderObjClass(def)
{
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- copy constructor                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/AABoxRenderObjClassCtorThunk.cpp
// ??0AABoxRenderObjClass@@ present-unmatched
AABoxRenderObjClass::AABoxRenderObjClass(const AABoxRenderObjClass & src)
{
	*this = src;
}


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- Constructor from a wwmath aabox                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/AABoxRenderObjClassCtorThunk.cpp
// ??0AABoxRenderObjClass@@ present-unmatched
// Implemented in AABoxRenderObjClassCtorThunk.cpp because the real class's
// base subobjects make MSVC prepend constructor initialization to a naked body.


/***********************************************************************************************
 * AABoxRenderObjClass::operator -- assignment operator                                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
AABoxRenderObjClass & AABoxRenderObjClass::operator = (const AABoxRenderObjClass & that)
{
	if (this != &that) {
		BoxRenderObjClass::operator = (that);
		CachedBox = that.CachedBox;
	}
	return *this;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Clone -- clones the box                                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
RenderObjClass * AABoxRenderObjClass::Clone(void) const
{
	return ::new AABoxRenderObjClass(*this);
}


/***********************************************************************************************
 * AABoxRenderObjClass::Class_ID -- returns the class-id for AABox's                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWSaveLoad/parameter.cpp
// ?Class_ID@AABoxRenderObjClass@@UBEHXZ present-unmatched
int AABoxRenderObjClass::Class_ID(void) const
{
	return RenderObjClass::CLASSID_AABOX;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Render -- render this box                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Render@AABoxRenderObjClass@@UAEXAAVRenderInfoClass@@@Z present-unmatched
void AABoxRenderObjClass::Render(RenderInfoClass & rinfo)
{
	Matrix3D temp(1);
	temp.Translate(Transform.Get_Translation());
	DX8Wrapper::Set_Transform(D3DTS_WORLD,temp);
	render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * AABoxRenderObjClass::Special_Render -- special render this box (vis)                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Special_Render@AABoxRenderObjClass@@UAEXAAVSpecialRenderInfoClass@@@Z present-unmatched
void AABoxRenderObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	if (rinfo.RenderType == SpecialRenderInfoClass::RENDER_VIS) {
		WWASSERT(rinfo.VisRasterizer != NULL);
		Matrix3D temp(1);
		temp.Translate(Transform.Get_Translation());
		rinfo.VisRasterizer->Set_Model_Transform(temp);
		vis_render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
	}
}


/***********************************************************************************************
 * AABoxRenderObjClass::Set_Transform -- set the transform for this box                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Set_Transform@AABoxRenderObjClass@@UAEXABVMatrix3D@@@Z present-unmatched
void AABoxRenderObjClass::Set_Transform(const Matrix3D &m)
{
	RenderObjClass::Set_Transform(m);
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::Set_Position -- Set the position of this box                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
class RetailAABoxRenderObjBase
{
public:
	void Set_Position_Retail(const Vector3 &position);
};

// ?Set_Position@AABoxRenderObjClass@@UAEXABVVector3@@@Z matched 27 bytes (Open-BFME5)
void AABoxRenderObjClass::Set_Position(const Vector3 &v)
{
	reinterpret_cast<RetailAABoxRenderObjBase *>(this)->Set_Position_Retail(v);
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::update_cached_box -- update the world-space version of this box        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void AABoxRenderObjClass::update_cached_box(void)
{
	CachedBox.Center = Transform.Get_Translation() + ObjSpaceCenter;
	CachedBox.Extent = ObjSpaceExtent;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_Ray -- cast a ray against this box                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool AABoxRenderObjClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	if (Is_Animation_Hidden()) return false;
	if (raytest.Result->StartBad) return false;

	if (CollisionMath::Collide(raytest.Ray,CachedBox,raytest.Result)) {
		raytest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_AABox -- cast an AABox against this box                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Cast_AABox@AABoxRenderObjClass@@UAE_NAAVAABoxCollisionTestClass@@@Z present-unmatched
bool AABoxRenderObjClass::Cast_AABox(AABoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_OBBox -- cast an OBBox against this box                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Cast_OBBox@AABoxRenderObjClass@@UAE_NAAVOBBoxCollisionTestClass@@@Z present-unmatched
bool AABoxRenderObjClass::Cast_OBBox(OBBoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Intersect_AABox -- intersect this box with an AABox                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Intersect_AABox@AABoxRenderObjClass@@UAE_NAAVAABoxIntersectionTestClass@@@Z present-unmatched
bool AABoxRenderObjClass::Intersect_AABox(AABoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);	
}


/***********************************************************************************************
 * AABoxRenderObjClass::Intersect_OBBox -- Intersect this box with an OBBox                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Intersect_OBBox@AABoxRenderObjClass@@UAE_NAAVOBBoxIntersectionTestClass@@@Z present-unmatched
bool AABoxRenderObjClass::Intersect_OBBox(OBBoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);
}


/***********************************************************************************************
 * AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sphe *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Init(ObjSpaceCenter,ObjSpaceExtent.Length());
}


/***********************************************************************************************
 * AABoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void AABoxRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Init(ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
OBBoxRenderObjClass::OBBoxRenderObjClass(void)
{
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor - initiallize from a definition     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
OBBoxRenderObjClass::OBBoxRenderObjClass(const W3dBoxStruct & def) :
	BoxRenderObjClass(def)
{
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- copy constructor                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ??0OBBoxRenderObjClass@@ present-unmatched
OBBoxRenderObjClass::OBBoxRenderObjClass(const OBBoxRenderObjClass & that)
{
	*this = that;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- constructor - initialize from a wwmath obbox    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ??0OBBoxRenderObjClass@@ present-unmatched
OBBoxRenderObjClass::OBBoxRenderObjClass(const OBBoxClass & box)
{
	ObjSpaceCenter.Set(Vector3(0,0,0));
	ObjSpaceExtent.Set(box.Extent);
	Set_Transform(Matrix3D(box.Basis,box.Center));
	update_cached_box(); // cached box should == box!
}


/***********************************************************************************************
 * OBBoxRenderObjClass::operator -- assignment operator                                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
OBBoxRenderObjClass & OBBoxRenderObjClass::operator = (const OBBoxRenderObjClass & that)
{
	if (this != &that) {
		BoxRenderObjClass::operator = (that);
		CachedBox = that.CachedBox;
	}
	return *this;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Clone -- clone this obbox                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Clone@OBBoxRenderObjClass@@UBEPAVRenderObjClass@@XZ present-unmatched
RenderObjClass * OBBoxRenderObjClass::Clone(void) const
{
	return W3DNEW OBBoxRenderObjClass(*this);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Class_ID -- returns the class ID of OBBoxRenderObjClass                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWSaveLoad/parameter.cpp
// ?Class_ID@OBBoxRenderObjClass@@UBEHXZ present-unmatched
int OBBoxRenderObjClass::Class_ID(void) const
{
	return RenderObjClass::CLASSID_OBBOX;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Render -- render this obbox                                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void OBBoxRenderObjClass::Render(RenderInfoClass & rinfo)
{
	DX8Wrapper::Set_Transform(D3DTS_WORLD,Transform);
	render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Special_Render -- special render (vis)                                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Special_Render@OBBoxRenderObjClass@@UAEXAAVSpecialRenderInfoClass@@@Z present-unmatched
void OBBoxRenderObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	if (rinfo.RenderType == SpecialRenderInfoClass::RENDER_VIS) {
		WWASSERT(rinfo.VisRasterizer != NULL);
		rinfo.VisRasterizer->Set_Model_Transform(Transform);
		vis_render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
	}
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Set_Transform -- set the transform for this box                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Set_Transform@OBBoxRenderObjClass@@UAEXABVMatrix3D@@@Z present-unmatched
void OBBoxRenderObjClass::Set_Transform(const Matrix3D &m)
{
	RenderObjClass::Set_Transform(m);
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Set_Position -- set the position of this box                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void OBBoxRenderObjClass::Set_Position(const Vector3 &v)
{
	RenderObjClass::Set_Position(v);
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::update_cached_box -- update the cached world-space box                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void OBBoxRenderObjClass::update_cached_box(void)
{
	Matrix3D::Transform_Vector(Transform,ObjSpaceCenter,&CachedBox.Center);
	CachedBox.Extent.Set(ObjSpaceExtent);
	CachedBox.Basis.Set(Transform);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_Ray -- cast a ray against this box                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool OBBoxRenderObjClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	if (Is_Animation_Hidden()) return false;
	if (raytest.Result->StartBad) return false;

	if (CollisionMath::Collide(raytest.Ray,CachedBox,raytest.Result)) {
		raytest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_AABox -- cast a swept aabox against this box                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Cast_AABox@OBBoxRenderObjClass@@UAE_NAAVAABoxCollisionTestClass@@@Z present-unmatched
bool OBBoxRenderObjClass::Cast_AABox(AABoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_OBBox -- cast a swept obbox against this bo                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Cast_OBBox@OBBoxRenderObjClass@@UAE_NAAVOBBoxCollisionTestClass@@@Z present-unmatched
bool OBBoxRenderObjClass::Cast_OBBox(OBBoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Intersect_AABox -- test this box for intersection with an AAbox        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Intersect_AABox@OBBoxRenderObjClass@@UAE_NAAVAABoxIntersectionTestClass@@@Z present-unmatched
bool OBBoxRenderObjClass::Intersect_AABox(AABoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);	
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Intersect_OBBox -- test this box for intersection with an OBBox        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?Intersect_OBBox@OBBoxRenderObjClass@@UAE_NAAVOBBoxIntersectionTestClass@@@Z present-unmatched
bool OBBoxRenderObjClass::Intersect_OBBox(OBBoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the obj-space bounding sphere  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Init(ObjSpaceCenter,ObjSpaceExtent.Length());
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Init(ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Box -- returns the cached world-space box                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
OBBoxClass & OBBoxRenderObjClass::Get_Box(void)
{
	Validate_Transform();
	update_cached_box();
	return CachedBox;
}

/*
** BoxLoaderClass Implementation
*/
// ?Load_W3D@BoxLoaderClass@@UAEPAVPrototypeClass@@AAVChunkLoadClass@@@Z present-unmatched
PrototypeClass * BoxLoaderClass::Load_W3D(ChunkLoadClass & cload)
{
	W3dBoxStruct box;
	cload.Read(&box,sizeof(box));
	return W3DNEW BoxPrototypeClass(box);
}

/*
** BoxPrototypeClass Implementation
*/
// ??0BoxPrototypeClass@@QAE@UW3dBoxStruct@@@Z present-unmatched
BoxPrototypeClass::BoxPrototypeClass(W3dBoxStruct box)
{
	Definition = box;
}

// ?Get_Name@BoxPrototypeClass@@UBEPBDXZ present-unmatched
const char * BoxPrototypeClass::Get_Name(void) const
{
	return Definition.Name;
}

// ?Get_Class_ID@BoxPrototypeClass@@UBEHXZ present-unmatched
int BoxPrototypeClass::Get_Class_ID(void) const
{
	if (Definition.Attributes & W3D_BOX_ATTRIBUTE_ORIENTED) {
		return RenderObjClass::CLASSID_OBBOX;
	} else {
		return RenderObjClass::CLASSID_AABOX;
	}
}
	
// ?Create@BoxPrototypeClass@@UAEPAVRenderObjClass@@XZ present-unmatched
RenderObjClass * BoxPrototypeClass::Create(void)
{
	if (Definition.Attributes & W3D_BOX_ATTRIBUTE_ORIENTED) {
		return NEW_REF( OBBoxRenderObjClass, (Definition) );
	} else {
		return NEW_REF( AABoxRenderObjClass, (Definition) );
	}
}

/*
** Global instance of the box loader
*/
BoxLoaderClass _BoxLoader;
