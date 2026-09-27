// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Native BFME sorting insertion, RVA 0093B340, 1257 bytes.
// Derived from EA GPL-3.0-or-later GeneralsMD sortingrenderer.cpp and
// dx8wrapper.h. Identity: matched no-sphere Insert_Triangles at 009037D0
// calls this overload, and the ZH sorting-state/list insertion sequence agrees.
// BFME TextureBaseClass references use a WORD at +4 and the named out-of-line
// Release_Ref at 009EB7A0. The ZH header's DWORD refcount is incompatible.
// Retail state copies independently witness RenderStateStruct at node+0C:
// material +10; textures +14; lights +34; enable flags +1D4;
// world +1D8; view +218; vertex buffers +26C; index buffer +274.
// Only transformed center Z is consumed: keep the matrix expressions at
// their state accesses so VC7 preserves retail's x87 sum evaluation order.
#define Matrix4x4 Matrix4
#include "sortingrenderer.h"
#include "sphere.h"
#include "matrix4.h"
#include "shader.h"
#include "dllist.h"
#include "refcount.h"
#include "d3d8.h"
class TextureBaseClass {
public:
 void Add_Ref() { ++refs0093B340; }
 void Release_Ref();
private:
 void* vptr0093B340;
 unsigned short refs0093B340;
};
const unsigned MAX_VERTEX_STREAMS=2, MAX_TEXTURE_STAGES=8;
struct RenderStateStruct
{
	ShaderClass shader;
	RefCountClass* material;
	TextureBaseClass * Textures[MAX_TEXTURE_STAGES];
	D3DLIGHT8 Lights[4];
	bool LightEnable[4];
  //unsigned lightsHash;
	Matrix4 world;
	Matrix4 view;
	unsigned vertex_buffer_types[MAX_VERTEX_STREAMS];
	unsigned index_buffer_type;
	unsigned short vba_offset;
	unsigned short vba_count;
	unsigned short iba_offset;
	RefCountClass* vertex_buffers[MAX_VERTEX_STREAMS];
	RefCountClass* index_buffer;
	unsigned short index_base_offset;

	RenderStateStruct();
	~RenderStateStruct();

	RenderStateStruct& operator= (const RenderStateStruct& src);
};

__forceinline RenderStateStruct& RenderStateStruct::operator= (const RenderStateStruct& src)
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


    //lightsHash = flimby((char*)(&Lights[0]), sizeof(D3DLIGHT8)-1 );

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
class DX8Wrapper {
public:
 static RenderStateStruct render_state;
 static __forceinline void Get_Render_State(RenderStateStruct& state) { state=render_state; }
 static void Draw_Triangles(unsigned short,unsigned short,unsigned short,unsigned short);
};
class WW3D { public: static bool IsSortingEnabled; static bool Is_Sorting_Enabled(){return IsSortingEnabled;} };
void bfmeAccount(int,int);
class SortingNodeStruct : public DLNodeClass<SortingNodeStruct>
{
	// BFME: global operator new/delete (retail Deinit @0x93BD60 calls 0x881EB0),
	// not W3DMPO pool free — drop W3DMPO_GLUE (same as MatBuffer/TexBuffer).

public:
	RenderStateStruct sorting_state;

	float transformed_center;
	unsigned short start_index;			// First index used in the ib
	unsigned short polygon_count;			// Polygon count to process (3 indices = one polygon)
	unsigned short min_vertex_index;		// First index used in the vb
	unsigned short vertex_count;			// Number of vertices used in vb
};

static DLListClass<SortingNodeStruct> sorted_list;

SortingNodeStruct* Get_Sorting_Struct();
void SortingRendererClass::Insert_Triangles(
	const SphereClass& bounding_sphere,
	unsigned short start_index, 
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	if (!WW3D::Is_Sorting_Enabled()) {
		DX8Wrapper::Draw_Triangles(start_index,polygon_count,min_vertex_index,vertex_count);
		return;
	}




	bfmeAccount(polygon_count,vertex_count);

	SortingNodeStruct* state=Get_Sorting_Struct();

	DX8Wrapper::Get_Render_State(reinterpret_cast<RenderStateStruct &>(state->sorting_state));

 	state->start_index=start_index;
	state->polygon_count=polygon_count;
	state->min_vertex_index=min_vertex_index;
	state->vertex_count=vertex_count;


	float transformed_z=
        (state->sorting_state.world[0][0]*state->sorting_state.view[0][2]+state->sorting_state.world[0][1]*state->sorting_state.view[1][2]+state->sorting_state.world[0][2]*state->sorting_state.view[2][2]+state->sorting_state.world[0][3]*state->sorting_state.view[3][2])*bounding_sphere.Center.X+
        (state->sorting_state.world[1][0]*state->sorting_state.view[0][2]+state->sorting_state.world[1][1]*state->sorting_state.view[1][2]+state->sorting_state.world[1][2]*state->sorting_state.view[2][2]+state->sorting_state.world[1][3]*state->sorting_state.view[3][2])*bounding_sphere.Center.Y+
        (state->sorting_state.world[2][0]*state->sorting_state.view[0][2]+state->sorting_state.world[2][1]*state->sorting_state.view[1][2]+state->sorting_state.world[2][2]*state->sorting_state.view[2][2]+state->sorting_state.world[2][3]*state->sorting_state.view[3][2])*bounding_sphere.Center.Z+
        (state->sorting_state.world[3][0]*state->sorting_state.view[0][2]+state->sorting_state.world[3][1]*state->sorting_state.view[1][2]+state->sorting_state.world[3][2]*state->sorting_state.view[2][2]+state->sorting_state.world[3][3]*state->sorting_state.view[3][2]);
	state->transformed_center=transformed_z;

	
	/// @todo lorenzen sez use a bucket sort here... and stop copying so much data so many times

	SortingNodeStruct* node=sorted_list.Head();
	while (node) {
		if (state->transformed_center>node->transformed_center) {
			if (sorted_list.Head()==sorted_list.Tail())
				sorted_list.Add_Head(state);
			else
				state->Insert_Before(node);
			break;
		}
		node=node->Succ();
	}
	if (!node) sorted_list.Add_Tail(state);

}
