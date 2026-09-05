// ?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z
// partial score=0.91 date=2026-09-04
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
// RVA 0x00960A30: scratch-free bank; TU-local VB ABI declarations included.
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8_WRAPPER_H
#define DX8_WRAPPER_H
#include "always.h"
#include "dllist.h"
#include "d3d8.h"
#include "matrix4.h"
#include "statistics.h"
#include "wwstring.h"
#include "lightenvironment.h"
#include "shader.h"
#include "vector4.h"
#include "cpudetect.h"
#include "dx8caps.h"
#include "texture.h"
#if defined(_MSC_VER)
#pragma once
#endif
#ifndef DX8VERTEXBUFFER_H
#define DX8VERTEXBUFFER_H
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "dx8fvf.h"
const unsigned dynamic_fvf_type=D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE;
class DX8Wrapper;
class SortingRendererClass;
class Vector2;
class Vector3;
class Vector4;
class StringClass;
class DX8VertexBufferClass;
class FVFInfoClass;
struct IDirect3DVertexBuffer8;
class VertexBufferClass;
struct VertexFormatXYZNDUV2;
class VertexBufferLockClass
{
protected:
VertexBufferClass* VertexBuffer;
void* Vertices;
VertexBufferLockClass(VertexBufferClass* vertex_buffer_) : VertexBuffer(vertex_buffer_) {}
public:
void* Get_Vertex_Array() { return Vertices; }
};
class VertexBufferClass : public W3DMPO, public RefCountClass
{
protected:
VertexBufferClass(unsigned type, unsigned FVF, unsigned short VertexCount, unsigned vertex_size=0);
virtual ~VertexBufferClass() throw();
public:
inline const FVFInfoClass& FVF_Info() const { return *fvf_info; }
inline unsigned short Get_Vertex_Count() const { return VertexCount; }
inline unsigned Type() const { return type; }
void Add_Engine_Ref() const;
void Release_Engine_Ref() const;
inline unsigned Engine_Refs() const { return engine_refs; } 
class WriteLockClass : public VertexBufferLockClass
{
public:
WriteLockClass(VertexBufferClass* vertex_buffer, int flags=0);
__declspec(noinline) ~WriteLockClass();
};
class AppendLockClass : public VertexBufferLockClass
{
public:
AppendLockClass(VertexBufferClass* vertex_buffer,unsigned start_index, unsigned index_range, int flags=0);
__declspec(noinline) ~AppendLockClass();
};
static unsigned Get_Total_Buffer_Count();
static unsigned Get_Total_Allocated_Vertices();
static unsigned Get_Total_Allocated_Memory();
protected:
unsigned							type;
unsigned short					VertexCount;
mutable int						engine_refs;
FVFInfoClass*					fvf_info;
bool								m_BFMEExplicitVertexSize;
unsigned char					m_BFMEPadding[3];
};
class BoxDynamicVBAccessClass
{
friend DX8Wrapper;
friend SortingRendererClass;
const FVFInfoClass& FVFInfo;
unsigned Type;
unsigned FVF;
unsigned Start;
unsigned short VertexCount;
unsigned short VertexBufferOffset;
VertexBufferClass* VertexBuffer;
void Allocate_Sorting_Dynamic_Buffer();
void Allocate_DX8_Dynamic_Buffer();
public:
BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned start);
~BoxDynamicVBAccessClass();
const FVFInfoClass& FVF_Info() const { return FVFInfo; }
unsigned Get_Type() const { return Type; }
unsigned short Get_Vertex_Count() const { return VertexCount; }
static void _Deinit();
static void _Reset(bool frame_changed);
static unsigned short Get_Default_Vertex_Count(void);	
class WriteLockClass
{
BoxDynamicVBAccessClass* DynamicVBAccess;
VertexFormatXYZNDUV2 * Vertices;
public:
WriteLockClass(BoxDynamicVBAccessClass* vb_access);
~WriteLockClass();
VertexFormatXYZNDUV2 * Get_Formatted_Vertex_Array();
};
friend WriteLockClass;
};
inline VertexFormatXYZNDUV2 * BoxDynamicVBAccessClass::WriteLockClass::Get_Formatted_Vertex_Array()
{
WWASSERT(DynamicVBAccess->VertexBuffer->FVF_Info().Get_FVF() == (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE));
return Vertices;
}
class DX8VertexBufferClass : public VertexBufferClass
{
protected:
~DX8VertexBufferClass();
public:
enum UsageType {
USAGE_DEFAULT=0,
USAGE_DYNAMIC=1,
USAGE_SOFTWAREPROCESSING=2,
USAGE_NPATCHES=4
};
DX8VertexBufferClass(unsigned FVF, unsigned short VertexCount, UsageType usage=USAGE_DEFAULT, unsigned vertex_size=0); 
DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector3* normals, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector4* diffuse, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
DX8VertexBufferClass(const Vector3* vertices, const Vector2* tex_coords, unsigned short VertexCount,UsageType usage=USAGE_DEFAULT);
IDirect3DVertexBuffer8* Get_DX8_Vertex_Buffer() { return VertexBuffer; }
void Copy(const Vector3* loc, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector2* uv, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector3* norm, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
void Copy(const Vector3* loc, const Vector2* uv, const Vector4* diffuse, unsigned first_vertex, unsigned count);
protected:
IDirect3DVertexBuffer8*		VertexBuffer;
void Create_Vertex_Buffer(UsageType usage);
};
class SortingVertexBufferClass : public VertexBufferClass
{
friend DX8Wrapper;
friend SortingRendererClass;
friend VertexBufferClass::WriteLockClass;
friend VertexBufferClass::AppendLockClass;
friend BoxDynamicVBAccessClass::WriteLockClass;
VertexFormatXYZNDUV2* VertexBuffer;
protected:
~SortingVertexBufferClass() throw();
public:
SortingVertexBufferClass(unsigned short VertexCount);
};
#endif 
#include "dx8indexbuffer.h"
#include "vertmaterial.h"
#include "dx8fvf.h"	
#define	VALUE_NAME_RENDER_DEVICE_NAME					"RenderDeviceName"
#define	VALUE_NAME_RENDER_DEVICE_WIDTH				"RenderDeviceWidth"
#define	VALUE_NAME_RENDER_DEVICE_HEIGHT				"RenderDeviceHeight"
#define	VALUE_NAME_RENDER_DEVICE_DEPTH				"RenderDeviceDepth"
#define	VALUE_NAME_RENDER_DEVICE_WINDOWED			"RenderDeviceWindowed"
#define	VALUE_NAME_RENDER_DEVICE_TEXTURE_DEPTH		"RenderDeviceTextureDepth"
const unsigned MAX_TEXTURE_STAGES=8;
const unsigned MAX_VERTEX_STREAMS=2;
const unsigned MAX_VERTEX_SHADER_CONSTANTS=96;
const unsigned MAX_PIXEL_SHADER_CONSTANTS=8;
const unsigned MAX_SHADOW_MAPS=1;
#define prevVer
#define nextVer
#define __volatile unsigned
enum {
BUFFER_TYPE_DX8,
BUFFER_TYPE_SORTING,
BUFFER_TYPE_DYNAMIC_DX8,
BUFFER_TYPE_DYNAMIC_SORTING,
BUFFER_TYPE_INVALID
};
class VertexMaterialClass;
class CameraClass;
class LightEnvironmentClass;
class RenderDeviceDescClass;
class VertexBufferClass;
class BoxDynamicVBAccessClass;
class IndexBufferClass;
class DynamicIBAccessClass;
class TextureClass;
class ZTextureClass;
class LightClass;
class SurfaceClass;
class DX8Caps;
#define DX8_RECORD_MATRIX_CHANGE()				matrix_changes++
#define DX8_RECORD_MATERIAL_CHANGE()			material_changes++
#define DX8_RECORD_VERTEX_BUFFER_CHANGE()		vertex_buffer_changes++
#define DX8_RECORD_INDEX_BUFFER_CHANGE()		index_buffer_changes++
#define DX8_RECORD_LIGHT_CHANGE()				light_changes++
#define DX8_RECORD_TEXTURE_CHANGE()				texture_changes++
#define DX8_RECORD_RENDER_STATE_CHANGE()		render_state_changes++
#define DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE() texture_stage_state_changes++
#define DX8_RECORD_DRAW_CALLS()					draw_calls++
extern unsigned number_of_DX8_calls;
extern bool _DX8SingleThreaded;
void DX8_Assert();
void Log_DX8_ErrorCode(unsigned res);
WWINLINE void DX8_ErrorCode(unsigned res)
{
if (res==D3D_OK) return;
Log_DX8_ErrorCode(res);
}
#ifdef WWDEBUG
#define DX8CALL_HRES(x,res) DX8_Assert(); res = DX8Wrapper::_Get_D3D_Device8()->x; DX8_ErrorCode(res); number_of_DX8_calls++;
#define DX8CALL(x) DX8_Assert(); DX8_ErrorCode(DX8Wrapper::_Get_D3D_Device8()->x); number_of_DX8_calls++;
#define DX8CALL_D3D(x) DX8_Assert(); DX8_ErrorCode(DX8Wrapper::_Get_D3D8()->x); number_of_DX8_calls++;
#define DX8_THREAD_ASSERT() if (_DX8SingleThreaded) { WWASSERT_PRINT(DX8Wrapper::_Get_Main_Thread_ID()==ThreadClass::_Get_Current_Thread_ID(),"DX8Wrapper::DX8 calls must be called from the main thread!"); }
#else
#define DX8CALL_HRES(x,res) res = DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;
#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++;
#define DX8CALL_D3D(x) DX8Wrapper::_Get_D3D8()->x; number_of_DX8_calls++;
#define DX8_THREAD_ASSERT() ;
#endif
#define no_EXTENDED_STATS
#ifdef EXTENDED_STATS
class DX8_Stats
{
public:
bool m_showingStats;
bool m_disableTerrain;
bool m_disableWater;
bool m_disableObjects;
bool m_disableOverhead;
bool m_disableConsole;
int  m_debugLinesToShow;
int	 m_sleepTime;
public:
DX8_Stats::DX8_Stats(void) {
m_disableConsole = m_showingStats = m_disableTerrain = m_disableWater = m_disableOverhead = m_disableObjects = false;
m_sleepTime = 0;
m_debugLinesToShow = -1; 
}
};
#endif
class DX8_CleanupHook
{
public:
virtual void ReleaseResources(void)=0;
virtual void ReAcquireResources(void)=0;
};
struct RenderStateStruct
{
ShaderClass shader;
VertexMaterialClass* material;
TextureBaseClass * Textures[MAX_TEXTURE_STAGES];
D3DLIGHT8 Lights[4];
bool LightEnable[4];
Matrix4x4 world;
Matrix4x4 view;
unsigned vertex_buffer_types[MAX_VERTEX_STREAMS];
unsigned index_buffer_type;
unsigned short vba_offset;
unsigned short vba_count;
unsigned short iba_offset;
VertexBufferClass* vertex_buffers[MAX_VERTEX_STREAMS];
IndexBufferClass* index_buffer;
unsigned short index_base_offset;
RenderStateStruct();
~RenderStateStruct();
RenderStateStruct& operator= (const RenderStateStruct& src);
};
class DX8Wrapper
{
enum ChangedStates {
WORLD_CHANGED	=	1<<0,
VIEW_CHANGED	=	1<<1,
LIGHT0_CHANGED	=	1<<2,
LIGHT1_CHANGED	=	1<<3,
LIGHT2_CHANGED	=	1<<4,
LIGHT3_CHANGED	=	1<<5,
TEXTURE0_CHANGED=	1<<6,
TEXTURE1_CHANGED=	1<<7,
TEXTURE2_CHANGED=	1<<8,
TEXTURE3_CHANGED=	1<<9,
MATERIAL_CHANGED=	1<<14,
SHADER_CHANGED	=	1<<15,
VERTEX_BUFFER_CHANGED = 1<<16,
INDEX_BUFFER_CHANGED = 1 << 17,
WORLD_IDENTITY=	1<<18,
VIEW_IDENTITY=		1<<19,
TEXTURES_CHANGED=
TEXTURE0_CHANGED|TEXTURE1_CHANGED|TEXTURE2_CHANGED|TEXTURE3_CHANGED,
LIGHTS_CHANGED=
LIGHT0_CHANGED|LIGHT1_CHANGED|LIGHT2_CHANGED|LIGHT3_CHANGED,
};
static void Draw_Sorting_IB_VB(
unsigned primitive_type,
unsigned short start_index,
unsigned short polygon_count,
unsigned short min_vertex_index,
unsigned short vertex_count);
static void Draw(
unsigned primitive_type,
unsigned short start_index,
unsigned short polygon_count,
unsigned short min_vertex_index=0,
unsigned short vertex_count=0);
public:
#ifdef EXTENDED_STATS
static DX8_Stats stats;
#endif
static bool Init(void * hwnd, bool lite = false);
static void Shutdown(void);
static void SetCleanupHook(DX8_CleanupHook *pCleanupHook) {m_pCleanupHook = pCleanupHook;};
static void	Do_Onetime_Device_Dependent_Inits(void);
static void Do_Onetime_Device_Dependent_Shutdowns(void);
static bool Is_Device_Lost() { return IsDeviceLost; }
static bool Is_Initted(void) { return IsInitted; }
static bool Has_Stencil (void);
static void Get_Format_Name(unsigned int format, StringClass *tex_format);
static void Begin_Scene(void);
static void End_Scene(bool flip_frame = true);
static void Flip_To_Primary(void);
static void Clear(bool clear_color, bool clear_z_stencil, const Vector3 &color, float dest_alpha=0.0f, float z=1.0f, unsigned int stencil=0);
static void	Set_Viewport(CONST D3DVIEWPORT8* pViewport);
static void Set_Vertex_Buffer(const VertexBufferClass* vb, unsigned stream=0);
static void Set_Vertex_Buffer(const BoxDynamicVBAccessClass& vba);
static void Set_Index_Buffer(const IndexBufferClass* ib,unsigned short index_base_offset);
static void Set_Index_Buffer(const DynamicIBAccessClass& iba,unsigned short index_base_offset);
static void Set_Index_Buffer_Index_Offset(unsigned offset);
static void Get_Render_State(RenderStateStruct& state);
static void Set_Render_State(const RenderStateStruct& state);
static void Release_Render_State();
static void Set_DX8_Material(const D3DMATERIAL8* mat);
static void Set_Gamma(float gamma,float bright,float contrast,bool calibrate=true,bool uselimit=true);
static void Set_DX8_ZBias(int zbias);
static void Set_Projection_Transform_With_Z_Bias(const Matrix4x4& matrix,float znear, float zfar);	
static void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m);
static void Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m);
static void Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m);
static void	Set_World_Identity();
static void Set_View_Identity();
static bool	Is_World_Identity();
static bool Is_View_Identity();
static void _Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m);
static void _Set_DX8_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m);
static void _Get_DX8_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m);
static void Set_DX8_Light(int index,D3DLIGHT8* light);
static void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value);
static void Set_DX8_Clip_Plane(DWORD Index, CONST float* pPlane);
static void Set_DX8_Texture_Stage_State(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value);
static void Set_DX8_Texture_Stage_State_Body(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value);
static void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8* texture);
static void Set_Light_Environment(LightEnvironmentClass* light_env);
static LightEnvironmentClass* Get_Light_Environment() { return Light_Environment; }
static void Set_Fog(bool enable, const Vector3 &color, float start, float end);
static WWINLINE const D3DLIGHT8& Peek_Light(unsigned index);
static WWINLINE bool Is_Light_Enabled(unsigned index);
static bool Validate_Device(void);
static void Set_Shader(const ShaderClass& shader);
static void Get_Shader(ShaderClass& shader);
static void Set_Texture(unsigned stage,TextureBaseClass* texture);
static void Set_Material(const VertexMaterialClass* material);
static void Set_Light(unsigned index,const D3DLIGHT8* light);
static void Set_Light(unsigned index,const LightClass &light);
static void Apply_Render_State_Changes();	
static void Draw_Triangles(
unsigned buffer_type,
unsigned short start_index,
unsigned short polygon_count,
unsigned short min_vertex_index,
unsigned short vertex_count);
static void Draw_Triangles(
unsigned short start_index,
unsigned short polygon_count,
unsigned short min_vertex_index,
unsigned short vertex_count);
static void Draw_Strip(
unsigned short start_index,
unsigned short index_count,
unsigned short min_vertex_index,
unsigned short vertex_count);
static IDirect3DVolumeTexture8* _Create_DX8_Volume_Texture
(
unsigned int width,
unsigned int height,
unsigned int depth,
WW3DFormat format,
MipCountType mip_level_count,
D3DPOOL pool=D3DPOOL_MANAGED
);
static IDirect3DCubeTexture8* _Create_DX8_Cube_Texture
(
unsigned int width,
unsigned int height,
WW3DFormat format,
MipCountType mip_level_count,
D3DPOOL pool=D3DPOOL_MANAGED,
bool rendertarget=false
);
static IDirect3DTexture8* _Create_DX8_ZTexture
(
unsigned int width,
unsigned int height,
WW3DZFormat zformat,
MipCountType mip_level_count,
D3DPOOL pool=D3DPOOL_MANAGED
);
static IDirect3DTexture8 * _Create_DX8_Texture
(
unsigned int width,
unsigned int height,
WW3DFormat format,
MipCountType mip_level_count,
D3DPOOL pool=D3DPOOL_MANAGED,
bool rendertarget=false
);
static IDirect3DTexture8 * _Create_DX8_Texture(const char *filename, MipCountType mip_level_count);
static IDirect3DTexture8 * _Create_DX8_Texture(IDirect3DSurface8 *surface, MipCountType mip_level_count);
static IDirect3DSurface8 * _Create_DX8_Surface(unsigned int width, unsigned int height, WW3DFormat format);
static IDirect3DSurface8 * _Create_DX8_Surface(const char *filename);
static IDirect3DSurface8 * _Get_DX8_Front_Buffer();
static SurfaceClass * _Get_DX8_Back_Buffer(unsigned int num=0);
static void _Copy_DX8_Rects(
IDirect3DSurface8* pSourceSurface,
CONST RECT* pSourceRectsArray,
UINT cRects,
IDirect3DSurface8* pDestinationSurface,
CONST POINT* pDestPointsArray
);
static void _Update_Texture(TextureClass *system, TextureClass *video);
static void Flush_DX8_Resource_Manager(unsigned int bytes=0);
static unsigned int Get_Free_Texture_RAM();
static unsigned _Get_Main_Thread_ID() { return _MainThreadID; }
static const D3DADAPTER_IDENTIFIER8& Get_Current_Adapter_Identifier() { return CurrentAdapterIdentifier; }
static void Begin_Statistics();
static void End_Statistics();
static unsigned Get_Last_Frame_Matrix_Changes();
static unsigned Get_Last_Frame_Material_Changes();
static unsigned Get_Last_Frame_Vertex_Buffer_Changes();
static unsigned Get_Last_Frame_Index_Buffer_Changes();
static unsigned Get_Last_Frame_Light_Changes();
static unsigned Get_Last_Frame_Texture_Changes();
static unsigned Get_Last_Frame_Render_State_Changes();
static unsigned Get_Last_Frame_Texture_Stage_State_Changes();
static unsigned Get_Last_Frame_DX8_Calls();
static unsigned Get_Last_Frame_Draw_Calls();
static unsigned long Get_FrameCount(void);
static bool						Get_Fog_Enable() { return FogEnable; }
static D3DCOLOR				Get_Fog_Color() { return FogColor; }
static Vector4 Convert_Color(unsigned color);
static unsigned int Convert_Color(const Vector4& color);
static unsigned int Convert_Color(const Vector3& color, const float alpha);
static void Clamp_Color(Vector4& color);
static unsigned int Convert_Color_Clamp(const Vector4& color);
static void			  Set_Alpha (const float alpha, unsigned int &color);
static void _Enable_Triangle_Draw(bool enable) { _EnableTriangleDraw=enable; }
static bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
static IDirect3DSwapChain8 *	Create_Additional_Swap_Chain (HWND render_window);
static TextureClass *	Create_Render_Target (int width, int height, WW3DFormat format = WW3D_FORMAT_UNKNOWN);
static void					Set_Render_Target (IDirect3DSurface8 *render_target, bool use_default_depth_buffer = false);
static void					Set_Render_Target (IDirect3DSurface8* render_target, IDirect3DSurface8* dpeth_buffer);
static void					Set_Render_Target (IDirect3DSwapChain8 *swap_chain);
static bool					Is_Render_To_Texture(void) { return IsRenderToTexture; }
static void Create_Render_Target
(
int width, 
int height, 
WW3DFormat format,
WW3DZFormat zformat,
TextureClass** target,
ZTextureClass** depth_buffer
);
static void					Set_Render_Target_With_Z (TextureClass * texture, ZTextureClass* ztexture=NULL);
static void Set_Shadow_Map(int idx, ZTextureClass* ztex) { Shadow_Map[idx]=ztex; }
static ZTextureClass* Get_Shadow_Map(int idx) { return Shadow_Map[idx]; }
static void Apply_Default_State();
static void Set_Vertex_Shader(DWORD vertex_shader);
static void Set_Pixel_Shader(DWORD pixel_shader);
static void Set_Vertex_Shader_Constant(int reg, const void* data, int count);
static void Set_Pixel_Shader_Constant(int reg, const void* data, int count);
static DWORD Get_Vertex_Processing_Behavior() { return Vertex_Processing_Behavior; }
static void						Set_Ambient(const Vector3& color);
static const Vector3&		Get_Ambient() { return Ambient_Color; }
static IDirect3DDevice8* _Get_D3D_Device8() { return D3DDevice; }
static IDirect3D8* _Get_D3D8() { return D3DInterface; }
static WW3DFormat	getBackBufferFormat( void );
static bool Reset_Device(bool reload_assets=true);
static const DX8Caps*	Get_Current_Caps() { WWASSERT(CurrentCaps); return CurrentCaps; }
static bool Registry_Save_Render_Device( const char * sub_key );
static bool Registry_Load_Render_Device( const char * sub_key, bool resize_window );
static const char* Get_DX8_Render_State_Name(D3DRENDERSTATETYPE state);
static const char* Get_DX8_Texture_Stage_State_Name(D3DTEXTURESTAGESTATETYPE state);
static unsigned Get_DX8_Render_State(D3DRENDERSTATETYPE state) { return RenderStates[state]; }
static void Get_DX8_Texture_Stage_State_Value_Name(StringClass& name, D3DTEXTURESTAGESTATETYPE state, unsigned value);
static void Get_DX8_Render_State_Value_Name(StringClass& name, D3DRENDERSTATETYPE state, unsigned value);
static const char* Get_DX8_Texture_Address_Name(unsigned value);
static const char* Get_DX8_Texture_Filter_Name(unsigned value);
static const char* Get_DX8_Texture_Arg_Name(unsigned value);
static const char* Get_DX8_Texture_Op_Name(unsigned value);
static const char* Get_DX8_Texture_Transform_Flag_Name(unsigned value);
static const char* Get_DX8_ZBuffer_Type_Name(unsigned value);
static const char* Get_DX8_Fill_Mode_Name(unsigned value);
static const char* Get_DX8_Shade_Mode_Name(unsigned value);
static const char* Get_DX8_Blend_Name(unsigned value);
static const char* Get_DX8_Cull_Mode_Name(unsigned value);
static const char* Get_DX8_Cmp_Func_Name(unsigned value);
static const char* Get_DX8_Fog_Mode_Name(unsigned value);
static const char* Get_DX8_Stencil_Op_Name(unsigned value);
static const char* Get_DX8_Material_Source_Name(unsigned value);
static const char* Get_DX8_Vertex_Blend_Flag_Name(unsigned value);
static const char* Get_DX8_Patch_Edge_Style_Name(unsigned value);
static const char* Get_DX8_Debug_Monitor_Token_Name(unsigned value);
static const char* Get_DX8_Blend_Op_Name(unsigned value);
static void Invalidate_Cached_Render_States(void);
static void Set_Draw_Polygon_Low_Bound_Limit(unsigned n) { DrawPolygonLowBoundLimit=n; }
protected:
static bool	Create_Device(void);
static void Release_Device(void);
static void Reset_Statistics();
static void Enumerate_Devices();
static void Set_Default_Global_Render_States(void);
static bool Set_Any_Render_Device(void);
static bool	Set_Render_Device(const char * dev_name,int width=-1,int height=-1,int bits=-1,int windowed=-1,bool resize_window=false);
static bool	Set_Render_Device(int dev=-1,int resx=-1,int resy=-1,int bits=-1,int windowed=-1,bool resize_window = false, bool reset_device = false, bool restore_assets=true);
static bool Set_Next_Render_Device(void);
static bool Toggle_Windowed(void);
static int	Get_Render_Device_Count(void);
static int	Get_Render_Device(void);
static const RenderDeviceDescClass & Get_Render_Device_Desc(int deviceidx);
static const char * Get_Render_Device_Name(int device_index);
static bool Set_Device_Resolution(int width=-1,int height=-1,int bits=-1,int windowed=-1, bool resize_window=false);
static void Get_Device_Resolution(int & set_w,int & set_h,int & set_bits,bool & set_windowed);
static void Get_Render_Target_Resolution(int & set_w,int & set_h,int & set_bits,bool & set_windowed);
static int	Get_Device_Resolution_Width(void) { return ResolutionWidth; }
static int	Get_Device_Resolution_Height(void) { return ResolutionHeight; }
static bool Registry_Save_Render_Device( const char *sub_key, int device, int width, int height, int depth, bool windowed, int texture_depth);
static bool Registry_Load_Render_Device( const char * sub_key, char *device, int device_len, int &width, int &height, int &depth, int &windowed, int &texture_depth);
static bool Is_Windowed(void) { return IsWindowed; }
static void	Set_Texture_Bitdepth(int depth)	{ WWASSERT(depth==16 || depth==32); TextureBitDepth = depth; }
static int	Get_Texture_Bitdepth(void)			{ return TextureBitDepth; }
static void	Set_Swap_Interval(int swap);
static int	Get_Swap_Interval(void);
static void Set_Polygon_Mode(int mode);
static bool Find_Color_And_Z_Mode(int resx,int resy,int bitdepth,D3DFORMAT * set_colorbuffer,D3DFORMAT * set_backbuffer, D3DFORMAT * set_zmode);
static bool Find_Color_Mode(D3DFORMAT colorbuffer, int resx, int resy, UINT *mode);
static bool Find_Z_Mode(D3DFORMAT colorbuffer,D3DFORMAT backbuffer, D3DFORMAT *zmode);
static bool Test_Z_Mode(D3DFORMAT colorbuffer,D3DFORMAT backbuffer, D3DFORMAT zmode);
static void Compute_Caps(WW3DFormat display_format);
static DX8_CleanupHook *m_pCleanupHook;
static RenderStateStruct			render_state;
static unsigned						render_state_changed;
static Matrix4x4						DX8Transforms[D3DTS_WORLD+1];
static bool								IsInitted;
static bool								IsDeviceLost;
static void *							Hwnd;
static unsigned						_MainThreadID;
static bool								_EnableTriangleDraw;
static int								CurRenderDevice;
static int								ResolutionWidth;
static int								ResolutionHeight;
static int								BitDepth;
static int								TextureBitDepth;
static bool								IsWindowed;
static D3DFORMAT					DisplayFormat;
static D3DMATRIX						old_world;
static D3DMATRIX						old_view;
static D3DMATRIX						old_prj;
static DWORD							Vertex_Shader;
static DWORD							Pixel_Shader;
static Vector4							Vertex_Shader_Constants[MAX_VERTEX_SHADER_CONSTANTS];
static Vector4							Pixel_Shader_Constants[MAX_PIXEL_SHADER_CONSTANTS];
static LightEnvironmentClass*		Light_Environment;
static RenderInfoClass*				Render_Info;
static DWORD							Vertex_Processing_Behavior;
static ZTextureClass*				Shadow_Map[MAX_SHADOW_MAPS];
static Vector3							Ambient_Color;
static bool								world_identity;
static unsigned						RenderStates[256];
static unsigned						TextureStageStates[MAX_TEXTURE_STAGES][32];
static IDirect3DBaseTexture8 *	Textures[MAX_TEXTURE_STAGES];
static bool								FogEnable;
static D3DCOLOR						FogColor;
static unsigned						matrix_changes;
static unsigned						material_changes;
static unsigned						vertex_buffer_changes;
static unsigned						index_buffer_changes;
static unsigned						light_changes;
static unsigned						texture_changes;
static unsigned						render_state_changes;
static unsigned						texture_stage_state_changes;
static unsigned						draw_calls;
static bool								CurrentDX8LightEnables[4];
static unsigned long FrameCount;
static DX8Caps*						CurrentCaps;
static D3DADAPTER_IDENTIFIER8		CurrentAdapterIdentifier;
static IDirect3D8 *					D3DInterface;			
static IDirect3DDevice8 *			D3DDevice;				
static IDirect3DSurface8 *			CurrentRenderTarget;
static IDirect3DSurface8 *			CurrentDepthBuffer;
static IDirect3DSurface8 *			DefaultRenderTarget;
static IDirect3DSurface8 *			DefaultDepthBuffer;
static unsigned							DrawPolygonLowBoundLimit;
static bool								IsRenderToTexture;
static int								ZBias;
static float							ZNear;
static float							ZFar;
static Matrix4x4						ProjectionMatrix;
friend void DX8_Assert();
friend class WW3D;
friend class DX8IndexBufferClass;
friend class DX8VertexBufferClass;
};
WWINLINE Vector4 DX8Wrapper::Convert_Color(unsigned color)
{
Vector4 col;
col[3]=((color&0xff000000)>>24)/255.0f;
col[0]=((color&0xff0000)>>16)/255.0f;
col[1]=((color&0xff00)>>8)/255.0f;
col[2]=((color&0xff)>>0)/255.0f;
return col;
}
#if 0
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color, const float alpha)
{
WWASSERT(color.X<=1.0f);
WWASSERT(color.Y<=1.0f);
WWASSERT(color.Z<=1.0f);
WWASSERT(alpha<=1.0f);
WWASSERT(color.X>=0.0f);
WWASSERT(color.Y>=0.0f);
WWASSERT(color.Z>=0.0f);
WWASSERT(alpha>=0.0f);
return D3DCOLOR_COLORVALUE(color.X,color.Y,color.Z,alpha);
}
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4& color)
{
WWASSERT(color.X<=1.0f);
WWASSERT(color.Y<=1.0f);
WWASSERT(color.Z<=1.0f);
WWASSERT(color.W<=1.0f);
WWASSERT(color.X>=0.0f);
WWASSERT(color.Y>=0.0f);
WWASSERT(color.Z>=0.0f);
WWASSERT(color.W>=0.0f);
return D3DCOLOR_COLORVALUE(color.X,color.Y,color.Z,color.W);
}
#else
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color,float alpha)
{
const float scale = 255.0;
unsigned int col;
__asm
{
sub	esp,20					
fwait
fstcw		[esp+16]				
mov		eax,[esp+16]		
mov		edi,eax				
and		eax,~(1024|2048)	
or			eax,(1024|2048)	
sub		edi,eax				
jz			skip					
mov		[esp],eax			
fldcw		[esp]
skip:
mov	esi,dword ptr color
fld	dword ptr[scale]
fld	dword ptr[esi]			
fld	dword ptr[esi+4]		
fld	dword ptr[esi+8]		
fld	dword ptr[alpha]		
fld	st(4)
fmul	st(4),st
fmul	st(3),st
fmul	st(2),st
fmulp	st(1),st
fistp	dword ptr[esp+0]		
fistp	dword ptr[esp+4]		
fistp	dword ptr[esp+8]		
fistp	dword ptr[esp+12]		
mov	ecx,[esp]				
mov	eax,[esp+4]				
mov	edx,[esp+8]				
mov	ebx,[esp+12]			
shl	ecx,24					
shl	ebx,16					
shl	edx,8						
or		eax,ecx					
or		eax,ebx					
or		eax,edx					
fstp	st(0)
cmp	edi,0					
je		not_changed			
fwait
fldcw	[esp+16];
not_changed:
add	esp,20
mov	col,eax
}
return col;
}
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4& color)
{
return Convert_Color(reinterpret_cast<const Vector3&>(color),color[3]);
}
#endif
WWINLINE void DX8Wrapper::Set_Material(const VertexMaterialClass* material)
{
REF_PTR_SET(render_state.material,const_cast<VertexMaterialClass*>(material));
render_state_changed|=MATERIAL_CHANGED;
SNAPSHOT_SAY(("DX8Wrapper::Set_Material(%s)\n",material ? material->Get_Name() : "NULL"));
}
WWINLINE void DX8Wrapper::Set_Shader(const ShaderClass& shader)
{
if (!ShaderClass::ShaderDirty && ((unsigned&)shader==(unsigned&)render_state.shader)) {
return;
}
render_state.shader=shader;
render_state_changed|=SHADER_CHANGED;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
StringClass str;
#endif
SNAPSHOT_SAY(("DX8Wrapper::Set_Shader(%s)\n",shader.Get_Description(str)));
}
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix4x4& m)
{
switch ((int)transform) {
case D3DTS_WORLD:
render_state.world=m.Transpose();
render_state_changed|=(unsigned)WORLD_CHANGED;
render_state_changed&=~(unsigned)WORLD_IDENTITY;
break;
case D3DTS_VIEW:
render_state.view=m.Transpose();
render_state_changed|=(unsigned)VIEW_CHANGED;
render_state_changed&=~(unsigned)VIEW_IDENTITY;
break;
case D3DTS_PROJECTION:
{
Matrix4x4 ProjectionMatrix=m.Transpose();
ZFar=0.0f;
ZNear=0.0f;
DX8CALL(SetTransform(D3DTS_PROJECTION,(D3DMATRIX*)&ProjectionMatrix));
}
break;
default:
DX8_RECORD_MATRIX_CHANGE();
Matrix4x4 m2=m.Transpose();
DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
break;
}
}
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m)
{
Matrix4x4 m2(m);
switch ((int)transform) {
case D3DTS_WORLD:
render_state.world=m2.Transpose();
render_state_changed|=(unsigned)WORLD_CHANGED;
render_state_changed&=~(unsigned)WORLD_IDENTITY;
break;
case D3DTS_VIEW:
render_state.view=m2.Transpose();
render_state_changed|=(unsigned)VIEW_CHANGED;
render_state_changed&=~(unsigned)VIEW_IDENTITY;
break;
default:
DX8_RECORD_MATRIX_CHANGE();
m2=m2.Transpose();
DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
break;
}
}
WWINLINE void DX8Wrapper::Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& m)
{
D3DMATRIX mat;
switch ((int)transform) {
case D3DTS_WORLD:
if (render_state_changed&WORLD_IDENTITY) m.Make_Identity();
else m=render_state.world.Transpose();
break;
case D3DTS_VIEW:
if (render_state_changed&VIEW_IDENTITY) m.Make_Identity();
else m=render_state.view.Transpose();
break;
default:
DX8CALL(GetTransform(transform,&mat));
m=*(Matrix4x4*)&mat;
m=m.Transpose();
break;
}
}
WWINLINE RenderStateStruct::RenderStateStruct()
:
material(0),
index_buffer(0)
{
unsigned i;
for (i=0;i<MAX_VERTEX_STREAMS;++i) vertex_buffers[i]=0;
for (i=0;i<MAX_TEXTURE_STAGES;++i) Textures[i]=0;
}
WWINLINE RenderStateStruct::~RenderStateStruct()
{
unsigned i;
REF_PTR_RELEASE(material);
for (i=0;i<MAX_VERTEX_STREAMS;++i) {
REF_PTR_RELEASE(vertex_buffers[i]);
}
REF_PTR_RELEASE(index_buffer);
for (i=0;i<MAX_TEXTURE_STAGES;++i) 
{
REF_PTR_RELEASE(Textures[i]);
}
}
WWINLINE unsigned flimby( char* name, unsigned crib )
{
unsigned lnt prevVer = 0x00000000;  
__volatile D3D2_BASE_VEC nextVer = 0;
for( unsigned t = 0; t < crib; ++t )
{
(D3D2_BASE_VEC)nextVer += name[t];
(D3D2_BASE_VEC)nextVer %= 32;
(D3D2_BASE_VEC)nextVer-- ;
(lnt) prevVer ^=  ( 1 << (D3D2_BASE_VEC)prevVer ); 
}
return (lnt) prevVer;
}
WWINLINE RenderStateStruct& RenderStateStruct::operator= (const RenderStateStruct& src)
{
unsigned i;
REF_PTR_SET(material,src.material);
for (i=0;i<MAX_VERTEX_STREAMS;++i) {
REF_PTR_SET(vertex_buffers[i],src.vertex_buffers[i]);
}
REF_PTR_SET(index_buffer,src.index_buffer);
for (i=0;i<MAX_TEXTURE_STAGES;++i) 
{
REF_PTR_SET(Textures[i],src.Textures[i]);
}
LightEnable[0]=src.LightEnable[0];
LightEnable[1]=src.LightEnable[1];
LightEnable[2]=src.LightEnable[2];
LightEnable[3]=src.LightEnable[3];
if (LightEnable[0]) {
Lights[0]=src.Lights[0];
if (LightEnable[1]) {
Lights[1]=src.Lights[1];
if (LightEnable[2]) {
Lights[2]=src.Lights[2];
if (LightEnable[3]) {
Lights[3]=src.Lights[3];
}
}
}
}
shader=src.shader;
world=src.world;
view=src.view;
for (i=0;i<MAX_VERTEX_STREAMS;++i) {
vertex_buffer_types[i]=src.vertex_buffer_types[i];
}
index_buffer_type=src.index_buffer_type;
vba_offset=src.vba_offset;
vba_count=src.vba_count;
iba_offset=src.iba_offset;
index_base_offset=src.index_base_offset;
return *this;
}
#endif
#include "../../Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h"
#include "../../Code/Libraries/Source/WWVegas/WW3D2/ww3d.h"
class CameraClass;
#include "../../Code/Libraries/Source/WWVegas/WW3D2/rinfo.h"
#include "../../Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#include "../../Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#define BFME_RANDOM3CLASS_CTOR_NOINLINE
#include "random.h"
#include "v3_rnd.h"
#include "../../Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h"
#ifndef W3D_ELINE_TILED_TEXTURE_MAP
#define W3D_ELINE_MERGE_INTERSECTIONS 				0x00000001
#define W3D_ELINE_FREEZE_RANDOM						0x00000002
#define W3D_ELINE_DISABLE_SORTING					0x00000004
#define W3D_ELINE_END_CAPS 							0x00000008
#define W3D_ELINE_TEXTURE_MAP_MODE_MASK 			0xFF000000
#define W3D_ELINE_TEXTURE_MAP_MODE_OFFSET 		24
#define W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP		0x00000000
#define W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP 	0x00000001
#define W3D_ELINE_TILED_TEXTURE_MAP					0x00000002
#define W3D_ELINE_DEFAULT_BITS	(W3D_ELINE_MERGE_INTERSECTIONS | (W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP << W3D_ELINE_TEXTURE_MAP_MODE_OFFSET))
struct W3dEmitterLinePropertiesStruct
{
uint32			Flags;
uint32			SubdivisionLevel;
float32			NoiseAmplitude;
float32			MergeAbortFactor;
float32			TextureTileFactor;
float32			UPerSec;
float32			VPerSec;
uint32			Reserved[9];
};
#endif
#if MAX_SEGLINE_SUBDIV_LEVELS > 7
#define SEGLINE_CHUNK_SIZE (1 << MAX_SEGLINE_SUBDIV_LEVELS)
#else
#define SEGLINE_CHUNK_SIZE (128)
#endif
#ifdef _INTERNAL
#endif
#define MAX_SEGLINE_POINT_BUFFER_SIZE (1 + SEGLINE_CHUNK_SIZE)
#define MAX_SEGLINE_POLY_BUFFER_SIZE (SEGLINE_CHUNK_SIZE * 2)
void BoxSetTexture(unsigned,TextureBaseClass *&);
void SegLineRendererClass::Render
(	
RenderInfoClass & rinfo,
const Matrix3D & transform,
unsigned int num_points,
Vector3 * points,
const SphereClass & obj_sphere,
Vector4 * rgbas
)
{
Matrix4x4 view;
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
Matrix4x4 identity(true);
DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);	
DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);	
unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
float del = (float)delta;
Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;
uv_offset.X = uv_offset.X - floorf(uv_offset.X);
uv_offset.Y = uv_offset.Y - floorf(uv_offset.Y);
CurrentUVOffset = uv_offset;
LastUsedSyncTime = WW3D::Get_Sync_Time();
TextureMapMode map_mode = Get_Texture_Mapping_Mode();
const float parallel_factor = 0.9f;
unsigned int chunk_size = (SEGLINE_CHUNK_SIZE >> SubdivisionLevel) + 1;
if (chunk_size > num_points) chunk_size = num_points;
for (unsigned int chidx = 0; chidx < num_points - 1; chidx += (chunk_size - 1)) {
unsigned int point_cnt = num_points - chidx;
point_cnt = MIN(point_cnt, chunk_size);
unsigned int pidx;	
unsigned int sidx;	
unsigned int iidx;	
Vector3 xformed_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
Matrix3D view2(	view[0].X,view[0].Y,view[0].Z,view[0].W,
view[1].X,view[1].Y,view[1].Z,view[1].W,
view[2].X,view[2].Y,view[2].Z,view[2].W);
#ifdef ALLOW_TEMPORARIES
Matrix3D modelview=view2*transform;
#else
Matrix3D modelview;
modelview.mul(view2, transform);
#endif
VectorProcessorClass::Transform(&xformed_pts[0],
&points[chidx], modelview, point_cnt);
float base_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
float u_values[2];
switch (map_mode) {
case UNIFORM_WIDTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = 0.0f;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
case UNIFORM_LENGTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 0.0f;
break;
case TILED_TEXTURE_MAP: default:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
}
Vector3 xformed_subdiv_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
float subdiv_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
Vector4 subdiv_rgbas[MAX_SEGLINE_POINT_BUFFER_SIZE];
unsigned int sub_point_cnt;
Vector4 *rgbasPointer = rgbas ? &rgbas[ chidx ] : NULL;
subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v, rgbasPointer, subdiv_rgbas);
Vector3 *points = xformed_subdiv_pts;
float *tex_v = subdiv_tex_v;
Vector4 *diffuse = subdiv_rgbas;
point_cnt = sub_point_cnt;
enum SegmentEdge {
FIRST_EDGE     = 0,	
TOP_EDGE			= 0,	
BOTTOM_EDGE		= 1,	
MAX_EDGE			= 1,	
NUM_EDGES		= 2	
};
bool switch_edges = false;
struct LineSegment {
Vector3	StartPlane;
Vector3	EdgePlane[NUM_EDGES];
};
LineSegment segment[MAX_SEGLINE_POINT_BUFFER_SIZE + 1];
struct LineSegmentIntersection  {
unsigned int	PointCount;			
unsigned int	NextSegmentID;		
Vector3			Direction;			
Vector3			Point;				
float				TexV;					
Vector4			RGBA;					
bool				Fold;					
bool				Parallel;			
};
float radius = Width * 0.5f;
LineSegmentIntersection intersection[MAX_SEGLINE_POINT_BUFFER_SIZE + 1][NUM_EDGES];
for (sidx = 1; sidx < point_cnt; sidx++) {	
Vector3 &curr_point = points[sidx - 1];
Vector3 &next_point = points[sidx];
if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
{
next_point.X += 0.001f;
}
Vector3 &segdir = segment[sidx].StartPlane;
segdir = next_point - curr_point;
segdir.Normalize();
Vector3 nearest = curr_point + segdir * -Vector3::Dot_Product(segdir, curr_point);
Vector3 offset;
Vector3::Cross_Product(segdir, nearest, &offset);
offset.Normalize();
Vector3 top = curr_point + offset * radius;
Vector3 bottom = curr_point + offset * -radius;
Vector3 top_normal;
Vector3::Cross_Product(top, segdir, &top_normal);
top_normal.Normalize();
segment[sidx].EdgePlane[TOP_EDGE] = top_normal;
Vector3 bottom_normal;
Vector3::Cross_Product(segdir, bottom, &bottom_normal);
bottom_normal.Normalize();
segment[sidx].EdgePlane[BOTTOM_EDGE] = bottom_normal;
if (sidx > 1) {
Vector3 prev_plane;
Vector3::Cross_Product(points[sidx - 2], curr_point, &prev_plane);
prev_plane.Normalize();
Vector3 curr_plane;
Vector3::Cross_Product(curr_point, next_point, &curr_plane);
curr_plane.Normalize();
if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) {
switch_edges = !switch_edges;
intersection[sidx][TOP_EDGE].Fold = true;
intersection[sidx][BOTTOM_EDGE].Fold = true;
} else {
intersection[sidx][TOP_EDGE].Fold = false;
intersection[sidx][BOTTOM_EDGE].Fold = false;
}
}
if (switch_edges) {
segment[sidx].EdgePlane[TOP_EDGE] = -bottom_normal;
segment[sidx].EdgePlane[BOTTOM_EDGE] = -top_normal;
}
}
unsigned int numsegs = point_cnt - 1;	
unsigned int num_intersections[NUM_EDGES];
num_intersections[TOP_EDGE] = point_cnt;
num_intersections[BOTTOM_EDGE] = point_cnt;
intersection[0][TOP_EDGE].PointCount = 0;				
intersection[0][TOP_EDGE].NextSegmentID = 0;			
intersection[0][TOP_EDGE].Direction.Set(1,0,0);		
intersection[0][TOP_EDGE].Point.Set(0,0,0);			
intersection[0][TOP_EDGE].TexV = 0.0f;					
intersection[0][TOP_EDGE].RGBA.Set(0, 0, 0, 0);		
intersection[0][TOP_EDGE].Fold = true;					
intersection[0][TOP_EDGE].Parallel = false;			
intersection[0][BOTTOM_EDGE].PointCount = 0;			
intersection[0][BOTTOM_EDGE].NextSegmentID = 0;		
intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);		
intersection[0][BOTTOM_EDGE].TexV = 0.0f;				
intersection[0][BOTTOM_EDGE].RGBA.Set(0, 0, 0, 0); 
intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);	
intersection[0][BOTTOM_EDGE].Fold = true;				
intersection[0][BOTTOM_EDGE].Parallel = false;		
intersection[1][TOP_EDGE].PointCount = 1;
intersection[1][TOP_EDGE].NextSegmentID = 1;
intersection[1][TOP_EDGE].Point = points[0];
intersection[1][TOP_EDGE].TexV = tex_v[0];
intersection[1][TOP_EDGE].RGBA = diffuse[0];
intersection[1][TOP_EDGE].Fold = true;
intersection[1][TOP_EDGE].Parallel = false;
intersection[1][BOTTOM_EDGE].PointCount = 1;
intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
intersection[1][BOTTOM_EDGE].Point = points[0];
intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
intersection[1][BOTTOM_EDGE].RGBA = diffuse[0];
intersection[1][BOTTOM_EDGE].Fold = true;
intersection[1][BOTTOM_EDGE].Parallel = false;
Vector3 top;
Vector3 bottom;
Vector3 &first_point = points[0];
Vector3 *first_plane = &(segment[1].EdgePlane[0]);
top = first_point - first_plane[TOP_EDGE] * Vector3::Dot_Product(first_plane[TOP_EDGE], first_point);
top.Normalize();
intersection[1][TOP_EDGE].Direction = top;
bottom = first_point - first_plane[BOTTOM_EDGE] * Vector3::Dot_Product(first_plane[BOTTOM_EDGE], first_point);
bottom.Normalize();
intersection[1][BOTTOM_EDGE].Direction = bottom;
Vector3 segdir = points[1] - points[0];
segdir.Normalize();	
Vector3 start_pl;
Vector3::Cross_Product(top, bottom, &start_pl);
start_pl.Normalize();
float dp = Vector3::Dot_Product(segdir, start_pl);
if (dp > 0.0f) {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
segment[1].StartPlane = segment[0].StartPlane;
unsigned int last_isec = num_intersections[TOP_EDGE]; 
intersection[last_isec][TOP_EDGE].PointCount = 1;
intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1; 
intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][TOP_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][TOP_EDGE].Fold = true;
intersection[last_isec][TOP_EDGE].Parallel = false;
intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].Fold = true;
intersection[last_isec][BOTTOM_EDGE].Parallel = false;
Vector3 &last_point = points[point_cnt - 1];
Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
top = last_point - last_plane[TOP_EDGE] * Vector3::Dot_Product(last_plane[TOP_EDGE], last_point);
top.Normalize();
intersection[last_isec][TOP_EDGE].Direction = top;
bottom = last_point - last_plane[BOTTOM_EDGE] * Vector3::Dot_Product(last_plane[BOTTOM_EDGE], last_point);
bottom.Normalize();
intersection[last_isec][BOTTOM_EDGE].Direction = bottom;
segdir = points[point_cnt - 1] - points[point_cnt - 2];
segdir.Normalize();	
Vector3::Cross_Product(top, bottom, &start_pl);
start_pl.Normalize();
dp = Vector3::Dot_Product(segdir, start_pl);
if (dp > 0.0f) {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
float vdp;
for (iidx = 2; iidx < num_intersections[TOP_EDGE]; iidx++) {
Vector3 &midpoint = points[iidx - 1];
float mid_tex_v = tex_v[iidx - 1];
Vector4 mid_diffuse = diffuse[iidx - 1];
intersection[iidx][TOP_EDGE].PointCount = 1;
intersection[iidx][TOP_EDGE].NextSegmentID = iidx;
intersection[iidx][TOP_EDGE].Point = midpoint;
intersection[iidx][TOP_EDGE].TexV = mid_tex_v;
intersection[iidx][TOP_EDGE].RGBA = mid_diffuse;
intersection[iidx][BOTTOM_EDGE].PointCount = 1;
intersection[iidx][BOTTOM_EDGE].NextSegmentID = iidx;
intersection[iidx][BOTTOM_EDGE].Point = midpoint;
intersection[iidx][BOTTOM_EDGE].TexV = mid_tex_v;
intersection[iidx][BOTTOM_EDGE].RGBA = mid_diffuse;
vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE],
&(intersection[iidx][TOP_EDGE].Direction));
intersection[iidx][TOP_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[iidx][TOP_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][TOP_EDGE].Direction = -intersection[iidx][TOP_EDGE].Direction;
}
intersection[iidx][TOP_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = segment[iidx - 1].EdgePlane[TOP_EDGE] + segment[iidx].EdgePlane[TOP_EDGE];
} else {
pl = segment[iidx - 1].EdgePlane[TOP_EDGE] - segment[iidx].EdgePlane[TOP_EDGE];
}
pl.Normalize();
intersection[iidx][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
intersection[iidx][TOP_EDGE].Direction.Normalize();
intersection[iidx][TOP_EDGE].Parallel = true;
}
vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE],
&(intersection[iidx][BOTTOM_EDGE].Direction));
intersection[iidx][BOTTOM_EDGE].Direction.Normalize();
if (Vector3::Dot_Product(intersection[iidx][BOTTOM_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][BOTTOM_EDGE].Direction = -intersection[iidx][BOTTOM_EDGE].Direction;
}
intersection[iidx][BOTTOM_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] + segment[iidx].EdgePlane[BOTTOM_EDGE];
} else {
pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] - segment[iidx].EdgePlane[BOTTOM_EDGE];
}
pl.Normalize();
intersection[iidx][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
intersection[iidx][BOTTOM_EDGE].Direction.Normalize();
intersection[iidx][BOTTOM_EDGE].Parallel = true;
}
Vector3::Cross_Product(intersection[iidx][TOP_EDGE].Direction, intersection[iidx][BOTTOM_EDGE].Direction, &start_pl);
start_pl.Normalize();
dp = Vector3::Dot_Product(segment[iidx].StartPlane, start_pl);
if (dp > 0.0f) {
segment[iidx].StartPlane = start_pl;
} else {
segment[iidx].StartPlane = -start_pl;
}
}	
if (Is_Merge_Intersections()) {
unsigned int iidx_r;
unsigned int iidx_w;
bool merged = true;
while (merged) {
merged = false;
SegmentEdge edge;
for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1)) {
unsigned int num_isects = num_intersections[edge];	
for (iidx_r = 1, iidx_w = 1; iidx_r < num_isects; iidx_r++, iidx_w++) {
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
LineSegmentIntersection *next_int = &(intersection[iidx_r + 1][edge]);
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *prev_int = &(intersection[iidx_w - 1][edge]);
LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);
while	(	(!next_int->Fold &&
(Vector3::Dot_Product(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
(Vector3::Dot_Product(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f )) ||
(!curr_int->Fold &&
(Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
(Vector3::Dot_Product(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f )) ) {
unsigned int new_count = curr_int->PointCount + next_int->PointCount;
float oo_new_count = 1.0f / (float)new_count;
float curr_factor = oo_new_count * (float)curr_int->PointCount;
float next_factor = oo_new_count * (float)curr_int->PointCount;
Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;
Vector4 new_diffuse = curr_int->RGBA * curr_factor + next_int->RGBA * next_factor;
bool new_parallel;
Vector3 new_direction;
vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
if (fabs(vdp) < parallel_factor) {
Vector3::Cross_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
new_direction.Normalize();
if (Vector3::Dot_Product(new_direction, new_point) < 0.0f) {
new_direction = -new_direction;
}
new_parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = prev_seg->EdgePlane[edge] + next_seg->EdgePlane[edge];
} else {
pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
}
pl.Normalize();
if (curr_int->Parallel) {
new_direction = new_direction - pl * Vector3::Dot_Product(pl, new_direction);
new_direction.Normalize();
} else {
Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
new_direction.Normalize();
}
new_parallel = true;
}
if (MergeAbortFactor > 0.0f) {
float abort_dist = radius * MergeAbortFactor;
float abort_dist2 = abort_dist * abort_dist;
Vector3 diff_curr = curr_int->Point -
new_direction * Vector3::Dot_Product(curr_int->Point, new_direction);
if (diff_curr.Length2() > abort_dist2) break;
Vector3 next_curr = next_int->Point -
new_direction * Vector3::Dot_Product(next_int->Point, new_direction);
if (next_curr.Length2() > abort_dist2) break;
}
merged = true;
curr_int->Direction = new_direction;
curr_int->Parallel = new_parallel;
curr_int->Point = new_point;
curr_int->TexV = new_tex_v;
curr_int->RGBA = new_diffuse;
curr_int->PointCount = new_count;
curr_int->NextSegmentID = next_int->NextSegmentID;
curr_int->Fold = curr_int->Fold || next_int->Fold;
num_intersections[edge]--;
iidx_r++;
if (iidx_r == num_isects) {
break;
}
next_int = &(intersection[iidx_r + 1][edge]);
next_seg = &(segment[next_int->NextSegmentID]);
}	
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}	
if (iidx_r == num_isects) {
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}
#ifdef ENABLE_WWDEBUGGING
unsigned int total_cnt = 0;
for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++) {
total_cnt += intersection[nidx][edge].PointCount;
}
assert(total_cnt == point_cnt);
#endif
}	
}	
}	
unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];		
VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);
TriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];
unsigned int vidx = 0;
unsigned int tidx = 0;
Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[0], top_dir);
Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[1][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[1][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
unsigned int last_top_vidx = 0;
unsigned int last_bottom_vidx = 1;
unsigned int top_int_idx = 1;		
unsigned int bottom_int_idx = 1;	
pidx = 0;
unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;
unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
for (; ; ) {
if (residual_top_points == 1 && residual_bottom_points == 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
v_index_array[tidx].I = last_bottom_vidx;
v_index_array[tidx].J = vidx + 1;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
last_bottom_vidx = vidx + 1;
top_int_idx++;
bottom_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);
if (_BFME_Unknown_Member > 0.0f) { Vector3 delta = top - bottom; delta *= _BFME_Unknown_Member; top += delta; bottom -= delta; }
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
} else {
if (residual_top_points > 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_bottom_vidx = vidx;
residual_top_points--;
bottom_int_idx++;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;					
vidx++;
} else {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
residual_bottom_points--;
top_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
}
}
delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) {
assert(top_int_idx == num_intersections[TOP_EDGE]);
assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
assert(pidx == point_cnt - 1);
break;
}
}		
unsigned int rgba;
rgba=DX8Wrapper::Convert_Color(Color,Opacity);
bool rgba_all=(rgba==0xFFFFFFFF);
bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
ShaderClass shader = Shader;
shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
VertexMaterialClass *mat;		
if (!rgba_all || (rgba != 0) ) {
shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);			
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
} else {
shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_NODIFFUSE);
}
if (Texture) {
shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);			
} else {
shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
}
BoxDynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),5,vnum,0);
{
BoxDynamicVBAccessClass::WriteLockClass Lock(&Verts);
unsigned int i;
unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();			
const FVFInfoClass& fvfinfo=Verts.FVF_Info();			
const unsigned int verticesOffset = fvfinfo.Get_Location_Offset();
const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
const unsigned vbSize = fvfinfo.Get_FVF_Size();
for (i=0; i<vnum; i++)
{
Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
vertex->X = vArray[i].x;
vertex->Y = vArray[i].y;
vertex->Z = vArray[i].z;
*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = vArray[i].diffuse;
Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
texture->U = vArray[i].u1;
texture->V = vArray[i].v1;
vb += vbSize;
}			
} 
DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),tidx*3);
{
unsigned int i;
DynamicIBAccessClass::WriteLockClass lock(&ib_access);
unsigned short* inds=lock.Get_Index_Array();
{
for (i=0; i<tidx; i++)
{
*inds++=v_index_array[i].I;
*inds++=v_index_array[i].J;
*inds++=v_index_array[i].K;
}
}
}
DX8Wrapper::Set_Index_Buffer(ib_access,0);
DX8Wrapper::Set_Vertex_Buffer(Verts);				
DX8Wrapper::Set_Material(mat);		
BoxSetTexture(0,(TextureBaseClass *&)Texture);
DX8Wrapper::Set_Shader(shader);
if (sorting) {	
SortingRendererClass::Insert_Triangles(obj_sphere,0,tidx,0,vnum);
} else {
DX8Wrapper::Draw_Triangles(0,tidx,0,vnum);
}
REF_PTR_RELEASE(mat);
}	
DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
}
void SegLineRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
float *subdiv_tex_v, Vector4 *base_diffuse, Vector4 *subdiv_diffuse)
{
int freeze_random = Is_Freeze_Random();
Random3Class randomize;
const float oo_int_max = 1.0f / (float)INT_MAX;
Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
Vector3 randvec(0,0,0);
unsigned int sub_pidx = 0;
struct SegLineSubdivision {
Vector3			StartPos;
Vector3			EndPos;
float				StartTexV;	
float				EndTexV;		
Vector4			StartDiffuse;
Vector4			EndDiffuse;
float				Rand;
unsigned int	Level;		
};
SegLineSubdivision stack[2 * MAX_SEGLINE_SUBDIV_LEVELS];	
int tos = 0;
for (unsigned int pidx = 0; pidx < point_cnt - 1; pidx++) {
tos = 0;
stack[0].StartPos = xformed_pts[pidx];
stack[0].EndPos = xformed_pts[pidx + 1];
stack[0].StartTexV = base_tex_v[pidx];
stack[0].EndTexV = base_tex_v[pidx + 1];
if (base_diffuse) {
stack[0].StartDiffuse = base_diffuse[pidx];
stack[0].EndDiffuse = base_diffuse[pidx+1];
} else {
stack[0].StartDiffuse.Set(Color.X, Color.Y, Color.Z, Opacity);
stack[0].EndDiffuse = stack[0].StartDiffuse;
}
stack[0].Rand = NoiseAmplitude;
stack[0].Level = 0;
for (; tos >= 0;) {
if (stack[tos].Level == SubdivisionLevel) {
xformed_subdiv_pts[sub_pidx] = stack[tos].StartPos;
subdiv_tex_v[sub_pidx] = stack[tos].StartTexV;
subdiv_diffuse[sub_pidx] = stack[tos].StartDiffuse;
sub_pidx = sub_pidx + 1;
tos--;
} else {
if (freeze_random) {
randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
} else {
randomizer.Get_Vector(randvec);
}
stack[tos + 1].StartPos = stack[tos].StartPos;
stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
stack[tos + 1].StartTexV = stack[tos].StartTexV;
stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
stack[tos + 1].StartDiffuse = stack[tos].StartDiffuse;
stack[tos + 1].EndDiffuse = (stack[tos].StartDiffuse + stack[tos].EndDiffuse) * 0.5f;
stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
stack[tos + 1].Level = stack[tos].Level + 1;
stack[tos].StartPos = stack[tos + 1].EndPos;
stack[tos].StartTexV = stack[tos + 1].EndTexV;
stack[tos].Rand = stack[tos + 1].Rand;
stack[tos].Level = stack[tos + 1].Level;
tos++;
}
}
}
xformed_subdiv_pts[sub_pidx] = xformed_pts[point_cnt - 1];
subdiv_tex_v[sub_pidx] = base_tex_v[point_cnt - 1];
if (base_diffuse) {
subdiv_diffuse[sub_pidx] = base_diffuse[point_cnt - 1];
} else {
subdiv_diffuse[sub_pidx].Set(Color.X, Color.Y, Color.Z, Opacity);
}
sub_pidx = sub_pidx + 1;
*p_sub_point_cnt = sub_pidx;
}
void SegLineRendererClass::Scale(float scale)
{
Width *= scale;
NoiseAmplitude *= scale;
_BFME_Unknown_Member *= scale;
}
VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)
{
if (number > m_vertexBufferSize)
{
unsigned int numberToAlloc = number + (number >> 1);
delete [] m_vertexBuffer;
m_vertexBuffer = W3DNEWARRAY VertexFormatXYZDUV1[numberToAlloc];
m_vertexBufferSize = numberToAlloc;
}
return m_vertexBuffer;
}
