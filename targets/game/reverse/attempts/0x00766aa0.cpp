// ?d_00766aa0@@YAXXZ
// partial score=0.58 date=2026-09-02
// ?d_00766aa0@@YAXXZ
// partial score=0.04 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
// Partial reconstruction of retail 0x00766AA0.  The two callers at
// 0x00769B60/0x00769C30 pass a selected AsciiString by value and prove the
// four-argument member shape.  The retail body resolves a named RenderObj,
// verifies that it is a mesh, and derives a world-space BridgeInfo prefix from
// the mesh vertices.  The output offsets are now identified: from at 0x00, to
// at 0x0C, bridgeWidth at 0x18, and the four corners at 0x1C..0x48.

typedef unsigned int u32;

class BfmeStringBase
{
protected:
    void *m_buffer;
public:
    BfmeStringBase();
    BfmeStringBase(const BfmeStringBase &);
    ~BfmeStringBase();
};

class BfmeGeometryName : private BfmeStringBase
{
public:
    BfmeGeometryName(const BfmeGeometryName &s) : BfmeStringBase(s) {}
    ~BfmeGeometryName() {}
    const char *text() const
    {
        return m_buffer ? (const char *)m_buffer + 8 : (const char *)0x0107388b;
    }
};

struct BfmeVec3
{
    float x, y, z;
};

struct BfmeMatrix3D
{
    float m[3][4];
    void identity()
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    }
};

struct BfmeMeshModel
{
    char pad0[0x24];
    int polygonCount;
    int vertexCount;
    char pad2c[4];
    void *vertexBuffer;
};

struct BfmeRenderObject
{
    void **vtable;
    int refs;
    char pad08[0x10];
    BfmeMatrix3D transform;
    char pad48[0x80];
    BfmeMeshModel *model;
};

struct BfmeGeometryResult
{
    BfmeVec3 center0;
    BfmeVec3 center1;
    float width;
    BfmeVec3 corners[4];
};

struct BfmeDrawModuleView
{
    unsigned char *moduleData;
    unsigned char *drawable;

    virtual void d00() = 0; virtual void d01() = 0;
    virtual void d02() = 0; virtual void d03() = 0;
    virtual void d04() = 0; virtual void d05() = 0;
    virtual void d06() = 0; virtual void d07() = 0;
    virtual void d08() = 0; virtual void d09() = 0;
    virtual void d10() = 0; virtual void d11() = 0;
    virtual void d12() = 0; virtual void d13() = 0;
    virtual void d14() = 0; virtual void d15() = 0;
    virtual void d16() = 0; virtual void d17() = 0;
    virtual void d18() = 0; virtual void d19() = 0;
    virtual void d20() = 0; virtual void d21() = 0;
    virtual void d22() = 0; virtual void d23() = 0;
    virtual void d24() = 0; virtual void d25() = 0;
    virtual void d26() = 0; virtual void d27() = 0;
    virtual void d28() = 0; virtual void d29() = 0;
    virtual void d30() = 0; virtual void d31() = 0;
    virtual void d32() = 0; virtual void d33() = 0;
    virtual void d34() = 0; virtual void d35() = 0;
    virtual void d36() = 0; virtual void d37() = 0;
    virtual void d38() = 0; virtual void d39() = 0;
    virtual void d40() = 0; virtual void d41() = 0;
    virtual void d42() = 0; virtual void d43() = 0;
    virtual void d44() = 0; virtual void d45() = 0;
    virtual void *drawableObject() = 0;

    bool buildMeshGeometry(BfmeGeometryResult *result, BfmeGeometryName name,
                           int *vertexResult, BfmeRenderObject **objectResult);
};

// VC7.1 does not accept __thiscall on a function-pointer typedef.  The
// __fastcall views keep the receiver in ECX; the unused EDX argument models
// the member-call register convention at these indirect sites.
typedef void *(__fastcall *NoArgFn)(void *, void *);
typedef BfmeRenderObject *(__fastcall *FindNamedFn)(void *, void *, const char *, int);
typedef BfmeRenderObject *(__fastcall *RenderFn)(BfmeRenderObject *, void *);
typedef int (__fastcall *ClassIdFn)(BfmeRenderObject *, void *);
typedef void (__fastcall *ReleaseFn)(BfmeRenderObject *, void *);
typedef void (__fastcall *MatrixFn)(void *, void *, BfmeMatrix3D *);

extern void __fastcall bfmeAdjustGeometryMatrix(BfmeDrawModuleView *, void *, BfmeMatrix3D *);
extern int __fastcall bfmeMeshVertexResult(BfmeDrawModuleView *, void *, BfmeRenderObject *, BfmeVec3 *);

static void release(BfmeRenderObject *p)
{
    if (p && --p->refs == 0)
        ((ReleaseFn)p->vtable[0])(p, 0);
}

static __forceinline float distanceSquared(const BfmeVec3 &a, const BfmeVec3 &b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

static __forceinline BfmeVec3 transformPoint(const BfmeMatrix3D &m, const BfmeVec3 &v)
{
    BfmeVec3 r;
    r.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
    r.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
    r.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
    return r;
}

extern "C" double __cdecl sqrt(double);

bool BfmeDrawModuleView::buildMeshGeometry(BfmeGeometryResult *result,
                                           BfmeGeometryName name,
                                           int *vertexResult,
                                           BfmeRenderObject **objectResult)
{
    // Retail reserves 0xBC bytes.  Its explicit Vector3 and matrix temporaries
    // account for this final 0x30-byte allocation gap.
    BfmeRenderObject *renderObject = 0;
    void *drawableObject = this->drawableObject();

    if (vertexResult)
        *vertexResult = 0;
    if (objectResult)
        *objectResult = 0;

    if (drawableObject) {
        FindNamedFn findNamed = (FindNamedFn)(*(void ***)drawableObject)[0x1f];
        BfmeRenderObject *held = findNamed(drawableObject, 0, name.text(), 0);
        if (held) {
            renderObject = ((RenderFn)held->vtable[5])(held, this);
            release(held);
        }
    }

    if (!drawable || !*(void **)(drawable + 0xfc) || !renderObject) {
        release(renderObject);
        return false;
    }

    BfmeMatrix3D matrix;
    matrix.identity();
    if (moduleData[0x69]) {
        const BfmeMatrix3D *source = (const BfmeMatrix3D *)
            ((NoArgFn)(*(void ***)moduleData)[0])(moduleData, this);
        matrix.m[0][3] = source->m[1][3];
        matrix.m[1][3] = source->m[0][3];
        matrix.m[2][3] = source->m[2][3];
    } else {
        matrix = *(const BfmeMatrix3D *)(drawable + 0xfc);
    }

    bfmeAdjustGeometryMatrix(this, this, &matrix);
    if (drawableObject)
        ((MatrixFn)(*(void ***)drawableObject)[0x15])(drawableObject, this, &matrix);

    if (((ClassIdFn)renderObject->vtable[3])(renderObject, this) != 0) {
        release(renderObject);
        return false;
    }

    if (objectResult) {
        ++renderObject->refs;
        *objectResult = renderObject;
    }

    BfmeMeshModel *model = renderObject->model;
    unsigned char *vertexStorage = model && model->vertexBuffer
        ? *(unsigned char **)((unsigned char *)model->vertexBuffer + 0x0c) : 0;
    BfmeVec3 *vertices = vertexStorage ? (BfmeVec3 *)(vertexStorage + 8) : 0;
    if (vertexResult && model && model->polygonCount > 2)
        *vertexResult = bfmeMeshVertexResult(this, this, renderObject, vertices);

    if (result && model && vertices && model->vertexCount > 0) {
        volatile unsigned char retailGeometryScratch[0x30];
        retailGeometryScratch[0] = 0;
        int count = model->vertexCount;
        float minX = vertices[0].x;
        float maxX = minX;
        int i;
        for (i = 1; i < count; ++i) {
            float x = vertices[i].x;
            if (x > maxX) maxX = x;
            if (x < minX) minX = x;
        }

        float halfSpan = (maxX - minX) * 0.5f;
        float highLimit = minX + halfSpan;
        float lowLimit = maxX - halfSpan;
        BfmeVec3 a = { 0, 0, 0 };
        BfmeVec3 b = { 0, 0, 0 };
        BfmeVec3 c = { 0, 0, 0 };
        BfmeVec3 d = { 0, 0, 0 };
        bool haveHigh = false;
        bool haveLow = false;

        for (i = 0; i < count; ++i) {
            const BfmeVec3 &v = vertices[i];
            if (v.x >= highLimit) {
                if (!haveHigh) {
                    a = b = v;
                    haveHigh = true;
                } else if (distanceSquared(a, v) > distanceSquared(a, b)) {
                    b = v;
                }
            } else if (v.x <= lowLimit) {
                if (!haveLow) {
                    c = d = v;
                    haveLow = true;
                } else if (distanceSquared(c, v) > distanceSquared(c, d)) {
                    d = v;
                }
            }
        }

        if (!haveHigh || !haveLow) {
            release(renderObject);
            return false;
        }

        // Retail makes a second pass so that each retained end point is the
        // farthest point from its mate, rather than depending on vertex order.
        for (i = 0; i < count; ++i) {
            const BfmeVec3 &v = vertices[i];
            if (v.x >= highLimit) {
                if (distanceSquared(b, v) > distanceSquared(b, a))
                    a = v;
            } else if (v.x <= lowLimit) {
                if (distanceSquared(d, v) > distanceSquared(d, c))
                    c = v;
            }
        }

        BfmeVec3 midpointHigh;
        midpointHigh.x = (a.x + b.x) * 0.5f;
        midpointHigh.y = (a.y + b.y) * 0.5f;
        midpointHigh.z = (a.z + b.z) * 0.5f;
        BfmeVec3 midpointLow;
        midpointLow.x = (c.x + d.x) * 0.5f;
        midpointLow.y = (c.y + d.y) * 0.5f;
        midpointLow.z = (c.z + d.z) * 0.5f;

        result->center0 = transformPoint(matrix, midpointLow);
        result->center1 = transformPoint(matrix, midpointHigh);
        float highWidth = (float)sqrt((double)distanceSquared(a, b));
        float lowWidth = (float)sqrt((double)distanceSquared(c, d));
        result->width = (highWidth + lowWidth) * 0.5f;

        if (model->polygonCount > 2) {
            BfmeVec3 p = transformPoint(matrix, a);
            result->corners[2].x = (float)(int)p.x;
            result->corners[2].y = (float)(int)p.y;
            result->corners[2].z = (float)(int)p.z;
            p = transformPoint(matrix, b);
            result->corners[3].x = (float)(int)p.x;
            result->corners[3].y = (float)(int)p.y;
            result->corners[3].z = (float)(int)p.z;
            p = transformPoint(matrix, c);
            result->corners[0].x = (float)(int)p.x;
            result->corners[0].y = (float)(int)p.y;
            result->corners[0].z = (float)(int)p.z;
            p = transformPoint(matrix, d);
            result->corners[1].x = (float)(int)p.x;
            result->corners[1].y = (float)(int)p.y;
            result->corners[1].z = (float)(int)p.z;
        } else {
            float dx = result->center1.x - result->center0.x;
            float dy = result->center1.y - result->center0.y;
            float invLength = 1.0f / (float)sqrt((double)(dx * dx + dy * dy));
            float ox = -dy * invLength * result->width * 0.5f;
            float oy = dx * invLength * result->width * 0.5f;
            result->corners[0].x = result->center0.x + ox;
            result->corners[0].y = result->center0.y + oy;
            result->corners[0].z = result->center0.z;
            result->corners[1].x = result->center0.x - ox;
            result->corners[1].y = result->center0.y - oy;
            result->corners[1].z = result->center0.z;
            result->corners[2].x = result->center1.x + ox;
            result->corners[2].y = result->center1.y + oy;
            result->corners[2].z = result->center1.z;
            result->corners[3].x = result->center1.x - ox;
            result->corners[3].y = result->center1.y - oy;
            result->corners[3].z = result->center1.z;
        }
    }

    release(renderObject);
    return true;
}
