// cl: /DNDEBUG /MD /O2

class Rva0089CC10Object
{
public:
    int get() const;
};
class BfmeS1238
{
public:
    BfmeS1238 *bfmeAt1238B(int index);
};
extern void *g_Rva01337A28Index;

int Rva00898D20Get()
{
    Rva0089CC10Object *object = (Rva0089CC10Object *)g_Rva01337A28Index;
    if (object)
        return object->get();
    return 0;
}

BfmeS1238 *Rva00898D40At(void *unused, int index)
{
    BfmeS1238 *object = (BfmeS1238 *)g_Rva01337A28Index;
    if (object)
        return object->bfmeAt1238B(index);
    return 0;
}
