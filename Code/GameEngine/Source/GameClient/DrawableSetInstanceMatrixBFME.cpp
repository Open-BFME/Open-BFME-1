// cl: /DNDEBUG /MD /EHsc
// BFME's Drawable layout is different from the vendored Zero Hour header in
// this method.  SwayClientUpdate and StructureCollapseUpdate both witness the
// instance matrix at +0x198, while the retail body witnesses its history at
// +0x168, identity byte at +0x3af, expiration word at +0x1fc and frame at
// +0x304.  Keep that view local to this conversion.

typedef unsigned int UnsignedInt;
typedef float Real;

class Matrix3D
{
public:
    Matrix3D &operator=(const Matrix3D &m)
    {
        Row[0] = m.Row[0];
        Row[1] = m.Row[1];
        Row[2] = m.Row[2];
        return *this;
    }

    void Make_Identity()
    {
        Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
        Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
        Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
    }

private:
    class Vector4
    {
    public:
        void Set(Real x, Real y, Real z, Real w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        Vector4 &operator=(const Vector4 &v)
        {
            X = v.X;
            Y = v.Y;
            Z = v.Z;
            W = v.W;
            return *this;
        }

        Real X;
        Real Y;
        Real Z;
        Real W;
    };

    Vector4 Row[3];
};

class GameEngine
{
public:
    unsigned char m_pad000[0x34];
    int m_frame;
};

class ClientRoot4120
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25();
    virtual UnsignedInt getFrame();
};

extern GameEngine *TheGameEngine;
extern ClientRoot4120 *TheGameClient;

class Rva00411840Drawable
{
public:
    void setInstanceMatrix(const Matrix3D *instance, bool preservePrevious);

private:
    unsigned char m_pad000[0x168];
    Matrix3D m_previousInstance;
    Matrix3D m_instance;
    unsigned char m_pad1c8[0x1fc - 0x1c8];
    UnsignedInt m_expirationDate;
    unsigned char m_pad200[0x304 - 0x200];
    UnsignedInt m_frame;
    unsigned char m_pad308[0x3af - 0x308];
    bool m_instanceIsIdentity;
};

// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z
void Rva00411840Drawable::setInstanceMatrix(const Matrix3D *instance,
    bool preservePrevious)
{
    m_previousInstance = m_instance;
    if (instance)
    {
        m_instance = *instance;
        m_instanceIsIdentity = false;
    }
    else
    {
        m_instance.Make_Identity();
        m_instanceIsIdentity = true;
    }

    if (preservePrevious)
        m_previousInstance = m_instance;

    Real frame = (Real)TheGameEngine->m_frame;
    frame += (Real)TheGameClient->getFrame();
    m_frame = (UnsignedInt)frame;
    m_expirationDate = 0xffffffff;
}
