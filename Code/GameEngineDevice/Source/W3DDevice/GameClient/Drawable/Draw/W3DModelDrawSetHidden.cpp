// candidate for retail 0x00762640 (132B), currently ?d_00762640@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /O2
// W3DModelDraw method, thiscall(bool hidden). Toggles several sub-object
// pointers similar to ZH's W3DModelDraw::setHidden, but this BFME build also
// stamps a Drawable position into a track-like member and always tail-calls
// its own updateSubObjectsFromShroud() (pinned at retail 0x00762500, still
// gen-dump). The Drawable::getPosition() callee is pinned at retail
// 0x0004B12D. The remaining callee (retail 0x0072F390) is still unidentified;
// pinned here as a plain member so the call resolves.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
    const Coord3D *getPosition() const;
};

class BfmeRenderObjLikeD62640
{
public:
    virtual void d000(); virtual void d001(); virtual void d002(); virtual void d003();
    virtual void d004(); virtual void d005(); virtual void d006(); virtual void d007();
    virtual void d008(); virtual void d009(); virtual void d010(); virtual void d011();
    virtual void d012(); virtual void d013(); virtual void d014(); virtual void d015();
    virtual void d016(); virtual void d017(); virtual void d018(); virtual void d019();
    virtual void d020(); virtual void d021(); virtual void d022(); virtual void d023();
    virtual void d024(); virtual void d025(); virtual void d026(); virtual void d027();
    virtual void d028(); virtual void d029(); virtual void d030(); virtual void d031();
    virtual void d032(); virtual void d033(); virtual void d034(); virtual void d035();
    virtual void d036(); virtual void d037(); virtual void d038(); virtual void d039();
    virtual void d040(); virtual void d041(); virtual void d042(); virtual void d043();
    virtual void d044(); virtual void d045(); virtual void d046(); virtual void d047();
    virtual void d048(); virtual void d049(); virtual void d050(); virtual void d051();
    virtual void d052(); virtual void d053(); virtual void d054(); virtual void d055();
    virtual void d056(); virtual void d057(); virtual void d058(); virtual void d059();
    virtual void d060(); virtual void d061(); virtual void d062(); virtual void d063();
    virtual void d064(); virtual void d065(); virtual void d066(); virtual void d067();
    virtual void d068(); virtual void d069(); virtual void d070(); virtual void d071();
    virtual void d072(); virtual void d073(); virtual void d074(); virtual void d075();
    virtual void d076(); virtual void d077(); virtual void d078(); virtual void d079();
    virtual void d080(); virtual void d081(); virtual void d082(); virtual void d083();
    virtual void d084(); virtual void d085(); virtual void d086(); virtual void d087();
    virtual void d088(); virtual void d089(); virtual void d090(); virtual void d091();
    virtual void d092(); virtual void d093(); virtual void d094(); virtual void d095();
    virtual void d096(); virtual void d097(); virtual void d098(); virtual void d099();
    virtual void SetHidden(int hidden);
};

struct BfmeFlagFieldD62640
{
    unsigned char pad0[4];
    unsigned char flag; // +4
};

class BfmeTrackLikeD62640
{
public:
    void addCapEdgeToTrack(float x, float y);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
    void setHidden(unsigned char hidden);
private:
    void updateSubObjectsFromShroud(void);
    unsigned char m_unreconstructed_00[8];
    Drawable *m_drawable;                 // +0x08
    unsigned char m_unreconstructed_0c[0x2e - 0x0c];
    unsigned char m_unreconstructed_2e;   // +0x2e
    unsigned char m_unreconstructed_2f;
    unsigned char m_unreconstructed_30;   // +0x30
    unsigned char m_unreconstructed_31[3];
    BfmeRenderObjLikeD62640 *m_renderObject; // +0x34
    unsigned char m_unreconstructed_38[0x3c - 0x38];
    BfmeFlagFieldD62640 *m_shadow;         // +0x3c
    BfmeFlagFieldD62640 *m_terrainDecal;   // +0x40
    BfmeTrackLikeD62640 *m_trackRenderObject; // +0x44
    unsigned char m_unreconstructed_48[0x132 - 0x48];
    unsigned char m_unreconstructed_132;   // +0x132 (member of *m_unreconstructed_04)
    unsigned char m_unreconstructed_133[0x232 - 0x133];
    unsigned char m_unreconstructed_232;   // +0x232
};

struct BfmeSubD62640
{
    unsigned char pad[0x132];
    unsigned char flag132;
};

void W3DModelDraw::setHidden(unsigned char hidden)
{
    if (m_unreconstructed_232) {
        BfmeSubD62640 *sub = *(BfmeSubD62640 **)((unsigned char *)this + 4);
        if (!sub->flag132)
            return;
    }

    m_unreconstructed_30 = hidden;
    if (m_renderObject)
        m_renderObject->SetHidden(hidden);

    if (m_shadow)
        m_shadow->flag = (hidden == 0);

    unsigned char notHidden = (hidden == 0);
    m_unreconstructed_2e = notHidden;
    if (m_terrainDecal)
        m_terrainDecal->flag = notHidden;

    if (m_trackRenderObject && hidden) {
        const Coord3D *pos = m_drawable->getPosition();
        m_trackRenderObject->addCapEdgeToTrack(pos->x, pos->y);
    }

    updateSubObjectsFromShroud();
}
