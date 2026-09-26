// cl: /DNDEBUG /MD /EHsc
struct Rva007849C0Object
{
    void *m_slot0;
};
struct Rva007849C0Owner
{
    unsigned int m_slot0;
    Rva007849C0Object *m_object;
};
void Rva007849C0Clear(Rva007849C0Owner *owner)
{
    Rva007849C0Object *object = owner->m_object;
    if (object)
    {
        object->m_slot0 = 0;
        ::operator delete(object);
    }
    owner->m_object = 0;
}
