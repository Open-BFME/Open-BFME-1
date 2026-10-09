// Clean reconstruction of the map-object thing-name validation predicate.

extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *left, const char *right, unsigned int count);

struct Rva00137E20StringData
{
	int refs;
	int length;
	char text[1];
};

class Rva00137E20String
{
public:
	const char *str() const
	{
		return data ? data->text : "";
	}

private:
	Rva00137E20StringData *data;
};

struct Rva00137E20ThingNameIterator
{
	void *node;
};

static bool operator!=(const Rva00137E20ThingNameIterator &left,
	const Rva00137E20ThingNameIterator &right)
{
	return left.node != right.node;
}

class AsciiString;
struct Rva001366A0Value;
struct Rva001366A0ExtractKey;
class Rva00137E20ThingNameRegistry;
namespace rts { template <class Key> struct hash; }
namespace _STL
{
template <class Key> struct equal_to;
template <class Value> class allocator;
template <class Value> struct _Hashtable_node;
template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
    friend class ::Rva00137E20ThingNameRegistry;
    template <class Lookup>
    _Hashtable_node<Value> *_M_find(const Lookup &) const;
};
}

class Rva00137E20ThingNameRegistry
{
public:
	Rva00137E20ThingNameIterator find(const Rva00137E20String &name)
	{
		Rva00137E20ThingNameIterator value = {
            reinterpret_cast<const _STL::hashtable<Rva001366A0Value,
                AsciiString, rts::hash<AsciiString>, Rva001366A0ExtractKey,
                _STL::equal_to<AsciiString>, _STL::allocator<Rva001366A0Value> > *>(this)
                ->_M_find<AsciiString>(*reinterpret_cast<const AsciiString *>(&name)) };
		return value;
	}

	Rva00137E20ThingNameIterator end() const
	{
		Rva00137E20ThingNameIterator value = { 0 };
		return value;
	}

};

class Rva00137E20ThingNameFilter
{
public:
	bool acceptsThingTemplateName(const Rva00137E20String &name);

private:
	char padding00[0x10];
	Rva00137E20ThingNameRegistry registry;
};

bool Rva00137E20ThingNameFilter::acceptsThingTemplateName(
	const Rva00137E20String &name)
{
	if (strncmp(name.str(), "***TESTING", 10) == 0) {
		return true;
	}

	return registry.find(name) != registry.end();
}
