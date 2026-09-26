// cl: /DNDEBUG /MD /EHsc
class Rva00786BD0Owner
{
public:
	void *find(unsigned key);
};

// ?Rva00786C70Find@@YAPAXPAVRva00786BD0Owner@@I@Z
void *Rva00786C70Find(Rva00786BD0Owner *owner, unsigned key)
{
	if (!owner) return 0;
	return owner->find(key);
}
