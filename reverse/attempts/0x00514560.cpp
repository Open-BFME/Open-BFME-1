// ?h00514560@Glo00EF4988@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc

class GameWindow;
void __cdecl operator delete(void *);
namespace _STL { template <bool threads, int instance> class __node_alloc { public: static void _M_deallocate(void *, unsigned); }; }

class Rva00514560IntVector
{
public:
    Rva00514560IntVector() : m_begin(0), m_end(0), m_capacity(0) {}
    ~Rva00514560IntVector()
    {
        if (m_begin) {
            unsigned bytes = (unsigned)(m_capacity - m_begin) * sizeof(int);
            if (bytes > 0x80)
                operator delete(m_begin);
            else
                _STL::__node_alloc<true, 0>::_M_deallocate(m_begin, bytes);
        }
    }
    int *begin() { return m_begin; }
    int *end() { return m_end; }
private:
    int *m_begin;
    int *m_end;
    int *m_capacity;
};

struct Rva00579160Manager
{
    void fire(void *target, const char *name, int a, int b, int c, int d, int e, int f);
};
extern Rva00579160Manager *Rva00579160TheManager;

class GameSpyInfo
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
    virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
    virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
    virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
    virtual void bfmeSlot72(int value);
};
extern GameSpyInfo *TheGameSpyInfo;

class Glo00EF4988
{
public:
    void h00514560();
    int rva00513BF0(GameWindow *window, Rva00514560IntVector *values, int kind, bool enabled);

private:
    unsigned char m_unmodelled000[0x250];
    void *m_target;
    unsigned char m_unmodelled254[0x264 - 0x254];
    GameWindow *m_window;
    unsigned char m_unmodelled268[0x292 - 0x268];
    bool m_addDirty;
    bool m_addEnabled;
    bool m_removeDirty;
    bool m_removeEnabled;
};

void Glo00EF4988::h00514560()
{
    Rva00514560IntVector values;

    if (m_addDirty || m_addEnabled) {
        m_addDirty = false;
        m_addEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableAddButton", 0, 0, 0, 0, 0, 0);
    }

    if (m_removeDirty || m_removeEnabled) {
        m_removeDirty = false;
        m_removeEnabled = false;
        Rva00579160TheManager->fire(m_target, "DisableRemoveButton", 0, 0, 0, 0, 0, 0);
    }

    if (rva00513BF0(m_window, &values, 7, true) > 0) {
        int *begin = values.begin();
        int *end = values.end();
        for (int *it = begin; it != end; ++it)
            TheGameSpyInfo->bfmeSlot72(*it);
    }
}
