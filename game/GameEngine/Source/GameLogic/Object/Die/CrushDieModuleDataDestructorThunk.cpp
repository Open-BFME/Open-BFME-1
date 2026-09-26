// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift CrushDieModuleData dtor __emit thunk to clean C++.
// Retail destroys the 0x70-element array member at this+0x34 through
// __ehvec_dtor under an SEH frame, then runs the inlined base dtor (base
// vtable store). The derived class emits no vtable store of its own.

class CrushDieElement
{
public:
    ~CrushDieElement();

private:
    unsigned char m_pad[0x70];
};

class CrushDieModuleDataBase
{
public:
    virtual ~CrushDieModuleDataBase() {}

private:
    unsigned char m_pad[0x30];
};

class __declspec(novtable) CrushDieModuleData : public CrushDieModuleDataBase
{
public:
    virtual ~CrushDieModuleData();

private:
    CrushDieElement m_arr[4];
};

// ??1CrushDieModuleData@@UAE@XZ
CrushDieModuleData::~CrushDieModuleData()
{
}
