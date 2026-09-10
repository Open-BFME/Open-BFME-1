// ?Get_Orientation@HCompressedAnimClass@@UBE_NAAVQuaternion@@HM@Z
// partial score=0.76 date=2026-09-09
bool HCompressedAnimClass::Get_Orientation(Quaternion& q, int pividx,float frame) const
{
	bool has_rotation = false;

	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED: {
			TimeCodedMotionChannelClass * qchan = NodeMotion[pividx].tc.Q;
			if (qchan) {
				Quaternion result;
				uint32 tc0 = frame;
				uint32 pidx;
				uint32 * data = qchan->Data;
				if (tc0 < (data[qchan->CachedIdx] & 0x7FFFFFFF)) {
					int rightIdx = (int)qchan->NumTimeCodes;
					int leftIdx = 0;
					rightIdx -= 2;
					for (;;) {
						int mid = (leftIdx + rightIdx) / 2;
						uint32 * pkt = data + mid * (int)qchan->PacketSize;
						uint32 t0 = *pkt;
						if (tc0 < (t0 & 0x7FFFFFFF)) {
							rightIdx = mid;
							continue;
						}
						if (tc0 < (pkt[qchan->PacketSize] & 0x7FFFFFFF)) {
							pidx = (uint32)(pkt - data);
							break;
						}
						if (leftIdx ^ mid) {
							leftIdx = mid;
							continue;
						}
						leftIdx++;
					}
				} else {
					pidx = qchan->CachedIdx;
				}
				uint32 p2idx;

				if (pidx == ((qchan->NumTimeCodes - 1) * qchan->PacketSize)) {
					float32 * vec = (float32 *)&data[pidx + 1];
					result.Set(vec[0], vec[1], vec[2], vec[3]);
				} else {
					p2idx = pidx + qchan->PacketSize;
					uint32 time = data[p2idx];

					if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
						float32 * vec = (float32 *)&data[pidx + 1];
						result.Set(vec[0], vec[1], vec[2], vec[3]);
					} else {
						float32 time1 = (data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
						float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
						float32 ratio = (frame - time1) / (time2 - time1);
						float32 * frame1 = (float32 *)&data[pidx + 1];
						float32 * frame2 = (float32 *)&data[p2idx + 1];
						Fast_Slerp(result, *(Quaternion *)frame1, *(Quaternion *)frame2, ratio);
					}
				}

				q = result;
				has_rotation = true;
			}
			break;
		}
		case ANIM_FLAVOR_ADAPTIVE_DELTA: {
			AdaptiveDeltaMotionChannelClass * qchan = NodeMotion[pividx].ad.Q;
			if (qchan) {
				q = qchan->Get_QuatVector(frame);
				has_rotation = true;
			}
			break;
		}
		default:
			WWASSERT(0); // unknown flavor
			break;
	}
	return has_rotation;
}
