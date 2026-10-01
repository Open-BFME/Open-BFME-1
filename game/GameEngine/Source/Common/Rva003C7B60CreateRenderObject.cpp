// ?create@Rva003C7B60Owner@@QAEXPAXVAsciiString@@H_N@Z
// Retail callers prove this callback ABI and place the render matrix at +0x18.
// The shared RenderObjClass view places it 0x18 bytes later, so this TU keeps a local vtable view.
// cl: /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWMath/matrix3d.h"

class RenderObjClass;

class Rva003C7B60RenderObjView
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0a();
    virtual void slot0b();
    virtual void slot0c();
    virtual void slot0d();
    virtual void slot0e();
    virtual void slot0f();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void validateTransform() const;
    virtual void setTransform(const Matrix3D &transform);

    const Matrix3D &getTransform() const
    {
        validateTransform();
        return *(const Matrix3D *)((const char *)this + 0x18);
    }
};

class Rva003C7B60HolderView
{
public:
    char m_pad00[8];
    float m_field08;
};

class Rva003C7B60Owner
{
public:
    void create(void *output, AsciiString name, int flag, bool makeUnique);

private:
    char m_pad00[4];
    Rva003C7B60HolderView *m_holder;
};

class BfmeThingESM;
class BfmeHostESM
{
public:
    void bfmeMarkESM(BfmeThingESM *thing, int flag);
};

class GlobalData;

// Retail [0x012ED5C8] is EA's writable GlobalData (Common/GlobalData.cpp); this
// file only reaches through it for a byte probe.
extern GlobalData *TheWritableGlobalData;
extern BfmeHostESM *g_bfmeStateDF;
extern const char g_bfmeEmptyAscii[];
RenderObjClass *Create_Render_Obj(const char *name);
void Rva00739B30(RenderObjClass *object, bool geometry);

class Rva003C7B60RegistryView
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0a(RenderObjClass *object);
};

void Rva003C7B60Owner::create(
    void *output, AsciiString name, int flag, bool makeUnique)
{
    RenderObjClass **result = (RenderObjClass **)output;
    if (*result == 0)
    {
        const char *buffer = *(const char **)&name;
        const char *objectName = buffer != 0 ? buffer + 8 : g_bfmeEmptyAscii;
        RenderObjClass *object = Create_Render_Obj(objectName);
        if (object != 0)
        {
            if (makeUnique != 0)
                Rva00739B30(object, false);

            Matrix3D transform(true);
            Rva003C7B60RenderObjView *renderView = (Rva003C7B60RenderObjView *)object;
            const Matrix3D &current = renderView->getTransform();
            Vector3 position = current.Get_Translation();
            if (*(unsigned char *)((char *)TheWritableGlobalData + 0x8f) != 0)
                position.Z = -100.0f;
            else
                position.Z = m_holder->m_field08;
            transform.Set_Translation(position);
            renderView->setTransform(transform);
            g_bfmeStateDF->bfmeMarkESM((BfmeThingESM *)object, flag);
            ((Rva003C7B60RegistryView *)g_bfmeStateDF)->slot0a(object);
        }
        *result = object;
    }
}
