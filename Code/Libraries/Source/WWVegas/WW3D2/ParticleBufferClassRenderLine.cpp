// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#include "part_buf.h"
#include "part_emt.h"
#include "ww3d.h"
#include "rinfo.h"
#include "scene.h"
#include "camera.h"
#include "predlod.h"
#include "pot.h"
#include "bound.h"
#include "simplevec.h"
#include "sphere.h"
#include "wwprofile.h"
#include <limits.h>
#include "vp.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vector3.h"


// Inlined context from part_buf.cpp; emitted copy already has its own owner.
inline int ParticleBufferClass::Is_Freeze_Random(void) const
{
	if (LineRenderer != NULL) {
		return LineRenderer->Is_Freeze_Random();
	}
	return false;
}
// ParticleBufferClass::Render_Line, retail 0x0098AD00, 1763 bytes.
// /EHsc is intentional: the default /EHsc- treats extern-C atexit as throwing
// and adds EH states 0/2/4 around the local-static vector registrations. State
// 2 then induces a function-wide EBX constant-2 allocation, obscuring the root
// cause as register/CSE drift. Retail omits those state writes. /EHsc matches
// both the registrations and the entire body without barriers or forced locals.
void ParticleBufferClass::Render_Line(RenderInfoClass & rinfo)
{

	LineRenderer->Set_Freeze_Random(Is_Freeze_Random());

	int pingpong = 0;
	if (PingPongPosition) {
		pingpong = WW3D::Get_Frame_Count() & 0x1;
	}

	static SimpleDynVecClass<Vector3> tmp_points;
	static SimpleDynVecClass<Vector4> tmp_diffuse;
	static SimpleDynVecClass<unsigned char> tmp_id;

	Vector3 * positions = Position[pingpong]->Get_Array();
	Vector4 * diffuse = 0;
	Vector4 default_diffuse(0, 0, 0, 0);
	unsigned char *ids = GroupID->Get_Array();
	Combine_Color_And_Alpha();
	if (Diffuse) {
		diffuse = Diffuse->Get_Array();
	} else {
		default_diffuse.Set(ColorKeyFrameValues[0].X, ColorKeyFrameValues[0].Y, ColorKeyFrameValues[0].Z,
								  AlphaKeyFrameValues[0]);
	}

	unsigned int sub1_end;
	unsigned int sub2_start;
	unsigned int i;

	if ((Start < End) || ((Start == End) && NonNewNum ==0)) {
		sub1_end = End;
		sub2_start = End;
	} else {
		sub1_end = MaxNum;
		sub2_start = 0;
	}

	tmp_points.Delete_All(false);
	tmp_diffuse.Delete_All(false);
	tmp_id.Delete_All(false);

	Vector4 *last_color = &default_diffuse;
	unsigned char last_id = 0;

	for (i = Start; i < sub1_end; i++) {
		if (PermutationArray[i & 0xF] >= DecimationThreshold) {
			tmp_points.Add(positions[i]);
			last_color = diffuse ? &diffuse[i] : &default_diffuse;
			tmp_diffuse.Add(*last_color);
			last_id = ids[i];
			tmp_id.Add(last_id);
		}
	}

	for (i = sub2_start; i < End; i++) {
		if (PermutationArray[i & 0xF] >= DecimationThreshold) {
			tmp_points.Add(positions[i]);
			last_color = diffuse ? &diffuse[i] : &default_diffuse;
			tmp_diffuse.Add(*last_color);
			last_id = ids[i];
			tmp_id.Add(last_id);
		}
	}

	if (Emitter && !Emitter->Is_Stopped() && (last_id == CurrentGroupID)) {
		tmp_points.Add(Emitter->Get_Position());
		tmp_diffuse.Add(*last_color);
		tmp_id.Add(last_id);
	}

	if (tmp_points.Count() > 0) {
		SphereClass bounding_sphere;
		Get_Obj_Space_Bounding_Sphere(bounding_sphere);

		int count = tmp_points.Count();
		int start = 0;
		int end = 0;

		while (end < count) {
			while ( (end < count) && (tmp_id[start] == tmp_id[end])) {
				end++;
			}

			if (end - start > 1) {
				LineRenderer->Render(rinfo,
											Transform,
											end - start,
											&(tmp_points[start]),
											bounding_sphere,
											&(tmp_diffuse[start]));
			}
			start = end;
		}
	}
}
