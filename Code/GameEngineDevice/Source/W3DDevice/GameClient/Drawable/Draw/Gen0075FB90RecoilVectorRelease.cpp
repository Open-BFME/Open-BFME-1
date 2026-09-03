// candidate for retail 0x0075FB90 (168B), currently ?d_0075fb90@@YAXXZ
// cl: /DNDEBUG /MD /EHsc /O2
// Free function (cdecl, 3 pointer params). Guards all three non-null, then
// requires (param1[0xAC] & 8). Walks 4 fixed slots at param1+0x80 (stride
// 0xC); each slot gates on a byte flag array param0[i+0x120]. Each gated
// slot holds an inline vector<T> (T size 0x3C) at [slot-4, slot); for each
// element with a non-null field at +8, calls param2's vtable slot 0x84
// (factory(0, val)); if that returns non-null, calls the result's vtable
// slot 0x190 (hide(1)) then decrements its refcount at +4 and, if it hits
// zero, calls the result's vtable slot 0 (release()).

class Gen0075FB90Factory
{
public:
    virtual void d000();
    virtual void d001();
    virtual void d002();
    virtual void d003();
    virtual void d004();
    virtual void d005();
    virtual void d006();
    virtual void d007();
    virtual void d008();
    virtual void d009();
    virtual void d010();
    virtual void d011();
    virtual void d012();
    virtual void d013();
    virtual void d014();
    virtual void d015();
    virtual void d016();
    virtual void d017();
    virtual void d018();
    virtual void d019();
    virtual void d020();
    virtual void d021();
    virtual void d022();
    virtual void d023();
    virtual void d024();
    virtual void d025();
    virtual void d026();
    virtual void d027();
    virtual void d028();
    virtual void d029();
    virtual void d030();
    virtual void d031();
    virtual void d032();
    virtual void *factory(int a, void *b);
};

class Gen0075FB90Result
{
public:
    virtual void release();
    virtual void d001();
    virtual void d002();
    virtual void d003();
    virtual void d004();
    virtual void d005();
    virtual void d006();
    virtual void d007();
    virtual void d008();
    virtual void d009();
    virtual void d010();
    virtual void d011();
    virtual void d012();
    virtual void d013();
    virtual void d014();
    virtual void d015();
    virtual void d016();
    virtual void d017();
    virtual void d018();
    virtual void d019();
    virtual void d020();
    virtual void d021();
    virtual void d022();
    virtual void d023();
    virtual void d024();
    virtual void d025();
    virtual void d026();
    virtual void d027();
    virtual void d028();
    virtual void d029();
    virtual void d030();
    virtual void d031();
    virtual void d032();
    virtual void d033();
    virtual void d034();
    virtual void d035();
    virtual void d036();
    virtual void d037();
    virtual void d038();
    virtual void d039();
    virtual void d040();
    virtual void d041();
    virtual void d042();
    virtual void d043();
    virtual void d044();
    virtual void d045();
    virtual void d046();
    virtual void d047();
    virtual void d048();
    virtual void d049();
    virtual void d050();
    virtual void d051();
    virtual void d052();
    virtual void d053();
    virtual void d054();
    virtual void d055();
    virtual void d056();
    virtual void d057();
    virtual void d058();
    virtual void d059();
    virtual void d060();
    virtual void d061();
    virtual void d062();
    virtual void d063();
    virtual void d064();
    virtual void d065();
    virtual void d066();
    virtual void d067();
    virtual void d068();
    virtual void d069();
    virtual void d070();
    virtual void d071();
    virtual void d072();
    virtual void d073();
    virtual void d074();
    virtual void d075();
    virtual void d076();
    virtual void d077();
    virtual void d078();
    virtual void d079();
    virtual void d080();
    virtual void d081();
    virtual void d082();
    virtual void d083();
    virtual void d084();
    virtual void d085();
    virtual void d086();
    virtual void d087();
    virtual void d088();
    virtual void d089();
    virtual void d090();
    virtual void d091();
    virtual void d092();
    virtual void d093();
    virtual void d094();
    virtual void d095();
    virtual void d096();
    virtual void d097();
    virtual void d098();
    virtual void d099();
    virtual void hide(int flag);
};

extern "C" void Gen_0075FB90(void *param0, unsigned char *param1, Gen0075FB90Factory *param2)
{
    if (!param0)
        return;
    if (!param1)
        return;
    if (!param2)
        return;
    if (!(param1[0xAC] & 8))
        return;

    int i = 0;
    unsigned char *slot = param1 + 0x80;
    for (; i < 4; ++i, slot += 0xC) {
        if (!*((unsigned char *)param0 + i + 0x120))
            continue;

        unsigned char *p = *(unsigned char **)(slot - 4);
        unsigned char *listEnd = *(unsigned char **)slot;
        if (p == listEnd)
            continue;

        do {
            void *val = *(void **)(p + 8);
            if (val) {
                Gen0075FB90Result *obj = (Gen0075FB90Result *)param2->factory(0, val);
                if (obj) {
                    obj->hide(1);
                    if (--*(int *)((char *)obj + 4) == 0)
                        obj->release();
                }
            }
            listEnd = *(unsigned char **)slot;
            p += 0x3C;
        } while (p != listEnd);
    }
}
