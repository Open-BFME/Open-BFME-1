// cl: /DNDEBUG /MD /EHsc
struct Rva007882F0Value { unsigned value; };
class Rva007882F0PointerMap
{
public:
	Rva007882F0Value *lookup(unsigned key);
};

// ?Rva00788A00Assign@@YAXPAVRva007882F0PointerMap@@II@Z
void Rva00788A00Assign(Rva007882F0PointerMap *owner, unsigned key, unsigned value)
{
	if (owner) {
		Rva007882F0Value *entry = owner->lookup(key);
		if (entry) entry->value = value;
	}
}
