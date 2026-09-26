// ?getModelVertices@W3DBridgeGetModelVerticesShim@@QAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// Four matched callers and two same-file bridge callers prove this is the W3DBridge vertex body.
// The private shim keeps its implementation symbol distinct from the forwarding ILT.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DBridgeBuffer.cpp ////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: W3DBridgeBuffer.cpp
//
// Created:   John Ahlquist, May 2001
//
// Desc:      Draw buffer to handle all the bridges in a scene.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes
//-----------------------------------------------------------------------------
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"

#include "common/GlobalData.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "sharebuf.h"

class BfmeC998
{
public:
	void bfmeGo998C(Int);
};

struct BfmeStaticDiffuseGlobalData
{
	char m_padding0[0xA04];
	Coord3D m_terrainLightPos[4];
	char m_paddingA34[0xA58 - 0xA34];
	Int m_numGlobalLights;
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array_By_Index(int index, bool allow_default);
};

class MeshGeometryClass
{
	char m_prefix[0x28];
	Int m_vertexCount;
	ShareBufferClass<Vector3> *m_poly;
	ShareBufferClass<Vector3> *m_vertex;
	char m_materialPadding[0x68];

public:
	Int Get_Vertex_Count() const
	{
		return m_vertexCount;
	}

	Vector3 *Get_Vertex_Array()
	{
		return m_vertex->Get_Array();
	}

	const Vector3 *Get_Vertex_Normal_Array()
	{
		union
		{
			void (BfmeC998::*void_function)(Int);
			const Vector3 *(BfmeC998::*normal_function)(Int);
		} function;
		function.void_function = &BfmeC998::bfmeGo998C;
		return (((BfmeC998 *)this)->*function.normal_function)(0);
	}
};

class MeshModelClass : public MeshGeometryClass
{
	MeshMatDescClass *m_curMatDesc;

public:
	const Vector2 *Get_UV_Array_By_Index(int index)
	{
		return m_curMatDesc->Get_UV_Array_By_Index(index, false);
	}
};

class MeshClass
{
	char m_padding[0xc8];
	MeshModelClass *m_model;

public:
	MeshModelClass *Peek_Model()
	{
		return m_model;
	}
};

static WWINLINE void Rva006D7EA0TransformVector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}

	float x = (*(volatile const float *)&v->Z) * A[0][2];
	x = x + v->X * A[0][0];
	x = x + (*(volatile const float *)&A[0][1]) * v->Y;
	out->X = x + A[0][3];
	float y = (*(volatile const float *)&v->X) * A[1][0];
	y = y + v->Z * A[1][2];
	y = y + v->Y * A[1][1];
	out->Y = y + A[1][3];
	float z = v->Z * A[2][2];
	z = z + v->Y * A[2][1];
	z = z + (*(volatile const float *)&v->X) * A[2][0];
	out->Z = z + A[2][3];
}

static WWINLINE void Rva006D7EA0RotateVector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}

	float x = v->Z * A[0][2];
	x = x + v->Y * A[0][1];
	x = x + (*(volatile const float *)&A[0][0]) * v->X;
	out->X = x;
	float y = (*(volatile const float *)&v->Z) * A[1][2];
	y = y + (*(volatile const float *)&v->Y) * A[1][1];
	y = y + (*(volatile const float *)&A[1][0]) * v->X;
	out->Y = y;
	float z = (*(volatile const float *)&v->Z) * A[2][2];
	z = z + v->Y * A[2][1];
	z = z + (*(volatile const float *)&A[2][0]) * v->X;
	out->Z = z;
}

class W3DBridgeGetModelVerticesShim
{
public:
	Int getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
																Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
																const Matrix3D &mtx,
																MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator);
private:
	Vector3 m_start;
};

Int W3DBridgeGetModelVerticesShim::getModelVertices(VertexFormatXYZNDUV1 *destination_vb, Int curVertex, Real xOffset,
																Vector3 &vec, Vector3 &vecNormal, Vector3 &vecZ, Vector3 &offset,
																const Matrix3D &mtx,
																MeshClass *pMesh, RefRenderObjListIterator *pLightsIterator)
{
	if (pMesh == NULL)
		return(0);

	Int i;
	MeshModelClass *model = (MeshModelClass *)pMesh->Peek_Model();
	Int numVertex = model->Get_Vertex_Count();
	Vector3 *pVert = model->Get_Vertex_Array();
	const Vector3 *pNormal = model->Get_Vertex_Normal_Array();

	// If we happen to have too many bridges, stop.  BFME's limit is 8000, half
	// the Zero Hour header's 12000, and it is the same 8000 the matched
	// getModelIndices body below halves out of its own 16000 index limit.
	const Int maxBridgeVertex = 8000;
	if (curVertex+numVertex+2>= maxBridgeVertex) {
		return(0);
	}

	Vector3 lightRay[MAX_GLOBAL_LIGHTS];
	const Coord3D *lightPos;

	for (Int lightIndex=0; lightIndex < ((const BfmeStaticDiffuseGlobalData *)TheWritableGlobalData)->m_numGlobalLights; lightIndex++)
	{
		lightPos = &((const BfmeStaticDiffuseGlobalData *)TheWritableGlobalData)->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].Set(-lightPos->x, -lightPos->y, -lightPos->z);
//		__asm {int 3}; //see if it really needs normalization!!
		lightRay[lightIndex].Normalize();
	}

	const Vector2 *uvs = ((MeshModelClass *)pMesh->Peek_Model())->Get_UV_Array_By_Index(0);
	VertexFormatXYZNDUV1 *curVb = destination_vb+curVertex;

	for (i=0; i<numVertex; i++) {
		curVb->u1 = uvs[i].U;
		curVb->v1 = uvs[i].V;
		Vector3 vLoc;
		Vector3 vertex;
		Rva006D7EA0TransformVector(mtx, pVert[i], &vertex);
		vLoc = (vertex.X+xOffset) * vec + vertex.Y*vecNormal + vertex.Z*vecZ;

		_ReadWriteBarrier();
		Real vLocX = vLoc.X;
		_ReadWriteBarrier();
		vLoc.X = vLocX + m_start.X;
		vLoc.Y += m_start.Y;
		vLoc.Z += m_start.Z;

		curVb->x = vLoc.X;
		curVb->y = vLoc.Y;
		curVb->z = vLoc.Z;

		VERTEX_FORMAT vb;
		vb.x = vLoc.X;
		vb.y = vLoc.Y;
		vb.z = vLoc.Z;

		Vector3 normal;
		Rva006D7EA0RotateVector(mtx, pNormal[i], &normal);
		curVb->diffuse = 0xFF000000;
#ifdef USE_BRIDGE_NORMALS
		curVb->nx = normal.X;
		curVb->ny = normal.Y;
		curVb->nz = normal.Z;
		curVb->diffuse = 0xFF000000;
#else
		normal = normal.X * vec + normal.Y*vecNormal + normal.Z*vecZ;
		normal.Normalize();
		TheTerrainRenderObject->doTheLight(&vb, lightRay, &normal, NULL, 1.0f);
		curVb->diffuse = vb.diffuse | 0xFF000000;
#endif
		curVb++;
	}
	return(numVertex);
}

//=============================================================================
// W3DBridge::getModelVerticesFixed
//=============================================================================
/** Gets the vertex values for a section of a fixed bridge.  */
//=============================================================================
