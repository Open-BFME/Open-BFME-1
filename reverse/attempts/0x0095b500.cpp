// ?Get_QuatVector@TimeCodedMotionChannelClass@@QAE?AVQuaternion@@M@Z
// partial score=0.90 date=2026-09-11
// Fits into Code/Libraries/Source/WWVegas/WW3D2/motchan.cpp, replacing the
// present-unmatched TimeCodedMotionChannelClass::Get_QuatVector body there
// (class/member declarations already in motchan.h; W3D_TIMECODED_BINARY_MOVEMENT_FLAG
// and Fast_Slerp come from the existing includes).
//
// probe.py: ours=367B retail=374B, 317 non-reloc diffs, first at +2.
// Ruled out vs the prior 0.9 stash (author gpt-5/gpt-5.6-luna, ours=363-366B,
// 315-316 diffs):
//   - The tail check "pidx == ((NumTimeCodes - 1) * PacketSize)" (copied from
//     the MATCHED sibling Get_Vector, 0x009781A0) is WRONG for this function.
//     Retail's disassembly for Get_QuatVector re-reads the CachedIdx member
//     directly at that point ("cmp ecx, dword ptr [ebp+0x14]", offset 0x14 =
//     CachedIdx) with no imul anywhere nearby. So the correct source is
//     "if (pidx == CachedIdx)", not a recomputed product. This is a real,
//     confirmed shape fact (not a guess): Get_Vector and Get_QuatVector use
//     two different spellings of the same "last packet" test.
//   - Declaring "uint32 *data = Data;" as the FIRST local (before tc0) gets
//     MSVC to load Data into esi immediately after capturing `this`, matching
//     retail's instruction order through +000c exactly (push esi; mov esi,
//     [ebp+0x18]). Without this local the Data load is deferred until after
//     the __ftol2 call and diverges from byte 0x000c on.
// Still unresolved: retail's prologue eagerly pushes FOUR callee-saved
// registers (ebx, ebp, esi, edi) and keeps tc0 in ebx permanently, spilling
// the freshly-loaded Data pointer (esi) AND `this` (ebp) to stack slots
// ([esp+0x14], [esp+0x18]) *before* the __ftol2 call, even though nothing
// clobbers esi/ebp across that call. Every source variant tried here (this
// one, the direct-cast return-Quaternion version, hoisting leftIdx/rightIdx
// to function scope) instead lets the compiler shrink-wrap: it defers the
// push of the loop-only register (whichever one lands on leftIdx) into the
// taken branch, and keeps tc0 in edi rather than ebx. That single scheduling
// difference cascades into a totally different register assignment for the
// rest of the body (matches Get_Vector's own algorithm one-for-one but does
// not reproduce retail's push/spill schedule). Landing this needs whatever
// source shape makes MSVC treat the Data pointer and `this` as always-spilled
// before the truncation call, not just the CachedIdx tail fix above.
Quaternion TimeCodedMotionChannelClass::Get_QuatVector(float32 frame)
{
	assert(VectorLen == 4);
	uint32 *data = Data;
	uint32 tc0 = (uint32)(int)frame;
	uint32 pidx;
	if (tc0 < (data[CachedIdx] & 0x7FFFFFFF))
	{
		int rightIdx = (int)NumTimeCodes;
		int leftIdx = 0;
		rightIdx -= 2;
		for (;;)
		{
			int mid = (leftIdx + rightIdx) / 2;
			uint32 *pkt = data + mid * (int)PacketSize;
			uint32 t0 = *pkt;
			if (tc0 < (t0 & 0x7FFFFFFF))
			{
				rightIdx = mid;
				continue;
			}
			if (tc0 < (pkt[PacketSize] & 0x7FFFFFFF))
			{
				pidx = (uint32)(pkt - data);
				break;
			}
			if (leftIdx ^ mid)
			{
				leftIdx = mid;
				continue;
			}
			leftIdx++;
		}
	}
	else
		pidx = CachedIdx;

	if (pidx == CachedIdx)
	{
		float32 *vec = (float32 *)&data[pidx + 1];
		return Quaternion(vec[0], vec[1], vec[2], vec[3]);
	}

	uint32 p2idx = pidx + PacketSize;
	uint32 time = data[p2idx];
	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG)
	{
		float32 *vec = (float32 *)&data[pidx + 1];
		return Quaternion(vec[0], vec[1], vec[2], vec[3]);
	}

	float32 time1 = (data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 ratio = (frame - time1) / (time2 - time1);
	float32 *frame1 = (float32 *)&data[pidx + 1];
	float32 *frame2 = (float32 *)&data[p2idx + 1];
	Quaternion q;
	Fast_Slerp(q, *(Quaternion *)frame1, *(Quaternion *)frame2, ratio);
	return q;
} // Get_QuatVector
