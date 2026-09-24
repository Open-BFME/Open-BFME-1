// cl: /O2 /DNDEBUG /MD
// Retail 0x009448C0 / 0x009448D0. Both adjust the receiver by +0x34
// and tail-call the matched BfmeSceneVector methods below.
struct Rva00943FF0Bounds { float value[6]; };
class BfmeSceneVector
{
public:
    void rva00943FF0(const Rva00943FF0Bounds &bounds);
    void Set_Level(unsigned int level);
private:
    Rva00943FF0Bounds m_bounds;
    void *m_vector;
    int m_vectorMax;
    float m_scale;
    unsigned int m_levelMask;
};
class Rva009448C0SceneView
{
public:
    void forwardBounds(const Rva00943FF0Bounds &bounds);
    void rva009448D0(unsigned int level);
private:
    unsigned char m_prefix[0x34];
    BfmeSceneVector m_grid;
};
void Rva009448C0SceneView::forwardBounds(const Rva00943FF0Bounds &bounds)
{
    m_grid.rva00943FF0(bounds);
}
void Rva009448C0SceneView::rva009448D0(unsigned int level)
{
    m_grid.Set_Level(level);
}
