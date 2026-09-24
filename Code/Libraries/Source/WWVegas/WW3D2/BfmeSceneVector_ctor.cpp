// ??0BfmeSceneVector@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
struct Rva00943FF0Bounds { float v[6]; };
struct BfmeSceneVectorElement;
struct Gen_00943CF0_Node;
struct Gen_uw_0002e866;
class BfmeSceneVector
{
public:
    BfmeSceneVector();
    void clear(Gen_uw_0002e866 *objects);
    void process(Gen_00943CF0_Node **objects);
    void Set_Level(unsigned int level);
    void rva00943FF0(const Rva00943FF0Bounds &bounds);
private:
    Rva00943FF0Bounds bounds;
    BfmeSceneVectorElement *vector;
    int vector_max;
    float scale;
    unsigned int level_mask;
};
BfmeSceneVector::BfmeSceneVector()
{
    vector = 0;
    vector_max = 0;
    Rva00943FF0Bounds initial;
    initial.v[0] = 0.0f;
    initial.v[1] = 0.0f;
    initial.v[2] = 0.0f;
    initial.v[3] = 0.0f;
    initial.v[4] = 0.0f;
    initial.v[5] = 0.0f;
    rva00943FF0(initial);
    Set_Level(0);
}
