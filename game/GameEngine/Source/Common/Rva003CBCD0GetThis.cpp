// cl: /DNDEBUG /MD

// The carved boundary at 0x003CBCE0 contains only a return.
void Rva003CBCE0Noop()
{
}

class Rva003CBCD0Object
{
public:
    Rva003CBCD0Object *getThis();
};

Rva003CBCD0Object *Rva003CBCD0Object::getThis()
{
    return this;
}
