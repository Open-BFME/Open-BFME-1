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

/* $Header: /Commando/Code/ww3d2/motchan.h 5     11/29/01 1:07p Jani_p $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/motchan.h                              $* 
 *                                                                                             * 
 *                      $Author:: Jani_p                                                      $* 
 *                                                                                             * 
 *                     $Modtime:: 11/28/01 5:43p                                              $* 
 *                                                                                             * 
 *                    $Revision:: 5                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MOTCHAN_H
#define MOTCHAN_H

#include "always.h"
#include "bittype.h"
#include "w3d_file.h"
#include "quat.h"

class ChunkLoadClass;
class Quaternion;

/******************************************************************************

	MotionChannelClass is used to store motion.  Motion data
	is broken into separate channels for X, Y, Z, and orientation.
	Then if any of the channels are empty, they don't have to be stored.
	The X,Y,Z channels all contain one-dimensional vectors and the
	orientation channel contains four-dimensional vectors (quaternions).

******************************************************************************/

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/motchan.h
class MotionChannelClass : public W3DMPO
{
	// BFME does not pool these two: ~NodeMotionStruct deletes every channel
	// through plain operator delete (0x00881EB0, one argument), where the glue
	// would route through getClassMemoryPool. W3DMPO itself is empty, so the
	// base stays and nothing moves.

public:
	// No Do_Data_Compression and no CompressedData: HRawAnimClass::read_channel
	// allocates the class with push 0x20 (0x00959AF6), eight dwords, which is
	// PivotIdx, Type, VectorLen, ValueOffset, ValueScale, Data, FirstFrame and
	// LastFrame with nothing left over.
	void Get_Vector(int frame,float * setvec) const;

	MotionChannelClass(void);
	~MotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);		
	WWINLINE int Get_Type(void) const { return Type; }
	WWINLINE int Get_Pivot(void) const { return PivotIdx; }
	WWINLINE void Set_Pivot(int idx) { PivotIdx=idx; }

#define SPECIAL_GETVEC_AS_QUAT
#ifdef SPECIAL_GETVEC_AS_QUAT
	WWINLINE void Get_Vector_As_Quat(int frame, Quaternion& quat) const;
#endif

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector

	float		ValueOffset;
	float		ValueScale;

	float	*	Data;					// pointer to the raw floating point data
	int		FirstFrame;			// first frame which was non-identity
	int		LastFrame;			// last frame which was non-identity
	void Free(void);
	WWINLINE void set_identity(float * setvec) const;

//	friend class HRawAnimClass;

};

WWINLINE void MotionChannelClass::set_identity(float * setvec) const
{
	if (Type == ANIM_CHANNEL_Q) {

		setvec[0] = 0.0f;
		setvec[1] = 0.0f;
		setvec[2] = 0.0f;
		setvec[3] = 1.0f;

	} else {

		setvec[0] = 0.0f;

	}
}

WWINLINE void	MotionChannelClass::Get_Vector(int frame,float * setvec) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		set_identity(setvec);

	} else {
	
		int vframe = frame - FirstFrame;

		for (int i=0; i<VectorLen; i++) {
			setvec[i] = Data[vframe * VectorLen + i];
		}
	}
}

#ifdef SPECIAL_GETVEC_AS_QUAT
WWINLINE void MotionChannelClass::Get_Vector_As_Quat(int frame, Quaternion& quat) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		quat.Set(0.0f, 0.0f, 0.0f, 1.0f);

	} else {
	
		const float* d = &Data[(frame - FirstFrame) * VectorLen];
		quat.Set(d[0], d[1], d[2], d[3]);

	}
}
#endif


/******************************************************************************

	BitChannelClass is used to store a boolean "on/off" value for each frame
	in an animation.  

******************************************************************************/

class BitChannelClass : public W3DMPO
{
	// BFME does not pool these two: ~NodeMotionStruct deletes every channel
	// through plain operator delete (0x00881EB0, one argument), where the glue
	// would route through getClassMemoryPool. W3DMPO itself is empty, so the
	// base stays and nothing moves.

public:

	BitChannelClass(void);
	~BitChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	WWINLINE int	Get_Type(void) const { return Type; }
	WWINLINE int	Get_Pivot(void) const { return PivotIdx; }
	WWINLINE int	Get_Bit(int frame) const;

private:

	uint32	PivotIdx;
	uint32	Type;
	int		DefaultVal;
	int		FirstFrame;
	int		LastFrame;

	uint8 *	Bits;

	void Free(void);

	friend class HRawAnimClass;
};


WWINLINE int BitChannelClass::Get_Bit(int frame) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		return DefaultVal;

	} else {
	
		int bit = frame - FirstFrame;

		uint8 mask = (uint8)(1 << (bit % 8));
		return ((*(Bits + (bit/8)) & mask) != 0);
		
	}
}

/******************************************************************************

	TimeCodedMotionChannelClass is used to store motion.  Motion data
	is broken into separate channels for X, Y, Z, and orientation.
	Then if any of the channels are empty, they don't have to be stored.
	The X,Y,Z channels all contain one-dimensional vectors and the
	orientation channel contains four-dimensional vectors (quaternions).

******************************************************************************/

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/motchan.h
class TimeCodedMotionChannelClass : public W3DMPO
{
	// Not pooled, on the same evidence as MotionChannelClass above: the unpooled
	// ??_G is 30 bytes and retail's are 30, where the glue makes ours 36.

public:

	TimeCodedMotionChannelClass(void);
	~TimeCodedMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);		
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);

	Quaternion Get_QuatVector(float32 frame);

	int		Get_Channel_Memory_Usage(void);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	PacketSize;			// size of each packet
	
	uint32	NumTimeCodes;		// Number of packets

	// BFME has no LastTimeCodeIdx: ~TimeCodedMotionChannelClass (0x00978180)
	// frees [esi+0x18] and Get_Vector (0x009781A0) reads +0xc, +0x10, +0x14 and
	// +0x18, which is PacketSize, NumTimeCodes, CachedIdx and Data with this
	// cached product gone. binary_search_index recomputes it instead.
	uint32	CachedIdx;			// Last Index Used
  
	uint32	*	Data;			 	// pointer to packet data

	void 		Free(void);
	void 		set_identity(float * setvec);
	// WWINLINE, defined below: retail folds the whole index search into
	// Get_Vector (0x009781A0), which makes exactly one call and that is the
	// float-to-integer conversion at 0x009F6E38.
	WWINLINE uint32	get_index(uint32 timecode);
	WWINLINE uint32	binary_search_index(uint32 timecode);

	friend class HCompressedAnimClass;
};

WWINLINE uint32 TimeCodedMotionChannelClass::binary_search_index(uint32 timecode)
{	
	int leftIdx = 0;
	int rightIdx = NumTimeCodes - 2;
	int dx;
	uint32 time;
	int idx;

	// No special case for the last packet: retail's search path (the fall-through
	// of the jae at 0x0097821B) sets leftIdx and rightIdx and drops straight into
	// the loop. get_index has already handled the last packet by the time it gets
	// here, and keeping the test gave (NumTimeCodes-1)*PacketSize a third use,
	// which made MSVC hoist it above the branch where retail computes it inside.

	for (;;) {
	
		dx = rightIdx - leftIdx;

		dx>>=1;	// divide by 2

		dx += leftIdx;

		idx = dx * PacketSize;

		time = Data[idx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;

		if (timecode < time) {
			rightIdx = dx;
			continue;
		}

		time = Data[idx + PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;

		if (timecode < time) return(idx); 

		if (leftIdx ^ dx) {
			leftIdx = dx;
			continue;
		}

		//
		// if leftIdx == dx prior to assignment, then leftIdx is stuck.
		//

		leftIdx++;

	}

	assert(0);
	return(0);

}	// binary_search_index

WWINLINE uint32 TimeCodedMotionChannelClass::get_index(uint32 timecode)
{	
	assert(CachedIdx <= LastTimeCodeIdx);

	uint32	time;

	time = Data[CachedIdx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;

	if (timecode >= time) {
		// possibly in the current packet

		// special case for end packets
		if (CachedIdx == (NumTimeCodes-1) * PacketSize) return(CachedIdx);
		time = Data[CachedIdx + PacketSize]	& ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;
		if (timecode < time) return(CachedIdx);

		// Do one time look-ahead before reverting to a search
		CachedIdx+=PacketSize;
		if (CachedIdx == (NumTimeCodes-1) * PacketSize) return(CachedIdx);
		time = Data[CachedIdx + PacketSize]	& ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG;
		if (timecode < time) return(CachedIdx);
	}

	CachedIdx = binary_search_index( timecode );

	return(CachedIdx);

}	// get_index

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/motchan.h
class AdaptiveDeltaMotionChannelClass : public W3DMPO
{
	// Not pooled, on the same evidence as MotionChannelClass above: the unpooled
	// ??_G is 30 bytes and retail's are 30, where the glue makes ours 36.

public:

	AdaptiveDeltaMotionChannelClass(void);
	~AdaptiveDeltaMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);		
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);

	Quaternion Get_QuatVector(float32 frame);

	int		Get_Channel_Memory_Usage(void);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	
	uint32	NumFrames;			// Number of frames

	// BFME has one more dword here, and Scale is the second of the two, not the
	// first: decompress @0x00977F53 multiplies the filter by this+0x14.
	// The destructor and getframe evidence that put a hole here in the first
	// place is unaffected - ~AdaptiveDeltaMotionChannelClass (0x009783C0) frees
	// [esi+0x18] and [esi+0x20], and getframe reads +0xc, +0x1c and +0x20 - since
	// only the order of these two dwords changes, not the size.
	float		_bfme_adm_scale2;
	float		Scale;				// Scale Filter, this much

	uint32  *Data;				 	// pointer to packet data

	uint32	CacheFrame;
	float	  *CacheData;			// the data for CachedFrame, and CachedFrame+1, x VectorLen

	void 		Free(void);

	float		getframe(uint32 frame_idx, uint32 vector_idx=0);
   void		decompress(uint32 frame_idx, float *outdata);
   void		decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata);

	friend class HCompressedAnimClass;
};



/******************************************************************************

	TimeCodedBitChannelClass is used to store a boolean "on/off" value for each frame
	in an animation.  

******************************************************************************/

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/motchan.h
class TimeCodedBitChannelClass : public W3DMPO
{
	// Not pooled, on the same evidence as MotionChannelClass above: the unpooled
	// ??_G is 30 bytes and retail's are 30, where the glue makes ours 36.

public:

	TimeCodedBitChannelClass(void);
	~TimeCodedBitChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	int	Get_Bit(int frame);

	int		Get_Channel_Memory_Usage(void);

private:

	uint32	PivotIdx;
	uint32	Type;
	int		DefaultVal;
	
	uint32	NumTimeCodes;
	uint32	CachedIdx;

	uint32	*Bits;

	void Free(void);

	friend class HCompressedAnimClass;
};


#endif
