// ?addShadow@W3DShadowManager@@QAEPAVShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@2@PAVDrawable@@@Z
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Shadow
{
public:
    struct ShadowTypeInfo
    {
        char m_padding[0x80];
        int m_type;
    };
};

class RenderObjClass
{
};

class Drawable
{
};

class Gen_01306F18
{
public:
    Shadow *addShadow(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
};

class Gen_01307178
{
public:
    Shadow *createShadow(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
};

class Gen_01306DF0
{
public:
    Shadow *addShadow(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
};

extern Gen_01306F18 *g_01306F18;
extern Gen_01307178 *g_01307178;
extern Gen_01306DF0 *g_01306DF0;

class W3DShadowManager
{
public:
    Shadow *addShadow(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
};

static const unsigned char kShadowAction[64] = {
    0, 1, 3, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

enum ShadowAction
{
    SHADOW_ACTION_PROJECTED,
    SHADOW_ACTION_VOLUMETRIC,
    SHADOW_ACTION_BUFFER,
    SHADOW_ACTION_NONE
};

Shadow *W3DShadowManager::addShadow(
    RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
    int type = 2;
    if (shadowInfo)
        type = shadowInfo->m_type;

    if (type <= 0x80) {
        if (type == 0x80) {
            if (g_01306F18)
                return g_01306F18->addShadow(robj, shadowInfo, draw);
        } else {
            switch (type) {
            case 1:
                if (g_01306DF0)
                    return g_01306DF0->addShadow(robj, shadowInfo, draw);
                break;
            case 2:
                if (g_01306F18)
                    return g_01306F18->addShadow(robj, shadowInfo, draw);
                break;
            case 4:
                if (g_01307178)
                    return g_01307178->createShadow(robj, shadowInfo, draw);
                break;
            case 8:
            case 16:
            case 32:
            case 64:
                break;
            default:
                break;
            }
        }
    } else {
        switch (type) {
        case 0x100:
            if (g_01306F18)
                return g_01306F18->addShadow(robj, shadowInfo, draw);
            break;
        case 0x400:
        case 0x800:
        case 0x1000:
            if (g_01306DF0)
                return g_01306DF0->addShadow(robj, shadowInfo, draw);
            break;
        default:
            break;
        }
    }

    return 0;
}
