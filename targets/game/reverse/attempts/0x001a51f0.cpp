// ?scan@Rva001A51F0TerrainGrid@@QAEXPBUCoord3D@@MPAHEH@Z
// partial score=0.72 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

typedef float Real;

static __forceinline int p48Round(Real value)
{
    int result;
    __asm { fld [value] }
    __asm { fistp [result] }
    return result;
}

struct Coord3D {
    Real x, y, z;
    void set(Real a, Real b, Real c) { x = a; y = b; z = c; }
    void sub(const Coord3D *other) { x -= other->x; y -= other->y; z -= other->z; }
    Real lengthSqr() const { return x * x + y * y + z * z; }
};
struct Region3D { Coord3D lo, hi; };

struct TerrainLogicP48Record {
    Coord3D position;
    int key;
    int m10;
    int m14;
    unsigned char m18;
    char pad19[15];
    int amount;
    unsigned char m2c;
    unsigned char m2d;
    short next;
};

class TerrainVisualP48Scan {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40();
    virtual void notify(int key, int value);
};

class Rva001A51F0TerrainGrid {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09();
    virtual void getExtent(Region3D *extent);
    void scan(const Coord3D *position, Real radius, int *a3, unsigned char a4, int a5);
private:
    char pad04[0x558];
    TerrainLogicP48Record *m_begin;
    TerrainLogicP48Record *m_end;
    int pad564;
    short m_partition[2500];
};

// ?scan@Rva001A51F0TerrainGrid@@QAEXPBUCoord3D@@MPAHEH@Z
void Rva001A51F0TerrainGrid::scan(const Coord3D *position, Real radius, int *a3, unsigned char a4, int a5)
{
    int count = m_end - m_begin;
    if (count == 0) return;
    radius += 7.0f;
    Region3D extent;
    getExtent(&extent);
    Real x = position->x - radius;
    Real y = position->y - radius;
    if (x < extent.lo.x) x = extent.lo.x;
    if (y < extent.lo.y) y = extent.lo.y;
    if (x > extent.hi.x) x = extent.hi.x;
    if (y > extent.hi.y) y = extent.hi.y;
    int xMin = p48Round((Real)floor((double)((x - extent.lo.x) / (extent.hi.x - extent.lo.x) * 49.9f)));
    int yMin = p48Round((Real)floor((double)((y - extent.lo.y) / (extent.hi.y - extent.lo.y) * 49.9f)));
    x = position->x + radius;
    y = position->y + radius;
    if (x < extent.lo.x) x = extent.lo.x;
    if (y < extent.lo.y) y = extent.lo.y;
    if (x > extent.hi.x) x = extent.hi.x;
    if (y > extent.hi.y) y = extent.hi.y;
    int xMax = p48Round((Real)ceil((double)((x - extent.lo.x) / (extent.hi.x - extent.lo.x) * 49.9f)));
    int yMax = p48Round((Real)ceil((double)((y - extent.lo.y) / (extent.hi.y - extent.lo.y) * 49.9f)));
    for (int i = xMin; i < xMax; ++i) {
        for (int j = yMin; j < yMax; ++j) {
            int index = m_partition[i + 50 * j];
            while (index != -1) {
                if (index >= 0 && index < count) {
                    TerrainLogicP48Record &record = m_begin[index];
                    if (record.key && (!a4 || !record.m18)) {
                        if (a5 == 1) {
                            if (record.m2c) goto processRecord;
                            goto nextRecord;
                        }
                        if (a5 == 2 && !record.m2d) goto nextRecord;
                    processRecord:
                        Coord3D delta;
                        delta.set(record.position.x, record.position.y, record.position.z);
                        delta.sub(position);
                        if (radius * radius > delta.lengthSqr()) {
                            TerrainVisualP48Scan *visual = *(TerrainVisualP48Scan **)0x012F7014;
                            visual->notify(record.key, *a3);
                        }
                    }
                nextRecord:
                    index = record.next;
                } else {
                    break;
                }
            }
        }
    }
}
