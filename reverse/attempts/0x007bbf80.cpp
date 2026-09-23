// ?RenderMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z
// partial score=0.7 date=2026-09-23
// Best measured partial reconstruction for 0x007BBF80.
struct BfmeRenderDevice;
typedef long (__stdcall *BfmeSetTransform)(BfmeRenderDevice *, unsigned, void *);
typedef long (__stdcall *BfmeSetStreamSource)(BfmeRenderDevice *, unsigned, void *, unsigned, unsigned);
typedef long (__stdcall *BfmeSetIndices)(BfmeRenderDevice *, void *);
typedef long (__stdcall *BfmeSetRenderState)(BfmeRenderDevice *, unsigned, unsigned);
typedef long (__stdcall *BfmeDrawIndexedPrimitive)(BfmeRenderDevice *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
struct BfmeRenderDevice { void **vtable; };
struct BfmeRenderFVFInfo { unsigned unused; unsigned stride; };
struct BfmeRenderDX8VertexBuffer { char unused14[0x14]; BfmeRenderFVFInfo *fvfInfo; char unused18[4]; void *vertexBuffer; };
struct BfmeRenderW3DVertexBuffer { char unused14[0x14]; BfmeRenderDX8VertexBuffer *dx8VertexBuffer; };
struct BfmeRenderVertexBufferSlot { int size; int start; BfmeRenderW3DVertexBuffer *vertexBuffer; };
struct BfmeRenderDX8IndexBuffer { char unused14[0x14]; void *indexBuffer; };
struct BfmeRenderW3DIndexBuffer { char unused10[0x10]; BfmeRenderDX8IndexBuffer *dx8IndexBuffer; };
struct BfmeRenderIndexBufferSlot { int size; int start; BfmeRenderW3DIndexBuffer *indexBuffer; };

void W3DVolumetricShadow::RenderMeshVolume(Int meshIndex, Int lightIndex, const Matrix3D *meshXform)
{
    BfmeRenderDevice *device = *(BfmeRenderDevice **)0x01340534;
    if (!device) return;

    int shadowMask = *(int *)((char *)this + 0x34) >> 7 & 7;
    if (shadowMask) {
        unsigned shadowRef = shadowMask << 4;
        unsigned mask = *(unsigned *)((char *)*(void **)0x01306EEC + 8);
        unsigned repeated = shadowRef;
        repeated = (repeated << 8) | shadowRef;
        repeated = (repeated << 8) | shadowRef;
        repeated = (repeated << 8) | mask;
        repeated |= shadowRef;
        (*(BfmeSetRenderState **)device)[57](device, 0x3a, repeated);
        (*(BfmeSetRenderState **)device)[57](device, 0x39, shadowRef);
    }

    Geometry *geometry = m_shadowVolume[lightIndex][meshIndex];
    int numVerts = geometry->GetNumActiveVertex();
    int numPolys = geometry->GetNumActivePolygon();
    if (!numVerts || !numPolys) return;

    Matrix4x4 mWorld(*meshXform);
    (*(BfmeSetTransform **)device)[44](device, 0x100, (void *)&mWorld.Transpose());

    W3DBufferManager::W3DVertexBufferSlot *vbSlot =
        m_shadowVolumeVB[lightIndex][meshIndex];
    if (!vbSlot) return;
    if (vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer() != *(void **)0x01306F34) {
        *(void **)0x01306F34 = vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer();
        (*(BfmeSetStreamSource **)device)[100](device, 0,
            vbSlot->m_VB->m_DX8VertexBuffer->Get_DX8_Vertex_Buffer(), 0,
            vbSlot->m_VB->m_DX8VertexBuffer->FVF_Info().Get_FVF_Size());
    }

    W3DBufferManager::W3DIndexBufferSlot *ibSlot =
        m_shadowVolumeIB[lightIndex][meshIndex];
    if (!ibSlot) return;
    (*(BfmeSetIndices **)device)[104](device,
        ibSlot->m_IB->m_DX8IndexBuffer->Get_DX8_Index_Buffer());

    if (*(unsigned char *)0x012D6DAD) {
        Debug_Statistics::Record_DX8_Polys_And_Vertices(
            numPolys, numVerts,
            *reinterpret_cast<const ShaderClass *>(0x012D6E08));
        (*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, vbSlot->m_start, 0,
            numVerts, ibSlot->m_start, numPolys);
    }

    if (shadowMask) {
        unsigned mask = *(unsigned *)((char *)*(void **)0x01306EEC + 8);
        (*(BfmeSetRenderState **)device)[57](device, 0x3a, mask);
        (*(BfmeSetRenderState **)device)[57](device, 0x39, 0x80808080);
    }
}
