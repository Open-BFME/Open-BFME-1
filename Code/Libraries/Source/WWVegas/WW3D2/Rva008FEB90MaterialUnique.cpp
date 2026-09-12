// cl: /EHs-c-
//
// Reconstruction of the 140-byte recursive render-object material
// uniquing helper at retail 0x008FEB90.  The nearby matched
// Rva00739B30RenderObjectUnique.cpp proves the BFME vtable layout and the
// Make_Unique -> Get_Material_Info -> Make_Vertex_Materials_Unique sequence.
// This candidate keeps the entry point address-derived until a named caller
// or emitter proves the production owner.

class MaterialInfoClass;
class MeshModelClass;
class MeshClass;

class RefCountClass {
public:
    virtual void Delete_This();
    int m_ref_count;
};

class RenderObjClass : public RefCountClass {
public:
    virtual void _bfme_ro_v1();
    virtual void _bfme_ro_v2();
    virtual int Class_ID() const;
    virtual void _bfme_ro_v4();
    virtual MeshClass *Mesh_Self();
    virtual void _bfme_ro_v6();
    virtual void _bfme_ro_v7();
    virtual void _bfme_ro_v8();
    virtual void _bfme_ro_v9();
    virtual void _bfme_ro_v10();
    virtual void _bfme_ro_v11();
    virtual void _bfme_ro_v12();
    virtual void _bfme_ro_v13();
    virtual void _bfme_ro_v14();
    virtual void _bfme_ro_v15();
    virtual void _bfme_ro_v16();
    virtual void _bfme_ro_v17();
    virtual void _bfme_ro_v18();
    virtual void _bfme_ro_v19();
    virtual void _bfme_ro_v20();
    virtual void _bfme_ro_v21();
    virtual void _bfme_ro_v22();
    virtual void _bfme_ro_v23();
    virtual void _bfme_ro_v24();
    virtual void _bfme_ro_v25();
    virtual void _bfme_ro_v26();
    virtual int Get_Num_Sub_Objects() const;
    virtual void _bfme_ro_v28();
    virtual RenderObjClass *Get_Sub_Object(int index) const;
    virtual void _bfme_ro_v30();
    virtual void _bfme_ro_v31();
    virtual void _bfme_ro_v32();
    virtual void _bfme_ro_v33();
    virtual void _bfme_ro_v34();
    virtual void _bfme_ro_v35();
    virtual void _bfme_ro_v36();
    virtual void _bfme_ro_v37();
    virtual void _bfme_ro_v38();
    virtual void _bfme_ro_v39();
    virtual void _bfme_ro_v40();
    virtual void _bfme_ro_v41();
    virtual void _bfme_ro_v42();
    virtual void _bfme_ro_v43();
    virtual void _bfme_ro_v44();
    virtual void _bfme_ro_v45();
    virtual void _bfme_ro_v46();
    virtual void _bfme_ro_v47();
    virtual void _bfme_ro_v48();
    virtual void _bfme_ro_v49();
    virtual void _bfme_ro_v50();
    virtual void _bfme_ro_v51();
    virtual void _bfme_ro_v52();
    virtual void _bfme_ro_v53();
    virtual void _bfme_ro_v54();
    virtual void _bfme_ro_v55();
    virtual void _bfme_ro_v56();
    virtual void _bfme_ro_v57();
    virtual void _bfme_ro_v58();
    virtual void _bfme_ro_v59();
    virtual void _bfme_ro_v60();
    virtual void _bfme_ro_v61();
    virtual void _bfme_ro_v62();
    virtual void _bfme_ro_v63();
    virtual void _bfme_ro_v64();
    virtual void _bfme_ro_v65();
    virtual void _bfme_ro_v66();
    virtual void _bfme_ro_v67();
    virtual void _bfme_ro_v68();
    virtual void _bfme_ro_v69();
    virtual void _bfme_ro_v70();
    virtual void _bfme_ro_v71();
    virtual void _bfme_ro_v72();
    virtual void _bfme_ro_v73();
    virtual void _bfme_ro_v74();
    virtual void _bfme_ro_v75();
    virtual void _bfme_ro_v76();
    virtual void _bfme_ro_v77();
    virtual void _bfme_ro_v78();
    virtual void _bfme_ro_v79();
    virtual void _bfme_ro_v80();
    virtual void _bfme_ro_v81();
    virtual void _bfme_ro_v82();
    virtual void _bfme_ro_v83();
    virtual MaterialInfoClass *Get_Material_Info() const;
};

class MaterialInfoClass : public RefCountClass {
public:
    void Make_Vertex_Materials_Unique();
};

class MeshModelClass : public RefCountClass {
public:
    void Make_Geometry_Unique();
};

class MeshClass : public RenderObjClass {
public:
    void Make_Unique(bool force_meshmdl_clone);
};

static void release(RefCountClass *object)
{
    if (object != 0 && --object->m_ref_count == 0) {
        object->Delete_This();
    }
}

void Rva008FEB90(RenderObjClass *object)
{
    if (object == 0) {
        return;
    }

    if (object->Class_ID() == 0) {
        MeshClass *mesh = object->Mesh_Self();
        mesh->Make_Unique(false);
        MaterialInfoClass *material = mesh->Get_Material_Info();
        material->Make_Vertex_Materials_Unique();
        release(material);
    } else {
        int count = object->Get_Num_Sub_Objects();
        for (int index = 0; index < count; ++index) {
            RenderObjClass *sub = object->Get_Sub_Object(index);
            Rva008FEB90(sub);
            release(sub);
        }
    }
}
