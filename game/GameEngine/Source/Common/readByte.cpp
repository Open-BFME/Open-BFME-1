// cl: /DNDEBUG /MD /EHsc

struct Rva005BD460Object
{
    char padding[0x1c];
    unsigned char value;
};

unsigned char readByte(Rva005BD460Object *object)
{
    return object->value;
}
