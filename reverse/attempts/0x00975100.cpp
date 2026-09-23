// ?Render@BfmeThingVGX@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAMABVSphereClass@@@Z
// partial score=0.19786150712830952 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /DWIN32 /D_WINDOWS

// Source-derived BFME port of ZH streakRender.cpp, GPL-3.0-or-later.
// Retail 00975100..0097775B, 9820B; Bitmap2D caller proves signature.
// Fixed chunks, no subdivision or merging, 36-byte intersections and stack vertices.
#include "winbase_shim.h"
#include "rinfo.h"
#include "ww3d.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
static __forceinline float Rva00975100Clamp(float v) {
    if (v<=0.0f) return 0.0f;
    if (v>1.0f) return 1.0f;
    return v;
}
static __forceinline unsigned Rva00975100Color(const Vector4 &color) {
    Vector4 c=color;
    if (!CPUDetectClass::Has_CMOV_Instruction()) {
        c.X=Rva00975100Clamp(c.X); c.Y=Rva00975100Clamp(c.Y);
        c.Z=Rva00975100Clamp(c.Z); c.W=Rva00975100Clamp(c.W);
    } else DX8Wrapper::Clamp_Color(c);
    return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3&>(c),c.W);
}
class BoxDynamicVBAccessClass {
    const FVFInfoClass &FVFInfo;
    unsigned Type,FVF,Start;
    unsigned short VertexCount,VertexBufferOffset;
    class BoxVertexBufferClass *VertexBuffer;
public:
    BoxDynamicVBAccessClass(unsigned,unsigned,unsigned short,unsigned);
    ~BoxDynamicVBAccessClass();
    const FVFInfoClass &FVF_Info() const { return FVFInfo; }
    class WriteLockClass {
        BoxDynamicVBAccessClass *DynamicVBAccess; VertexFormatXYZNDUV2 *Vertices;
    public:
        WriteLockClass(BoxDynamicVBAccessClass*); ~WriteLockClass();
        VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
    };
};
void BoxSetTexture(unsigned,TextureBaseClass*&);
class ShroudFilter { public: char pad[0xc]; int m_uAddress,m_vAddress; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class BfmeThingVGX {
public:
    void Render(RenderInfoClass&,const Matrix3D&,unsigned,Vector3*,float*,const SphereClass&);
    TextureBaseClass *Texture; ShaderClass Shader; float Width;
    Vector3 Color; float Opacity; float TexSpan; bool DisableSorting;
};
#define STREAK_CHUNK_SIZE 128
#define MAX_STREAK_POINT_BUFFER_SIZE 129
#define MAX_STREAK_POLY_BUFFER_SIZE 256
void BfmeThingVGX::Render(RenderInfoClass &rinfo,const Matrix3D &transform,
    unsigned num_points,Vector3 *points,float *widths,const SphereClass &obj_sphere)
{
	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW,view);

	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);	
	DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);

	const float parallel_factor = 0.9f;

	unsigned int chunk_size = STREAK_CHUNK_SIZE + 1;
	if (chunk_size > num_points) chunk_size = num_points;

	for (unsigned int chunkIndex = 0; chunkIndex < num_points - 1; chunkIndex += (chunk_size - 1)) 
	{
		unsigned int point_cnt = num_points - chunkIndex;
		point_cnt = MIN(point_cnt, chunk_size);

		unsigned int pointIndex;	
		unsigned int segmentIndex;	
		unsigned int intersectionIndex;	

		Vector3 xformed_pts[MAX_STREAK_POINT_BUFFER_SIZE];

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
			&points[chunkIndex], modelview, point_cnt);

		float base_tex_v[MAX_STREAK_POINT_BUFFER_SIZE];
        float u_values[2] = {0.0f,1.0f};
        float last = widths[point_cnt-1] - TexSpan;
        for(pointIndex=0;pointIndex<point_cnt;++pointIndex)
            base_tex_v[pointIndex]=(widths[pointIndex]-last)/TexSpan;
        Vector3 *points=xformed_pts;
        float *tex_v=base_tex_v;
        enum SegmentEdge 
		{
			FIRST_EDGE     = 0,	
			TOP_EDGE			= 0,	
			BOTTOM_EDGE		= 1,	
			MAX_EDGE			= 1,	
			NUM_EDGES		= 2	
		};

		bool switch_edges = false;

		struct LineSegment 
		{
			Vector3	StartPlane;
			Vector3	EdgePlane[NUM_EDGES];
		};

		LineSegment segment[MAX_STREAK_POINT_BUFFER_SIZE + 1];

		struct LineSegmentIntersection  
		{
			unsigned int	PointCount;			
			unsigned int	NextSegmentID;		
			Vector3			Direction;			
			Vector3			Point;				
			float				TexV;					
		};

		float radius = Width * 0.5f; 

		LineSegmentIntersection intersection[MAX_STREAK_POINT_BUFFER_SIZE + 1][NUM_EDGES];

		for (segmentIndex = 1; segmentIndex < point_cnt; segmentIndex++) 
		{	

			Vector3 &curr_point = points[segmentIndex - 1];
			Vector3 &next_point = points[segmentIndex];
			if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
			{
				next_point.X += 0.001f;
			}

			Vector3 &segdir = segment[segmentIndex].StartPlane;
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
			segment[segmentIndex].EdgePlane[TOP_EDGE] = top_normal;

			Vector3 bottom_normal;
			Vector3::Cross_Product(segdir, bottom, &bottom_normal);
			bottom_normal.Normalize();
			segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = bottom_normal;

			if (segmentIndex > 1) 
			{

				Vector3 prev_plane;
				Vector3::Cross_Product(points[segmentIndex - 2], curr_point, &prev_plane);
				prev_plane.Normalize();

				Vector3 curr_plane;
				Vector3::Cross_Product(curr_point, next_point, &curr_plane);
				curr_plane.Normalize();

				if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) 
				{
					switch_edges = !switch_edges;
				} 
				else 
				{
				}
			}

			if (switch_edges) 
			{
				
				segment[segmentIndex].EdgePlane[TOP_EDGE] = -bottom_normal;
				segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = -top_normal;
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
		intersection[0][BOTTOM_EDGE].PointCount = 0;			
		intersection[0][BOTTOM_EDGE].NextSegmentID = 0;		
		intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);		
		intersection[0][BOTTOM_EDGE].TexV = 0.0f;				
		intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);	

		intersection[1][TOP_EDGE].PointCount = 1;
		intersection[1][TOP_EDGE].NextSegmentID = 1;
		intersection[1][TOP_EDGE].Point = points[0];
		intersection[1][TOP_EDGE].TexV = tex_v[0];
		intersection[1][BOTTOM_EDGE].PointCount = 1;
		intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
		intersection[1][BOTTOM_EDGE].Point = points[0];
		intersection[1][BOTTOM_EDGE].TexV = tex_v[0];

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
		if (dp > 0.0f) 
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
		} 
		else
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}

		segment[1].StartPlane = segment[0].StartPlane;

		unsigned int last_isec = num_intersections[TOP_EDGE]; 

		intersection[last_isec][TOP_EDGE].PointCount = 1;
		intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1; 
		intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
		intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
		intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];

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
		if (dp > 0.0f) 
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
		} 
		else 
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}

		float vdp;

		for (intersectionIndex = 2; intersectionIndex < num_intersections[TOP_EDGE]; intersectionIndex++) 
		{

			Vector3 &midpoint = points[intersectionIndex - 1];
			float mid_tex_v = tex_v[intersectionIndex - 1];

			intersection[intersectionIndex][TOP_EDGE].PointCount = 1;
			intersection[intersectionIndex][TOP_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][TOP_EDGE].Point = midpoint;

			intersection[intersectionIndex][TOP_EDGE].TexV = mid_tex_v;

			intersection[intersectionIndex][BOTTOM_EDGE].PointCount = 1;
			intersection[intersectionIndex][BOTTOM_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][BOTTOM_EDGE].Point = midpoint;

			intersection[intersectionIndex][BOTTOM_EDGE].TexV = mid_tex_v;

			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE]);
			if (fabs(vdp) < parallel_factor) 
			{

				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE],
					&(intersection[intersectionIndex][TOP_EDGE].Direction));
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][TOP_EDGE].Direction, midpoint) < 0.0f) 
				{
					intersection[intersectionIndex][TOP_EDGE].Direction = -intersection[intersectionIndex][TOP_EDGE].Direction;
				}

			} 
			else 
			{

				Vector3 pl;
				if (vdp > 0.0f) 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] + segment[intersectionIndex].EdgePlane[TOP_EDGE];
				} 
				else 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] - segment[intersectionIndex].EdgePlane[TOP_EDGE];
				}
				pl.Normalize();

				intersection[intersectionIndex][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();

			}

			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE]);
			if (fabs(vdp) < parallel_factor) 
			{

				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE],
					&(intersection[intersectionIndex][BOTTOM_EDGE].Direction));
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][BOTTOM_EDGE].Direction, midpoint) < 0.0f) 
				{
					intersection[intersectionIndex][BOTTOM_EDGE].Direction = -intersection[intersectionIndex][BOTTOM_EDGE].Direction;
				}

			} 
			else 
			{

				Vector3 pl;
				if (vdp > 0.0f) 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] + segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				} 
				else 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] - segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				}
				pl.Normalize();

				intersection[intersectionIndex][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();

			}

			Vector3::Cross_Product(intersection[intersectionIndex][TOP_EDGE].Direction, intersection[intersectionIndex][BOTTOM_EDGE].Direction, &start_pl);
			start_pl.Normalize();
			dp = Vector3::Dot_Product(segment[intersectionIndex].StartPlane, start_pl);
			if (dp > 0.0f) 
			{
				segment[intersectionIndex].StartPlane = start_pl;
			} 
			else 
			{
				segment[intersectionIndex].StartPlane = -start_pl;
			}

		}	

		unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];		
		VertexFormatXYZUV1 vertexArray[MAX_STREAK_POLY_BUFFER_SIZE];
		Vector3i v_index_array[MAX_STREAK_POLY_BUFFER_SIZE];

		unsigned int vertexIndex = 0;
		unsigned int triangleIndex = 0;

		Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
		top = top_dir * Vector3::Dot_Product(points[0], top_dir);
		Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
		bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
		vertexArray[vertexIndex].x = top.X;
		vertexArray[vertexIndex].y = top.Y;
		vertexArray[vertexIndex].z = top.Z;
		vertexArray[vertexIndex].u1 = u_values[0] ;
		vertexArray[vertexIndex].v1 = intersection[1][TOP_EDGE].TexV ;
		vertexIndex++;
		vertexArray[vertexIndex].x = bottom.X;
		vertexArray[vertexIndex].y = bottom.Y;
		vertexArray[vertexIndex].z = bottom.Z;
		vertexArray[vertexIndex].u1 = u_values[1] ;
		vertexArray[vertexIndex].v1 = intersection[1][BOTTOM_EDGE].TexV ;
		vertexIndex++;
		
		unsigned int last_top_vertexIndex = 0;
		unsigned int last_bottom_vertexIndex = 1;

		unsigned int top_int_idx = 1;		
		unsigned int bottom_int_idx = 1;	
		pointIndex = 0;
		unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
		unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;

		unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
		residual_top_points -= delta;
		residual_bottom_points -= delta;
		pointIndex += delta;

		for (; ; ) 
		{

			if (residual_top_points == 1 && residual_bottom_points == 1) 
			{
				
				v_index_array[triangleIndex].I = last_top_vertexIndex;
				v_index_array[triangleIndex].J = last_bottom_vertexIndex;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				v_index_array[triangleIndex].I = last_bottom_vertexIndex;
				v_index_array[triangleIndex].J = vertexIndex + 1;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				last_top_vertexIndex = vertexIndex;
				last_bottom_vertexIndex = vertexIndex + 1;

				top_int_idx++;
				bottom_int_idx++;
				residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
				residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;

				pointIndex++;

				Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
				top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
				Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
				bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);

				vertexArray[vertexIndex].x = top.X;
				vertexArray[vertexIndex].y = top.Y;
				vertexArray[vertexIndex].z = top.Z;
				vertexArray[vertexIndex].u1 = u_values[0] ;
				vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV ;
				vertexIndex++;
				vertexArray[vertexIndex].x = bottom.X;
				vertexArray[vertexIndex].y = bottom.Y;
				vertexArray[vertexIndex].z = bottom.Z;
				vertexArray[vertexIndex].u1 = u_values[1] ;
				vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV ;
				vertexIndex++;
			}
			else 
			{
				
				if (residual_top_points > 1) 
				{
					
					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_bottom_vertexIndex = vertexIndex;

					residual_top_points--;
					bottom_int_idx++;
					residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;

					pointIndex++;

					Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
					bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);

					vertexArray[vertexIndex].x = bottom.X;
					vertexArray[vertexIndex].y = bottom.Y;
					vertexArray[vertexIndex].z = bottom.Z;
					vertexArray[vertexIndex].u1 = u_values[1] ;
					vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV ;					
					vertexIndex++;
				}
				else 
				{

					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_top_vertexIndex = vertexIndex;

					residual_bottom_points--;
					top_int_idx++;
					residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;

					pointIndex++;

					Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
					top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
					vertexArray[vertexIndex].x = top.X;
					vertexArray[vertexIndex].y = top.Y;
					vertexArray[vertexIndex].z = top.Z;
					vertexArray[vertexIndex].u1 = u_values[0] ;
					vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV ;
					vertexIndex++;
				}
			}

			delta = MIN(residual_top_points, residual_bottom_points) - 1;
			residual_top_points -= delta;
			residual_bottom_points -= delta;
			pointIndex += delta;
			
			if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
					(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) 
			{

				assert(top_int_idx == num_intersections[TOP_EDGE]);
				assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
				assert(pointIndex == point_cnt - 1);
				break;
			}
		}		

		bool sorting = (!DisableSorting) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
		
		ShaderClass shader = Shader;
		shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
		shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);			

		VertexMaterialClass *mat;		
		mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(mat);
		REF_PTR_RELEASE(mat);

		if (Texture) 
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);			
		} 
		else 
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
		}

		BoxDynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),5,vnum,0);
		
		{
			BoxDynamicVBAccessClass::WriteLockClass Lock(&Verts);
			unsigned int i;
			unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();			
			const FVFInfoClass& fvfinfo=Verts.FVF_Info();			
			int segIdx = 0;

			unsigned int oddEven = 0;

			const unsigned verticesOffset = fvfinfo.Get_Location_Offset();
			const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
			const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
			const unsigned vbSize = fvfinfo.Get_FVF_Size();
            unsigned int argb = Rva00975100Color(Vector4(Color.X,Color.Y,Color.Z,1.0f));

			for (i=0; i<vnum; i++)
			{
				Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
				vertex->X = vertexArray[i].x;
				vertex->Y = vertexArray[i].y;
				vertex->Z = vertexArray[i].z;
				*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = argb; 
				Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
				texture->U = vertexArray[i].u1;
				texture->V = vertexArray[i].v1;
				vb += vbSize;				
			}			
		} 
		
		DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),triangleIndex*3);
		{
			unsigned int i;
			DynamicIBAccessClass::WriteLockClass lock(&ib_access);
			unsigned short* inds=lock.Get_Index_Array();

			for (i=0; i<triangleIndex; i++)
			{
				*inds++=v_index_array[i].I;
				*inds++=v_index_array[i].J;
				*inds++=v_index_array[i].K;
			}
			
		}

		((ShroudTexture*)&Texture)->getFilter()->m_uAddress=1;
        ((ShroudTexture*)&Texture)->getFilter()->m_vAddress=1;
        DX8Wrapper::Set_Index_Buffer(ib_access,0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass*>(&Verts));				
		BoxSetTexture(0,Texture);
		DX8Wrapper::Set_Shader(shader);

		if (sorting) 
		{	
			SortingRendererClass::Insert_Triangles(obj_sphere,0,triangleIndex,0,vnum);
		} 
		else 
		{
			DX8Wrapper::Draw_Triangles(0,triangleIndex,0,vnum);
		}
		
	}	

	DX8Wrapper::Set_Transform(D3DTS_VIEW,view);

}
