// cl: /DNDEBUG /MD /EHsc

#include <stddef.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass
{
public:
    int vtable;
    int references;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
    int vtable;
    int references;
};

struct MatPassTaskClass;

class MatPassTaskPoolClass
{
public:
    MatPassTaskClass *Allocate_Object_Memory();
};

extern MatPassTaskPoolClass MatPassTaskPool;

struct MatPassTaskClass
{
    MaterialPassClass *pass;
    MeshClass *mesh;
    MatPassTaskClass *next;

    MatPassTaskClass(MaterialPassClass *new_pass, MeshClass *new_mesh) :
        pass(new_pass), mesh(new_mesh), next(0)
    {
        ++pass->references;
        ++mesh->references;
    }

    static void *operator new(size_t)
    {
        return MatPassTaskPool.Allocate_Object_Memory();
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8RigidFVFCategoryContainer
{
    unsigned char prefix[0xcc];
    MatPassTaskClass *delayed_matpass_head;
    MatPassTaskClass *delayed_matpass_tail;
    unsigned char middle[0x15];
    bool AnyDelayedPassesToRender;

public:
    virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
};

void DX8RigidFVFCategoryContainer::Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh)
{
    MatPassTaskClass *task = new MatPassTaskClass(pass, mesh);

    if (delayed_matpass_head == 0) {
        delayed_matpass_head = task;
        delayed_matpass_tail = task;
    } else {
        delayed_matpass_tail->next = task;
        delayed_matpass_tail = task;
    }
    AnyDelayedPassesToRender = true;
}
