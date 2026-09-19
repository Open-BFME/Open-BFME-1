// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift LargeGroupAudioUpdateModuleData dtor __emit thunk to clean
// C++. Body calls an out-param remove on a global manager (SEH state 1), the
// member at +0x08 has an out-of-line dtor (state 0), and the base dtor is the
// inline vtable-store-only kind.

class LGA_Global
{
public:
    void remove(void **handle);
};

extern LGA_Global g_lgaGlobal;

class LGA_MemberObj
{
public:
    ~LGA_MemberObj();
};

class LGA_Base
{
public:
    virtual ~LGA_Base() {}
};

class LargeGroupAudioUpdateModuleData : public LGA_Base
{
public:
    virtual ~LargeGroupAudioUpdateModuleData();

private:
    unsigned int m_f4;
    LGA_MemberObj m_obj;
};

// ??1LargeGroupAudioUpdateModuleData@@UAE@XZ
LargeGroupAudioUpdateModuleData::~LargeGroupAudioUpdateModuleData()
{
    void *handle = this;
    g_lgaGlobal.remove(&handle);
}
