// Windows XP firewall setup, retail RVA 0x006909B0 (313 bytes).
// The constructor and applicationIsEnabled establish the same 0x14-byte
// owner; this method obtains the manager, local policy and current profile.
typedef long HRESULT;
void *operator new[](unsigned int);
struct FirewallInterface;
struct FirewallVtable {
    void *unused[2];
    unsigned long (__stdcall *release)(FirewallInterface *);
    void *dispatch[4];
    HRESULT (__stdcall *getChild)(FirewallInterface *, FirewallInterface **);
    HRESULT (__stdcall *getEnabled)(FirewallInterface *, short *);
};
struct FirewallInterface { FirewallVtable *vtable; };
struct FirewallGuid { unsigned long a; unsigned short b, c; unsigned char d[8]; };
// Retail VA 0x0111B8F4 / 0x0111B908: NetFwMgr class and INetFwMgr.
extern const FirewallGuid CLSID_BfmeNetFwMgr = {
    0x304ce942, 0x6e39, 0x40d8, {0x94,0x3a,0xb9,0x13,0xc4,0x0c,0x9c,0xd4}
};
extern const FirewallGuid IID_BfmeNetFwMgr = {
    0xf7898af5, 0xcac4, 0x4632, {0xa2,0xec,0xda,0x06,0xe5,0x11,0x1a,0xf2}
};
extern "C" __declspec(dllimport) HRESULT __stdcall CoCreateInstance(
    const FirewallGuid &, void *, unsigned long, const FirewallGuid &, void **);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *, const unsigned short *);

class BfmeThingTTD {
public:
    void initialize(const unsigned short *name, const unsigned short *imageFileName);
private:
    unsigned short *m_name, *m_imageFileName;
    bool m_initialized, m_applicationEnabled, m_firewallEnabled;
    char m_pad;
    HRESULT m_comResult;
    FirewallInterface *m_profile;
};

void BfmeThingTTD::initialize(const unsigned short *name, const unsigned short *imageFileName)
{
    FirewallInterface *manager = 0;
    FirewallInterface *policy = 0;
    m_name = new unsigned short[wcslen(name) + 1];
    m_imageFileName = new unsigned short[wcslen(imageFileName) + 1];
    wcscpy(m_name, name);
    wcscpy(m_imageFileName, imageFileName);
    m_initialized = false;
    m_firewallEnabled = false;
    HRESULT result = CoCreateInstance(CLSID_BfmeNetFwMgr, 0, 1,
        IID_BfmeNetFwMgr, reinterpret_cast<void **>(&manager));
    if (result < 0) {
        if (manager) manager->vtable->release(manager);
        return;
    }
    result = manager->vtable->getChild(manager, &policy);
    if (result < 0) {
        if (manager) manager->vtable->release(manager);
        if (policy) policy->vtable->release(policy);
        return;
    }
    result = policy->vtable->getChild(policy, &m_profile);
    if (result < 0) {
        if (manager) manager->vtable->release(manager);
        if (policy) policy->vtable->release(policy);
        return;
    }
    m_initialized = true;
    if (policy) policy->vtable->release(policy);
    if (manager) manager->vtable->release(manager);
    short enabled;
    result = m_profile->vtable->getEnabled(m_profile, &enabled);
    if (result >= 0 && enabled != 0) m_firewallEnabled = true;
}
