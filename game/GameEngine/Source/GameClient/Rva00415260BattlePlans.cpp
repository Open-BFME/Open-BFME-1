// cl: /DNDEBUG /MD /EHsc
// RVA 0x00415260: battle-plan icon rendering. The old Set_HTree claim
// ended after its generic SEH prologue; the tail calls Player and Anim2D APIs.
class Anim2DTemplate;
class Anim2DCollection;
class Anim2D {
    char storage[0x34];
public:
    Anim2D(Anim2DTemplate *, Anim2DCollection *);
    unsigned getCurrentFrameWidth() const;
    unsigned getCurrentFrameHeight() const;
    void draw(int,int,int,int);
};
class Object;
class Player {
public:
    bool doesObjectQualifyForBattlePlan(Object *) const;
    char pad00[0x64];
    int bombard, hold, search;
    int count() const { return bombard + hold + search; }
};
class Rva000C9B10 { public: void *get(int); };
class Object { public: Player *getControllingPlayer() const; };
class DrawableIconInfo { public: void *vtable; Anim2D *icons[14]; };
class Rva00415260Owner;
class Drawable {
    friend class Rva00415260Owner;
public:
    DrawableIconInfo *getIconInfo();
private:
    static Anim2DTemplate **s_animationTemplates;
};
class BfmeThingES { public: void bfmeDropES(int); };
extern Anim2DCollection *TheAnim2DCollection;
class Rva00415260Owner {
    char pad00[0xfc];
    Object *object;
    char pad100[0x2c4];
    int x, y;
public:
    void draw();
private:
    DrawableIconInfo *icons() { return ((Drawable *)this)->getIconInfo(); }
    void drop(int index) { ((BfmeThingES *)this)->bfmeDropES(index); }
};
void Rva00415260Owner::draw()
{
    Object *obj = object;
    if (!obj) return;
    Player *player = obj->getControllingPlayer();
    if (player && player->count() > 0 && player->doesObjectQualifyForBattlePlan(obj)) {
        if (((Rva000C9B10 *)player)->get(1)) {
            if (!icons()->icons[7])
                icons()->icons[7] = new Anim2D(Drawable::s_animationTemplates[7], TheAnim2DCollection);
            int width = icons()->icons[7]->getCurrentFrameWidth();
            int height = icons()->icons[7]->getCurrentFrameHeight();
            int screenX = x;
            int screenY = y + height;
            icons()->icons[7]->draw(screenX,screenY,width,height);
        } else drop(7);
        if (((Rva000C9B10 *)player)->get(2)) {
            if (!icons()->icons[8])
                icons()->icons[8] = new Anim2D(Drawable::s_animationTemplates[8], TheAnim2DCollection);
            int width = icons()->icons[8]->getCurrentFrameWidth();
            int height = icons()->icons[8]->getCurrentFrameHeight();
            int screenX = x;
            int screenY = y + height;
            icons()->icons[8]->draw(screenX+width,screenY,width,height);
        } else drop(8);
        if (((Rva000C9B10 *)player)->get(3)) {
            if (!icons()->icons[9])
                icons()->icons[9] = new Anim2D(Drawable::s_animationTemplates[9], TheAnim2DCollection);
            int width = icons()->icons[9]->getCurrentFrameWidth();
            int height = icons()->icons[9]->getCurrentFrameHeight();
            int screenX = x;
            int screenY = y + height;
            icons()->icons[9]->draw(screenX+width*2,screenY,width,height);
        } else drop(9);
    }
}
