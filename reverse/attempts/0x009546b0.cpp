// ?Blend_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimClass@@M1MM@Z
// partial score=0.95 date=2026-09-09
/***********************************************************************************************
 * HTreeClass::Blend_Update -- computes each pivot as a blend of two anims                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/4/98     GTH : Created.                                                                 *
 *=============================================================================================*/
void HTreeClass::Blend_Update
(
	const Matrix3D &					root,
	HAnimClass *						motion0,
	float									frame0,
	HAnimClass *						motion1,
	float									frame1,
	float									percentage		// 0.0 = motion0.  1.0 = motion1
)
{
	PivotClass *pivot;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int num_anim_pivots = MIN( motion0->Get_Num_Pivots (), motion1->Get_Num_Pivots () );

	for (int piv_idx=1; piv_idx < NumPivots; piv_idx++) {

		pivot = &Pivot[piv_idx];

		assert(pivot->Parent != NULL);
		// mul() rather than Multiply(): the first is WWINLINE and the second is not,
		// which is how retail ends up with the base-pose multiply inlined here and
		// called from Anim_Update.
		pivot->Transform.mul(pivot->Parent->Transform,pivot->BaseTransform);

		if (piv_idx < num_anim_pivots) {
			// interpolated translation
			Vector3 trans0;
			motion0->Get_Translation(trans0,piv_idx,frame0);
			Vector3 trans1;
			motion1->Get_Translation(trans1,piv_idx,frame1);
			Vector3 lerped = (1.0 - percentage) * trans0 + (percentage) * trans1;
			pivot->Transform.Translate(lerped * ScaleFactor);

			// Interpolated rotation. BFME asks each animation whether it has any
			// rotation for this pivot and skips the blend entirely when neither
			// does; when only one does, the other contributes identity.
			Quaternion q0;
			bool got0 = motion0->Get_Orientation(q0,piv_idx,frame0);
			Quaternion q1;
			bool got1 = motion1->Get_Orientation(q1,piv_idx,frame1);

			if (got0 || got1) {
				if (!got0) q0.Make_Identity();
				if (!got1) q1.Make_Identity();

				Quaternion q;
				Fast_Slerp(q,q0,q1,percentage);
				Matrix3D mtx;
				::Build_Matrix3D(q,mtx);
				pivot->Transform.postMul(mtx);
			}

			pivot->IsVisible = (motion0->Get_Visibility(piv_idx,frame0) || motion1->Get_Visibility(piv_idx,frame1));

			// BFME blends the two fades the same way it blends the pose. The second
			// animation is read first: retail calls through motion1 before motion0
			// and keeps both results on the x87 stack rather than spilling one.
			float fade1 = motion1->_bfme_hanim_fade(piv_idx,frame1);
			float fade0 = motion0->_bfme_hanim_fade(piv_idx,frame0);
			pivot->PivotFade = fade0 + (fade1 - fade0) * percentage;
		}

		if (pivot->Is_Captured())
		{
			pivot->Capture_Update();
			pivot->IsVisible = true;
		}
	}
}

