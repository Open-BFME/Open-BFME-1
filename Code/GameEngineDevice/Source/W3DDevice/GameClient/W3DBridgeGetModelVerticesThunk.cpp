// readable body of ?getModelVertices@W3DBridge@@IAEHPAUVertexFormatXYZNDUV1@@HMAAVVector3@@111ABVMatrix3D@@PAVMeshClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
struct VertexFormatXYZNDUV1;
class Vector3;
class Matrix3D;
class MeshClass;
class RenderObjClass;

template<class T>
class RefMultiListIterator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridge
{
protected:
	int getModelVertices(VertexFormatXYZNDUV1 *, int, float, Vector3 &, Vector3 &, Vector3 &, Vector3 &, const Matrix3D &, MeshClass *, RefMultiListIterator<RenderObjClass> *);
};

class W3DBridgeGetModelVerticesShim
{
public:
	int getModelVertices(VertexFormatXYZNDUV1 *, int, float, Vector3 &, Vector3 &, Vector3 &, Vector3 &, const Matrix3D &, MeshClass *, RefMultiListIterator<RenderObjClass> *);
};

int W3DBridge::getModelVertices(VertexFormatXYZNDUV1 *format, int count, float scale, Vector3 &a, Vector3 &b, Vector3 &c, Vector3 &d, const Matrix3D &matrix, MeshClass *mesh, RefMultiListIterator<RenderObjClass> *iterator)
{
	return ((W3DBridgeGetModelVerticesShim *)this)->getModelVertices(format, count, scale, a, b, c, d, matrix, mesh, iterator);
}
