// ?Render_Line@ParticleBufferClass@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.88 date=2026-09-02
// banked ZH Render_Line for 0x0098AD00
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


