// cl: /DNDEBUG /MD

class Rva00589DD0DwordGetter
{
public:
    int get(void);
};

int Rva00589DD0DwordGetter::get(void)
{
    return *(int *)((unsigned char *)this + 4);
}
