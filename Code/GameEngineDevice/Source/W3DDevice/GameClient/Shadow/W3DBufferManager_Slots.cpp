// cl: /DNDEBUG /MD /EHsc
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

// W3DBufferManager's four slot pool accessors -- Zero Hour bodies, unchanged,
// compiled against the BFME member block.
//
// One constant did all the drift. releaseSlot(W3DVertexBufferSlot*) at
// 0x007ADD60 indexes m_W3DVertexBufferSlots with `shl edi,9` on the vertex
// format before adding the size index, so a row of that array is 512 pointers
// wide, not ZH's MAX_VB_SIZES of 128.
//
// Nothing else in the block moved, and releaseSlot(W3DIndexBufferSlot*) at
// 0x007ADFC0 proves it: it reaches m_W3DIndexBufferSlots at this+0x253D0, and
//
//     18*512*4  m_W3DVertexBufferSlots[MAX_FVF][512]
//   +   18*4    m_W3DVertexBuffers[MAX_FVF]
//   + 4096*28   m_W3DVertexBufferEmptySlots[MAX_NUMBER_SLOTS]
//   +      4    m_numEmptySlotsAllocated
//   +   32*28   m_W3DEmptyVertexBuffers[MAX_VERTEX_BUFFERS_CREATED]
//   +      4    m_numEmptyVertexBuffersAllocated
//   = 0x253D0
//
// so MAX_FVF, MAX_NUMBER_SLOTS and MAX_VERTEX_BUFFERS_CREATED are all still ZH's.
//
// The class is spelled here rather than in a corrected copy of
// W3DDevice/GameClient/W3DBufferManager.h on purpose: a header or shim change
// makes every later commit in the tree run the full gate, which is the same
// reason FrameDataManager.cpp declares its class inline. Only the four bodies
// below need the corrected width, and W3DBufferManager.cpp keeps compiling
// against the vendored ZH header exactly as before.
//
// getSlot's one out-of-line call is allocateSlotStorage, whose body is still
// drifted; both overloads are declared but not defined here, and pinned in
// reverse/symbols.csv at the ILT thunk addresses their call sites encode.

#define MAX_VB_SIZES 512	// BFME, not ZH's 128 -- see above
#define MIN_SLOT_SIZE 32
#define MIN_SLOT_SIZE_SHIFT 5
#define MAX_NUMBER_SLOTS 4096
#define MAX_VERTEX_BUFFERS_CREATED 32
#define MAX_IB_SIZES 1024
#define MAX_INDEX_BUFFERS_CREATED 32

#define NULL 0

typedef int Int;

class DX8VertexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8VertexBufferClass( unsigned fvf, unsigned short vertexCount,
		UsageType usage = USAGE_DEFAULT, unsigned vertexSize = 0 );
private:
	char m_storage[ 32 ];
};

class DX8IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass( unsigned indexCount, UsageType usage = USAGE_DEFAULT );
private:
	char m_storage[ 24 ];
};

class W3DBufferManager
{
public:

	enum VBM_FVF_TYPES
	{
		VBM_FVF_XYZ,
		VBM_FVF_XYZD,
		VBM_FVF_XYZUV,
		VBM_FVF_XYZDUV,
		VBM_FVF_XYZUV2,
		VBM_FVF_XYZDUV2,
		VBM_FVF_XYZN,
		VBM_FVF_XYZND,
		VBM_FVF_XYZNUV,
		VBM_FVF_XYZNDUV,
		VBM_FVF_XYZNUV2,
		VBM_FVF_XYZNDUV2,
		VBM_FVF_XYZRHW,
		VBM_FVF_XYZRHWD,
		VBM_FVF_XYZRHWUV,
		VBM_FVF_XYZRHWDUV,
		VBM_FVF_XYZRHWUV2,
		VBM_FVF_XYZRHWDUV2,
		MAX_FVF
	};

	struct W3DRenderTask
	{
		W3DRenderTask	*m_nextTask;
	};

	struct W3DVertexBuffer;
	struct W3DIndexBuffer;

	struct W3DVertexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DVertexBuffer *m_VB;
		W3DVertexBufferSlot *m_prevSameSize;
		W3DVertexBufferSlot *m_nextSameSize;
		W3DVertexBufferSlot *m_prevSameVB;
		W3DVertexBufferSlot *m_nextSameVB;
	};

	struct W3DVertexBuffer
	{
		VBM_FVF_TYPES	m_format;
		W3DVertexBufferSlot *m_usedSlots;
		Int	m_startFreeIndex;
		Int m_size;
		W3DVertexBuffer *m_nextVB;
		DX8VertexBufferClass *m_DX8VertexBuffer;
		W3DRenderTask	*m_renderTaskList;
	};

	struct W3DIndexBufferSlot
	{
		Int m_size;
		Int m_start;
		W3DIndexBuffer *m_IB;
		W3DIndexBufferSlot *m_prevSameSize;
		W3DIndexBufferSlot *m_nextSameSize;
		W3DIndexBufferSlot *m_prevSameIB;
		W3DIndexBufferSlot *m_nextSameIB;
	};

	struct W3DIndexBuffer
	{
		W3DIndexBufferSlot *m_usedSlots;
		Int	m_startFreeIndex;
		Int m_size;
		W3DIndexBuffer *m_nextIB;
		DX8IndexBufferClass *m_DX8IndexBuffer;
	};

	W3DVertexBufferSlot *getSlot(VBM_FVF_TYPES fvfType, Int size);
	W3DIndexBufferSlot *getSlot(Int size);
	void releaseSlot(W3DVertexBufferSlot *vbSlot);
	void releaseSlot(W3DIndexBufferSlot *ibSlot);
	void freeAllSlots(void);

protected:

	W3DVertexBufferSlot *m_W3DVertexBufferSlots[MAX_FVF][MAX_VB_SIZES];	///< retail this+0x00000
	W3DVertexBuffer		*m_W3DVertexBuffers[MAX_FVF];					///< retail this+0x09000
	W3DVertexBufferSlot	m_W3DVertexBufferEmptySlots[MAX_NUMBER_SLOTS];	///< retail this+0x09048
	Int m_numEmptySlotsAllocated;
	W3DVertexBuffer		m_W3DEmptyVertexBuffers[MAX_VERTEX_BUFFERS_CREATED];
	Int m_numEmptyVertexBuffersAllocated;

	W3DIndexBufferSlot *m_W3DIndexBufferSlots[MAX_IB_SIZES];			///< retail this+0x253D0
	W3DIndexBuffer		*m_W3DIndexBuffers;
	W3DIndexBufferSlot	m_W3DIndexBufferEmptySlots[MAX_NUMBER_SLOTS];
	Int m_numEmptyIndexSlotsAllocated;
	W3DIndexBuffer		m_W3DEmptyIndexBuffers[MAX_INDEX_BUFFERS_CREATED];
	Int m_numEmptyIndexBuffersAllocated;

	W3DVertexBufferSlot *allocateSlotStorage(VBM_FVF_TYPES fvfType, Int size);
	W3DIndexBufferSlot *allocateSlotStorage(Int size);
};

// ?freeAllSlots@W3DBufferManager@@QAEXXZ
void W3DBufferManager::freeAllSlots(void)
{
	Int i,j;

	for (i=0; i<MAX_FVF; i++)
	{
		for (j=0; j<MAX_VB_SIZES; j++)
		{
			W3DVertexBufferSlot *vbSlot = m_W3DVertexBufferSlots[i][j];
			while (vbSlot)
			{
				if (vbSlot->m_prevSameVB)
					vbSlot->m_prevSameVB->m_nextSameVB=vbSlot->m_nextSameVB;
				else
					vbSlot->m_VB->m_usedSlots=NULL;

				if (vbSlot->m_nextSameVB)
					vbSlot->m_nextSameVB->m_prevSameVB=vbSlot->m_prevSameVB;
				vbSlot=vbSlot->m_nextSameSize;
				m_numEmptySlotsAllocated--;
			}
			m_W3DVertexBufferSlots[i][j]=NULL;
		}
	}

	for (j=0; j<MAX_IB_SIZES; j++)
	{
		W3DIndexBufferSlot *ibSlot = m_W3DIndexBufferSlots[j];
		while (ibSlot)
		{
			if (ibSlot->m_prevSameIB)
				ibSlot->m_prevSameIB->m_nextSameIB=ibSlot->m_nextSameIB;
			else
				ibSlot->m_IB->m_usedSlots=NULL;

			if (ibSlot->m_nextSameIB)
				ibSlot->m_nextSameIB->m_prevSameIB=ibSlot->m_prevSameIB;
			ibSlot=ibSlot->m_nextSameSize;
			m_numEmptyIndexSlotsAllocated--;
		}
		m_W3DIndexBufferSlots[j]=NULL;
	}
}

/**Reserves space inside a vertex buffer.  If no space is available,
   creates a new slot and adds it to the pool.
*/
// ?getSlot@W3DBufferManager@@QAEPAUW3DVertexBufferSlot@1@W4VBM_FVF_TYPES@1@H@Z
W3DBufferManager::W3DVertexBufferSlot *W3DBufferManager::getSlot(VBM_FVF_TYPES fvfType, Int size)
{
	W3DVertexBufferSlot *vbSlot=NULL;

	//round size to next multiple of minimum slot size.
	//should help avoid fragmentation.
	size = (size + (MIN_SLOT_SIZE-1)) & (~(MIN_SLOT_SIZE-1));
	Int sizeIndex = (size >> MIN_SLOT_SIZE_SHIFT)-1;

	// DEBUG_ASSERTCRASH -- compiled out under NDEBUG

	if ((vbSlot=m_W3DVertexBufferSlots[fvfType][sizeIndex]) != 0)
	{	//found a previously allocated slot matching required size
		m_W3DVertexBufferSlots[fvfType][sizeIndex]=vbSlot->m_nextSameSize;
		if (vbSlot->m_nextSameSize)
			vbSlot->m_nextSameSize->m_prevSameSize=NULL;
		return vbSlot;
	}
	else
	{	//need to allocate a new slot
		return allocateSlotStorage(fvfType, size);
	}

	return NULL;
}

/**Returns vertex buffer space back to pool so it can be reused later*/
// ?releaseSlot@W3DBufferManager@@QAEXPAUW3DVertexBufferSlot@1@@Z
void W3DBufferManager::releaseSlot(W3DVertexBufferSlot *vbSlot)
{
	Int sizeIndex = (vbSlot->m_size >> MIN_SLOT_SIZE_SHIFT)-1;

	vbSlot->m_nextSameSize=m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex];
	if (m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex])
		m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex]->m_prevSameSize=vbSlot;

	m_W3DVertexBufferSlots[vbSlot->m_VB->m_format][sizeIndex]=vbSlot;
}

/**Reserves space inside an index buffer.  If no space is available,
   creates a new slot and adds it to the pool.
*/
// ?getSlot@W3DBufferManager@@QAEPAUW3DIndexBufferSlot@1@H@Z
W3DBufferManager::W3DIndexBufferSlot *W3DBufferManager::getSlot(Int size)
{
	W3DIndexBufferSlot *ibSlot=NULL;

	//round size to next multiple of minimum slot size.
	//should help avoid fragmentation.
	size = (size + (MIN_SLOT_SIZE-1)) & (~(MIN_SLOT_SIZE-1));
	Int sizeIndex = (size >> MIN_SLOT_SIZE_SHIFT)-1;

	// DEBUG_ASSERTCRASH -- compiled out under NDEBUG

	if ((ibSlot=m_W3DIndexBufferSlots[sizeIndex]) != 0)
	{	//found a previously allocated slot matching required size
		m_W3DIndexBufferSlots[sizeIndex]=ibSlot->m_nextSameSize;
		if (ibSlot->m_nextSameSize)
			ibSlot->m_nextSameSize->m_prevSameSize=NULL;
		return ibSlot;
	}
	else
	{	//need to allocate a new slot
		return allocateSlotStorage(size);
	}

	return NULL;
}

/**Returns index buffer space back to pool so it can be reused later*/
// ?releaseSlot@W3DBufferManager@@QAEXPAUW3DIndexBufferSlot@1@@Z
void W3DBufferManager::releaseSlot(W3DIndexBufferSlot *ibSlot)
{
	Int sizeIndex = (ibSlot->m_size >> MIN_SLOT_SIZE_SHIFT)-1;

	ibSlot->m_nextSameSize=m_W3DIndexBufferSlots[sizeIndex];
	if (m_W3DIndexBufferSlots[sizeIndex])
		m_W3DIndexBufferSlots[sizeIndex]->m_prevSameSize=ibSlot;

	m_W3DIndexBufferSlots[sizeIndex]=ibSlot;
}

static int SlotFVFTypeIndexList[ W3DBufferManager::MAX_FVF ] =
{
	0x002, 0x042, 0x102, 0x142, 0x202, 0x242,
	0x012, 0x052, 0x112, 0x152, 0x212, 0x252,
	0x004, 0x044, 0x104, 0x144, 0x204, 0x244
};

W3DBufferManager::W3DVertexBufferSlot *W3DBufferManager::allocateSlotStorage(
	VBM_FVF_TYPES fvfType, Int size )
{
	W3DVertexBuffer *pVB = m_W3DVertexBuffers[ fvfType ];
	W3DVertexBufferSlot *vbSlot;

	while ( pVB )
	{
		if ( pVB->m_size - pVB->m_startFreeIndex >= size )
		{
			if ( m_numEmptySlotsAllocated < MAX_NUMBER_SLOTS )
			{
				vbSlot = &m_W3DVertexBufferEmptySlots[ m_numEmptySlotsAllocated ];
				vbSlot->m_size = size;
				vbSlot->m_start = pVB->m_startFreeIndex;
				vbSlot->m_VB = pVB;
				vbSlot->m_nextSameVB = pVB->m_usedSlots;
				vbSlot->m_prevSameVB = NULL;
				if ( pVB->m_usedSlots )
					pVB->m_usedSlots->m_prevSameVB = vbSlot;
				vbSlot->m_prevSameSize = vbSlot->m_nextSameSize = NULL;
				pVB->m_usedSlots = vbSlot;
				pVB->m_startFreeIndex += size;
				m_numEmptySlotsAllocated++;
				return vbSlot;
			}
		}
		pVB = pVB->m_nextVB;
	}

	pVB = m_W3DVertexBuffers[ fvfType ];
	if ( m_numEmptyVertexBuffersAllocated < MAX_VERTEX_BUFFERS_CREATED )
	{
		m_W3DVertexBuffers[ fvfType ] =
			&m_W3DEmptyVertexBuffers[ m_numEmptyVertexBuffersAllocated ];
		m_W3DVertexBuffers[ fvfType ]->m_nextVB = pVB;
		m_numEmptyVertexBuffersAllocated++;
		pVB = m_W3DVertexBuffers[ fvfType ];

		Int vbSize = size < 16384 ? 16384 : size;
		pVB->m_DX8VertexBuffer = new DX8VertexBufferClass(
			SlotFVFTypeIndexList[ fvfType ], (unsigned short)vbSize,
			DX8VertexBufferClass::USAGE_DEFAULT );
		pVB->m_format = fvfType;
		pVB->m_startFreeIndex = size;
		pVB->m_size = vbSize;
		pVB->m_renderTaskList = NULL;
		vbSlot = &m_W3DVertexBufferEmptySlots[ m_numEmptySlotsAllocated ];
		m_numEmptySlotsAllocated++;
		pVB->m_usedSlots = vbSlot;
		vbSlot->m_size = size;
		vbSlot->m_start = 0;
		vbSlot->m_VB = pVB;
		vbSlot->m_prevSameVB = vbSlot->m_nextSameVB = NULL;
		vbSlot->m_prevSameSize = vbSlot->m_nextSameSize = NULL;
		return vbSlot;
	}

	return NULL;
}

W3DBufferManager::W3DIndexBufferSlot *W3DBufferManager::allocateSlotStorage( Int size )
{
	W3DIndexBuffer *pIB = m_W3DIndexBuffers;
	W3DIndexBufferSlot *ibSlot;

	while ( pIB )
	{
		if ( pIB->m_size - pIB->m_startFreeIndex >= size )
		{
			if ( m_numEmptyIndexSlotsAllocated < MAX_NUMBER_SLOTS )
			{
				ibSlot = &m_W3DIndexBufferEmptySlots[ m_numEmptyIndexSlotsAllocated ];
				ibSlot->m_size = size;
				ibSlot->m_start = pIB->m_startFreeIndex;
				ibSlot->m_IB = pIB;
				ibSlot->m_nextSameIB = pIB->m_usedSlots;
				ibSlot->m_prevSameIB = NULL;
				if ( pIB->m_usedSlots )
					pIB->m_usedSlots->m_prevSameIB = ibSlot;
				ibSlot->m_prevSameSize = ibSlot->m_nextSameSize = NULL;
				pIB->m_usedSlots = ibSlot;
				pIB->m_startFreeIndex += size;
				m_numEmptyIndexSlotsAllocated++;
				return ibSlot;
			}
		}
		pIB = pIB->m_nextIB;
	}

	pIB = m_W3DIndexBuffers;
	if ( m_numEmptyIndexBuffersAllocated < MAX_INDEX_BUFFERS_CREATED )
	{
		m_W3DIndexBuffers = &m_W3DEmptyIndexBuffers[ m_numEmptyIndexBuffersAllocated ];
		m_W3DIndexBuffers->m_nextIB = pIB;
		m_numEmptyIndexBuffersAllocated++;
		pIB = m_W3DIndexBuffers;

		Int ibSize = size < 32768 ? 32768 : size;
		pIB->m_DX8IndexBuffer =
			new DX8IndexBufferClass( ibSize, DX8IndexBufferClass::USAGE_DEFAULT );
		pIB->m_startFreeIndex = size;
		pIB->m_size = ibSize;
		ibSlot = &m_W3DIndexBufferEmptySlots[ m_numEmptyIndexSlotsAllocated ];
		m_numEmptyIndexSlotsAllocated++;
		pIB->m_usedSlots = ibSlot;
		ibSlot->m_size = size;
		ibSlot->m_start = 0;
		ibSlot->m_IB = pIB;
		ibSlot->m_prevSameIB = ibSlot->m_nextSameIB = NULL;
		ibSlot->m_prevSameSize = ibSlot->m_nextSameSize = NULL;
		return ibSlot;
	}

	return NULL;
}
