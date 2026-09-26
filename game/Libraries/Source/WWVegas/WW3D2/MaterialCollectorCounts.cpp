// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME MaterialCollector vectors have 0x18-byte strides. The matched
// constructor, Reset, Add and Peek bodies establish the three count slots.
// Only the ActiveCount fields are needed by this translation-unit view.
struct BfmeCollectorVectorCountView
{
    unsigned char VectorPrefix[0x10];
    int ActiveCount;
    unsigned char VectorSuffix[4];
};
class MaterialCollectorClass
{
    BfmeCollectorVectorCountView Shaders;
    BfmeCollectorVectorCountView VertexMaterials;
    BfmeCollectorVectorCountView Textures;
public:
    int Get_Shader_Count(void);
    int Get_Vertex_Material_Count(void);
    int Get_Texture_Count(void);
};

// 0x0092F500, full 4-byte body; active count at this+0x10.
int MaterialCollectorClass::Get_Shader_Count(void)
{
    return Shaders.ActiveCount;
}

// 0x0092F510, full 4-byte body; active count at this+0x28.
int MaterialCollectorClass::Get_Vertex_Material_Count(void)
{
    return VertexMaterials.ActiveCount;
}

// 0x0092F520, full 4-byte body; active count at this+0x40.
int MaterialCollectorClass::Get_Texture_Count(void)
{
    return Textures.ActiveCount;
}
