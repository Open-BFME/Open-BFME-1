// cl: /DNDEBUG /MD /EHsc
// readable body of ?Set_Element@MatBufferClass@@QAEXHPAVVertexMaterialClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp
// readable body of ?Set_Material@MeshMatDescClass@@QAEXHPAVVertexMaterialClass@@H@Z: Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
    virtual void Release();
    int references;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.h
class MatBufferClass
{
    unsigned char prefix[8];
    VertexMaterialClass **Array;

public:
    void Set_Element(int index, VertexMaterialClass *material);
};

void MatBufferClass::Set_Element(int index, VertexMaterialClass *material)
{
    if (material != 0)
        ++material->references;

    VertexMaterialClass *old = Array[index];
    if (old != 0) {
        --old->references;
        if (old->references == 0)
            old->Release();
    }
    Array[index] = material;
}

class MeshMatDescClass
{
public:
    MatBufferClass *Get_Material_Array(int pass, bool create);
    void Set_Material(int index, VertexMaterialClass *material, int pass);
};

void MeshMatDescClass::Set_Material(int index, VertexMaterialClass *material, int pass)
{
    MatBufferClass *materials = Get_Material_Array(pass, true);
    materials->Set_Element(index, material);
}
