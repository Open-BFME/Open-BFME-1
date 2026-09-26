// ?operation@Rva00212610Owner@@QAEXM_N@Z
// partial score=0.368421 date=2026-09-25
// ?operation@Rva00212610Owner@@QAEXM_N@Z
// Unused virtual slots reserve positions only; their signatures are not claimed.
// Address-derived owner for the secondary BodyModule interface.  The +0x08,
// +0x0C, +0x10 and +0x1C float offsets and this adjustments follow the retail
// body; they are not ActiveBody's primary layout.
struct Rva00211890Coord
{
    float x, y, z;
};

struct Rva00212610Object
{
    unsigned char beforePosition[0x38];
    Rva00211890Coord position;
};

class Rva00212610Owner
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
    virtual void slot80(float value, float zero);

    unsigned char beforeCurrent[4];
    float current;
    float previous;
    float maximum;
    unsigned char beforeInitial[8];
    float initial;
    void operation(float percent, bool mode);
};

extern float g_01076C24;
extern float GetGameLogicRandomValueReal(float low, float high, char *file, int line);

class Rva00211890Owner
{
public:
    void applyAt(float amount, const Rva00211890Coord *point);
};

void Rva00212610Owner::operation(float percent, bool mode)
{
    if (percent > 100.0f)
        maximum = percent * maximum * .01f;
    float factor = percent * .01f;

    if (mode)
    {
        previous = current;
        current += factor * maximum - current;

        Rva00212610Object *object = *(Rva00212610Object **)((char *)this - 8);
        Rva00211890Coord original = object->position;
        Rva00211890Coord point;
        point.x = original.x + GetGameLogicRandomValueReal(-1.0f, 1.0f,
            (char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp", 0x484);
        point.y = original.y + GetGameLogicRandomValueReal(-1.0f, 1.0f,
            (char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp", 0x485);
        point.z = original.z + GetGameLogicRandomValueReal(-1.0f, 1.0f,
            (char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp", 0x486);

        ((Rva00211890Owner *)((char *)this - 0x10))->applyAt(
            (1.0f - factor) * maximum, &point);
    }
    else
    {
        slot80(factor * initial - current, 0.0f);
    }
}
