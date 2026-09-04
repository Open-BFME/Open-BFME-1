// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
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

/* $Header: /Commando/Code/ww3d2/hcanim.cpp 3     6/29/01 6:41p Jani_p $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hcanim.cpp                             $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 6/27/01 7:50p                                               $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   NodeMotionStruct::NodeMotionStruct -- constructor                                         *
 *   NodeMotionStruct::~NodeMotionStruct -- destructor                                         *
 *   HCompressedAnimClass::HCompressedAnimClass -- constructor                                 * 
 *   HCompressedAnimClass::~HCompressedAnimClass -- Destructor                                 * 
 *   HCompressedAnimClass::Free -- De-allocates all memory in use                              * 
 *   HCompressedAnimClass::Load -- Loads hierarchy animation from a file                       * 
 *   HCompressedAnimClass::read_channel -- Reads in a single channel of motion                 * 
 *   HCompressedAnimClass::add_channel -- Adds a motion channel to the animation               * 
 *   HCompressedAnimClass::Get_Translation -- returns the translation vector for the given fram* 
 *   HCompressedAnimClass::Get_Orientation -- returns a quaternion for the orientation of the p* 
 *   HCompressedAnimClass::read_bit_channel -- read a bit channel from the file                *
 *   HCompressedAnimClass::add_bit_channel -- install a bit channel into the animation         *
 *   HCompressedAnimClass::Get_Visibility -- return visibility state for given pivot/frame     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "hcanim.h"
#include "assetmgr.h"

// BFME reaches the hierarchy through a free function, as HRawAnimClass::Load_W3D
// does -- cdecl, one argument, caller cleans -- rather than through the asset
// manager singleton. The body lives in another translation unit.
HTreeClass *Get_HTree(const char *name);
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"


struct NodeCompressedMotionStruct
{
	NodeCompressedMotionStruct();
	~NodeCompressedMotionStruct();

	void SetFlavor(int flavor)  {Flavor = flavor;}

	int Flavor;

	union {
		struct {
			TimeCodedMotionChannelClass *		X;
			TimeCodedMotionChannelClass *		Y;
			TimeCodedMotionChannelClass *		Z;
			TimeCodedMotionChannelClass *		Q;
			TimeCodedMotionChannelClass *		Fade;
		} tc;

		struct {
			AdaptiveDeltaMotionChannelClass *		X;
			AdaptiveDeltaMotionChannelClass *		Y;
			AdaptiveDeltaMotionChannelClass *		Z;
			AdaptiveDeltaMotionChannelClass *		Q;
			AdaptiveDeltaMotionChannelClass *		Fade;

		} ad;

		struct {
			 void * X;
			 void * Y;
			 void * Z;
			 void * Q;
			 void * Fade;
		} vd;
	};


	// BFME: Vis sits at +0x18 and the struct strides 0x1c (imul ...,0x1c at
	// 0x0095BA3B and 0x0095B2D7), which is one dword more than Zero Hour's. The
	// extra one is a fade channel inside the union at +0x14 -- the slot-13 getter
	// at 0x0095B260 switches on Flavor and reads [eax+0x14] in both arms.
	TimeCodedBitChannelClass *			Vis;

	int Get_Channel_Memory_Usage(void);
};

/***********************************************************************************************
 * NodeCompressedMotionStruct::NodeCompressedMotionStruct -- constructor                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
// ?NodeCompressedMotionStruct::NodeCompressedMotionStruct present-unmatched
NodeCompressedMotionStruct::NodeCompressedMotionStruct() : 
	Vis(NULL)
{
		vd.X = NULL;
		vd.Y = NULL;
		vd.Z = NULL;
		vd.Q = NULL;
		vd.Fade = NULL;
}


/***********************************************************************************************
 * NodeCompressedMotionStruct::~NodeCompressedMotionStruct -- destructor                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/23/98   GTH : Created.                                                                 *
 *   02/02/00   JGA : Compressed                                                               *
 *=============================================================================================*/
// ?NodeCompressedMotionStruct::~NodeCompressedMotionStruct present-unmatched
NodeCompressedMotionStruct::~NodeCompressedMotionStruct()
{
	// Needs to be changed to call the correct destructors

	switch (Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (tc.X) delete tc.X;
			if (tc.Y) delete tc.Y;
			if (tc.Z) delete tc.Z;
			if (tc.Q) delete tc.Q;
			if (tc.Fade) delete tc.Fade;
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (ad.X) delete ad.X;
			if (ad.Y) delete ad.Y;
			if (ad.Z) delete ad.Z;
			if (ad.Q) delete ad.Q;
			if (ad.Fade) delete ad.Fade;
			break;
		default:
			WWASSERT(0);	// unknown flavor
			break;
	}

	if (Vis) delete Vis;

}  // ~NodeCompressedMotionStruct


int NodeCompressedMotionStruct::Get_Channel_Memory_Usage(void)
{
	int size = sizeof(NodeCompressedMotionStruct);

	switch (Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (tc.X) size += tc.X->Get_Channel_Memory_Usage();
			if (tc.Y) size += tc.Y->Get_Channel_Memory_Usage();
			if (tc.Z) size += tc.Z->Get_Channel_Memory_Usage();
			if (tc.Q) size += tc.Q->Get_Channel_Memory_Usage();
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (ad.X) size += ad.X->Get_Channel_Memory_Usage();
			if (ad.Y) size += ad.Y->Get_Channel_Memory_Usage();
			if (ad.Z) size += ad.Z->Get_Channel_Memory_Usage();
			if (ad.Q) size += ad.Q->Get_Channel_Memory_Usage();
			break;
	}

	if (Vis) size += Vis->Get_Channel_Memory_Usage();

	return size;
}


/*********************************************************************************************** 
 * HCompressedAnimClass::HCompressedAnimClass -- constructor                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::HCompressedAnimClass present-unmatched
HCompressedAnimClass::HCompressedAnimClass(void) :
	NumFrames(0),
	NumNodes(0),
	Flavor(0),
	FrameRate(0),
	NodeMotion(NULL)
{
	memset(Name,0,W3D_NAME_LEN);
	memset(HierarchyName,0,W3D_NAME_LEN);
}


/*********************************************************************************************** 
 * HCompressedAnimClass::~HCompressedAnimClass -- Destructor                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::~HCompressedAnimClass present-unmatched
HCompressedAnimClass::~HCompressedAnimClass(void)
{
	Free();
}


/*********************************************************************************************** 
 * HCompressedAnimClass::Free -- De-allocates all memory in use                                * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Free present-unmatched
void HCompressedAnimClass::Free(void)
{
	if (NodeMotion != NULL) {
		delete[] NodeMotion;
	}
	// Outside the test, unlike HRawAnimClass::Free: retail's je at 0x0095C457
	// lands at 0x0095C478, ahead of the store at 0x0095C47A, so it runs on both
	// paths. Zero Hour never nulled it here at all.
	NodeMotion = NULL;
}


/*********************************************************************************************** 
 * HCompressedAnimClass::Load -- Loads hierarchy animation from a file                         * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Load_W3D present-unmatched
int HCompressedAnimClass::Load_W3D(ChunkLoadClass & cload)
{
	int i = 0;
	/* 
	** First make sure we release any memory in use
	*/
	Free();

	/*
	**	Open the first chunk, it should be the animation header
	*/
	if (!cload.Open_Chunk()) return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_COMPRESSED_ANIMATION_HEADER) {
		// ERROR: Expected Animation Header!
		return LOAD_ERROR;
	}

	W3dCompressedAnimHeaderStruct aheader;
	if (cload.Read(&aheader,sizeof(W3dAnimHeaderStruct)) != sizeof(W3dAnimHeaderStruct)) {
		return LOAD_ERROR;
	}

	cload.Close_Chunk();

	strcpy(Name,aheader.HierarchyName);
	strcat(Name,".");
	strcat(Name,aheader.Name);

	// TSS chasing crash bug 05/26/99
   WWASSERT(HierarchyName != NULL);
   WWASSERT(aheader.HierarchyName != NULL);
   WWASSERT(sizeof(HierarchyName) >= W3D_NAME_LEN);
   strncpy(HierarchyName,aheader.HierarchyName,W3D_NAME_LEN);

	HTreeClass * base_pose = Get_HTree(HierarchyName);
	if (base_pose == NULL) {
		goto Error;
	}
	NumNodes = base_pose->Num_Pivots();

	NumFrames = aheader.NumFrames;
	FrameRate = aheader.FrameRate;
	Flavor    = aheader.Flavor;
  																					
	// Just for now                                          
	WWASSERT((Flavor == ANIM_FLAVOR_TIMECODED)||(Flavor == ANIM_FLAVOR_ADAPTIVE_DELTA));

	NodeMotion = W3DNEWARRAY NodeCompressedMotionStruct[ NumNodes ];
	if (NodeMotion == NULL) {
		goto Error;
	}

	// Initialize Flavor
	for (i=0; i<NumNodes; i++) {
		NodeMotion[i].SetFlavor(Flavor);
	}

	/*
	** Now, read in all of the other chunks (motion channels).
	*/
	TimeCodedMotionChannelClass * tc_chan;
	AdaptiveDeltaMotionChannelClass * ad_chan;
	TimeCodedBitChannelClass * newbitchan;

	while (cload.Open_Chunk()) {

		switch (cload.Cur_Chunk_ID()) {

			case W3D_CHUNK_COMPRESSED_ANIMATION_CHANNEL:

				switch ( Flavor ) {

					case ANIM_FLAVOR_TIMECODED:
						
						if (!read_channel(cload,&tc_chan)) {
							goto Error;
						}			
						if (tc_chan->Get_Pivot() < NumNodes) {
							add_channel(tc_chan);
						} else {
							// PWG 12-14-98: we have only allocated space for NumNode pivots.  
							// If we have an index thats equal or higher than NumNode we are
							// gonna trash memory.  Boy will we trash memory.
							// GTH 09-25-2000: print a warning and survive this error
							delete tc_chan;
							WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
						}

						break;

					case ANIM_FLAVOR_ADAPTIVE_DELTA:
						if (!read_channel(cload,&ad_chan)) {
							goto Error;
						}			
						if (ad_chan->Get_Pivot() < NumNodes) {
							add_channel(ad_chan);
						} else {
							// PWG 12-14-98: we have only allocated space for NumNode pivots.  
							// If we have an index thats equal or higher than NumNode we are
							// gonna trash memory.  Boy will we trash memory.
							// GTH 09-25-2000: print a warning and survive this error
							delete ad_chan;
							WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
						}
						break;
				}
				break;
	
			case W3D_CHUNK_COMPRESSED_BIT_CHANNEL:
				if (!read_bit_channel(cload,&newbitchan)) {
					goto Error;
				}
				if (newbitchan->Get_Pivot() < NumNodes) {
					add_bit_channel(newbitchan);
				} else {
					// PWG 12-14-98: we have only allocated space for NumNode pivots.  
					// If we have an index thats equal or higher than NumNode we are
					// gonna trash memory.  Boy will we trash memory.
					// GTH 09-25-2000: print a warning and survive this error
					delete newbitchan;
					WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
				}

				break;

			default:
				break;
		}
		cload.Close_Chunk();
	}

	return OK;

Error:

	Free();
	return LOAD_ERROR;

}	 // Load_W3D

/*********************************************************************************************** 
 * HCompressedAnimClass::read_channel -- Reads in a single channel of motion                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::read_channel present-unmatched
bool HCompressedAnimClass::read_channel(ChunkLoadClass & cload,TimeCodedMotionChannelClass * * newchan)
{
	*newchan = W3DNEW TimeCodedMotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	
	
	return result;
  
}	// read_channel

// ?HCompressedAnimClass::read_channel present-unmatched
bool HCompressedAnimClass::read_channel(ChunkLoadClass & cload,AdaptiveDeltaMotionChannelClass * * newchan)
{
	*newchan = W3DNEW AdaptiveDeltaMotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	
	
	return result;
  
}	// read_channel


/*********************************************************************************************** 
 * HCompressedAnimClass::add_channel -- Adds a motion channel to the animation                 * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::add_channel present-unmatched
void HCompressedAnimClass::add_channel(TimeCodedMotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].tc.X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].tc.Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].tc.Z = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].tc.Q = newchan;
			break;

		case ANIM_CHANNEL_FADE:
			NodeMotion[idx].tc.Fade = newchan;
			break;
	}

}	// add_channel

// ?HCompressedAnimClass::add_channel present-unmatched
void HCompressedAnimClass::add_channel(AdaptiveDeltaMotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].ad.X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].ad.Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].ad.Z = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].ad.Q = newchan;
			break;

		case ANIM_CHANNEL_FADE:
			NodeMotion[idx].ad.Fade = newchan;
			break;
	}

}	// add_channel




/***********************************************************************************************
 * HCompressedAnimClass::read_bit_channel -- read a bit channel from the file                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::read_bit_channel present-unmatched
bool HCompressedAnimClass::read_bit_channel(ChunkLoadClass & cload,TimeCodedBitChannelClass * * newchan)
{
	*newchan = W3DNEW TimeCodedBitChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	

	return result;		 
  
}	// read_bit_channel


/***********************************************************************************************
 * HCompressedAnimClass::add_bit_channel -- install a bit channel into the animation           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::add_bit_channel present-unmatched
void HCompressedAnimClass::add_bit_channel(TimeCodedBitChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case BIT_CHANNEL_VIS:
			NodeMotion[idx].Vis = newchan;
			break;
	}
}

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Translation -- returns the translation vector for the given frame * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Translation present-unmatched
void HCompressedAnimClass::Get_Translation( Vector3& trans, int pividx, float frame ) const
{
	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];
	  
	trans=Vector3(0,0,0);

	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (motion->tc.X) motion->tc.X->Get_Vector(frame, &(trans[0]));
			if (motion->tc.Y) motion->tc.Y->Get_Vector(frame, &(trans[1]));
			if (motion->tc.Z) motion->tc.Z->Get_Vector(frame, &(trans[2]));
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (motion->ad.X) motion->ad.X->Get_Vector(frame, &(trans[0]));
			if (motion->ad.Y) motion->ad.Y->Get_Vector(frame, &(trans[1]));
			if (motion->ad.Z) motion->ad.Z->Get_Vector(frame, &(trans[2]));
			break;
		default:
			WWASSERT(0);	// unknown flavor
			break;
	}
}

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Orientation -- returns a quaternion for the orientation of the    * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Orientation present-unmatched
bool HCompressedAnimClass::Get_Orientation(Quaternion& q, int pividx,float frame) const
{		
	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (NodeMotion[pividx].tc.Q) q = NodeMotion[pividx].tc.Q->Get_QuatVector(frame);
			else q.Make_Identity();
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (NodeMotion[pividx].ad.Q) q = NodeMotion[pividx].ad.Q->Get_QuatVector(frame);
			else q.Make_Identity();
			break;
		default:
			WWASSERT(0); // unknown flavor
			break;
	}
	// BFME reports whether the pivot actually has rotation; these bodies are not
	// matched yet, so true is a placeholder that preserves Zero Hour behaviour.
	return true;
} // Get_Orientation

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Transform -- returns the transform matrix for the given frame	  * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Transform present-unmatched
void HCompressedAnimClass::Get_Transform( Matrix3D& mtx, int pividx, float frame ) const
{
	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];
	  
		switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
		{
			TimeCodedMotionChannelClass * qchan = NodeMotion[pividx].tc.Q;
			if (qchan) {
				Quaternion q;
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
					const float32 * vec = (const float32 *)&data[pidx + 1];
					q.Set(vec[0], vec[1], vec[2], vec[3]);
				} else {
					p2idx = pidx + qchan->PacketSize;
					uint32 time = data[p2idx];
					if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
						const float32 * vec = (const float32 *)&data[pidx + 1];
						q.Set(vec[0], vec[1], vec[2], vec[3]);
					} else {
						float32 time1 = (data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
						float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
						float32 ratio = (frame - time1) / (time2 - time1);
						Fast_Slerp(q,
							*(Quaternion *)&data[pidx + 1],
							*(Quaternion *)&data[p2idx + 1],
							 ratio);
					}
				}
				::Build_Matrix3D(q,mtx);
			}
			else mtx.Make_Identity();
			if (motion->tc.X) motion->tc.X->Get_Vector(frame, &(mtx[0][3]));
			if (motion->tc.Y) motion->tc.Y->Get_Vector(frame, &(mtx[1][3]));
			if (motion->tc.Z) motion->tc.Z->Get_Vector(frame, &(mtx[2][3]));
			break;
		}
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
		{
			if (NodeMotion[pividx].ad.Q) {
				::Build_Matrix3D(NodeMotion[pividx].ad.Q->Get_QuatVector(frame),mtx);
			}
			else mtx.Make_Identity();

			if (motion->ad.X) motion->ad.X->Get_Vector(frame, &(mtx[0][3]));
			if (motion->ad.Y) motion->ad.Y->Get_Vector(frame, &(mtx[1][3]));
			if (motion->ad.Z) motion->ad.Z->Get_Vector(frame, &(mtx[2][3]));
			break;
		}
		default:
			WWASSERT(0);	// unknown flavor
			break;
	}
}

/***********************************************************************************************
 * HCompressedAnimClass::Get_Visibility -- return visibility state for given pivot/frame       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Visibility present-unmatched
bool HCompressedAnimClass::Get_Visibility(int pividx,float frame)
{		

	if (NodeMotion[pividx].Vis != NULL) {
		return (NodeMotion[pividx].Vis->Get_Bit((int)frame) == 1);
	}


	// default to always visible...
	return 1;
}



/***********************************************************************************************
 * HAnimClass::Is_Node_Motion_Present -- return true if there is motion defined for this frame *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/23/99    EHC : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::Is_Node_Motion_Present present-unmatched
bool HCompressedAnimClass::Is_Node_Motion_Present(int pividx) 
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));

	if (NodeMotion[pividx].vd.X != NULL)	return true;
	if (NodeMotion[pividx].vd.Y != NULL)	return true;
	if (NodeMotion[pividx].vd.Z != NULL)	return true;
	if (NodeMotion[pividx].vd.Q  != NULL)	return true;
	if (NodeMotion[pividx].Vis != NULL)		return true;

	return false;
}

// ?HCompressedAnimClass::Has_X_Translation present-unmatched
bool HCompressedAnimClass::Has_X_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.X != NULL;
}

// ?HCompressedAnimClass::Has_Y_Translation present-unmatched
bool HCompressedAnimClass::Has_Y_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Y != NULL;
}

// ?HCompressedAnimClass::Has_Z_Translation present-unmatched
bool HCompressedAnimClass::Has_Z_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Z != NULL;
}

// ?HCompressedAnimClass::Has_Rotation present-unmatched
bool HCompressedAnimClass::Has_Rotation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Q != NULL;
}

// ?HCompressedAnimClass::Has_Visibility present-unmatched
bool HCompressedAnimClass::Has_Visibility (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Vis != NULL;
}


// eof - hcanim.cpp
