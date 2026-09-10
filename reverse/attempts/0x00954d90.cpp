// ?Combo_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimComboClass@@@Z
// partial score=0.88 date=2026-09-09
/***********************************************************************************************
 * HTreeClass::Combo_Update -- compute each pivot's transform using an anim combo              *
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
void HTreeClass::Combo_Update
(
	const Matrix3D & root,
	HAnimComboClass *anim
)
{
	PivotClass *pivot;
	Matrix3D mtx;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;
	
	int num_anim_pivots = 100000;
	for ( int anim_num = 0; anim_num < anim->Get_Num_Anims(); anim_num++ ) {
		num_anim_pivots = MIN( num_anim_pivots, anim->Peek_Motion( anim_num )->Get_Num_Pivots() );
	}
	if ( num_anim_pivots == 100000 ) {
		num_anim_pivots = 0;
	}

	for (int piv_idx=1; piv_idx < NumPivots; piv_idx++) {
		
		pivot = &Pivot[piv_idx];
		assert(pivot->Parent != NULL);
		// Multiply(), not mul(): unlike Blend_Update, retail calls this one here
		// (call 0x008D80C0 at 0x00954E99), so the out-of-line spelling is right.
		Matrix3D::Multiply(pivot->Parent->Transform,pivot->BaseTransform,&(pivot->Transform));
		
		if (piv_idx < num_anim_pivots) {

#define	ASSUME_NORMALIZED_ANIM_COMBO_WEIGHTS

			Vector3 trans(0,0,0);
			Quaternion q0;
			Quaternion q1;
#ifndef ASSUME_NORMALIZED_ANIM_COMBO_WEIGHTS
			float	last_weight = 0;
#endif
			float	weight_total = 0;
			int wcount = 0;

			for ( int anim_num = 0; anim_num < anim->Get_Num_Anims(); anim_num++ ) {

				HAnimClass *motion = anim->Get_Motion( anim_num );

				if ( motion != NULL ) {

					float frame_num = anim->Get_Frame( anim_num );

					PivotMapClass * pivot_map = anim->Get_Pivot_Weight_Map( anim_num );

					//float	*pivot_map = anim->Get_Pivot_Weight_Map( anim_num );

					float	weight = anim->Get_Weight( anim_num );

					if ( pivot_map != NULL ) {
						weight *= (*pivot_map)[piv_idx];
						// GREG - Pivot maps are ref counted so shouldn't we
						// release the rivot map here?
						pivot_map->Release_Ref();
					}

					if ( weight != 0.0 ) {

						wcount++;
						Vector3 temp_trans;
						motion->Get_Translation( temp_trans, piv_idx, frame_num );
						trans += weight * ScaleFactor * temp_trans;
						weight_total += weight;

#ifdef ASSUME_NORMALIZED_ANIM_COMBO_WEIGHTS
						// BFME: Get_Orientation reports whether the animation has a
						// rotation for this pivot, and an absent one contributes an
						// identity to the slerp rather than being skipped.
						if ( !motion->Get_Orientation(q1,piv_idx, frame_num ) ) {
							q1.Make_Identity();
						}
						if ( wcount == 1 ) {
							q0 = q1;
						} else {
							Fast_Slerp(q0, q0, q1, weight / weight_total );
						}
#else
						q0 = q1;	
						motion->Get_Orientation(q1, piv_idx, frame_num );
						last_weight = weight;
#endif
					}

					motion->Release_Ref();

				}
			}

#ifdef ASSUME_NORMALIZED_ANIM_COMBO_WEIGHTS

			if (weight_total != 0.0f ) {
				// SKB: Removed assert because I have a case where I don't want normalization.
				// 	  One anim moves X, the other moves Y.  Assert was just in to warn programmers.	
//				WWASSERT(WWMath::Fabs( weight_total - 1.0 ) < WWMATH_EPSILON);

				pivot->Transform.Translate(trans);
#ifdef ALLOW_TEMPORARIES
				pivot->Transform = pivot->Transform * Build_Matrix3D(q0);
#else
				pivot->Transform.postMul(Build_Matrix3D(q0,mtx));
#endif
			}
#else
			if (( weight_total != 0.0f ) && (wcount >= 2)) {
			
				pivot->Transform.Translate( trans / weight_total );
				Quaternion q = Slerp_( q0, q1, last_weight / weight_total );
				pivot->Transform = pivot->Transform * Build_Matrix3D(q);

			} else if (weight_total != 0.0f) {

				pivot->Transform.Translate( trans / weight_total );
				pivot->Transform = pivot->Transform * Build_Matrix3D(q1);
			}
#endif

			pivot->IsVisible = false;

			// BFME sums each contributing animation's fade alongside the visibility
			// and averages it once the loop ends.
			pivot->PivotFade = 0.0f;
			float fade_count = 0.0f;

			for ( anim_num = 0; (anim_num < anim->Get_Num_Anims()) && (!pivot->IsVisible); anim_num++ ) {
				HAnimClass *motion = anim->Get_Motion( anim_num );
				if ( motion != NULL ) {
					float frame_num = anim->Get_Frame( anim_num );

					pivot->IsVisible |= motion->Get_Visibility(piv_idx,frame_num);
					pivot->PivotFade += motion->_bfme_hanim_fade(piv_idx,frame_num);
					fade_count += 1.0f;

					motion->Release_Ref();
				}
			}

			// Greater-than, not non-zero: retail compares with an ordered fcomp and
			// tests ah against 0x41, which is the <= arm being skipped.
			if (fade_count > 0.0f) {
				pivot->PivotFade /= fade_count;
			}
		}

		if (pivot->Is_Captured()) 
		{
			pivot->Capture_Update();
			pivot->IsVisible = true;
		}
	}
}						 


/***********************************************************************************************

