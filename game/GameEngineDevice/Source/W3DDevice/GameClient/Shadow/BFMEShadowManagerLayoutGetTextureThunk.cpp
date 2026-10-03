// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib

class W3DShadowTexture;

void d_007afd10();

class BFMEShadowManagerLayout
{
public:
    W3DShadowTexture *getTexture(const char *name);
};

class BFMEShadowManagerLayoutGetTextureShim
{
public:
    W3DShadowTexture *getTexture(const char *);
};

W3DShadowTexture *BFMEShadowManagerLayout::getTexture(const char *name)
{
    union {
        void (*asFunction)(void);
        W3DShadowTexture *(BFMEShadowManagerLayoutGetTextureShim::*asMember)(const char *);
    } target;
    target.asFunction = d_007afd10;
    return (((BFMEShadowManagerLayoutGetTextureShim *)this)->*target.asMember)(name);
}
