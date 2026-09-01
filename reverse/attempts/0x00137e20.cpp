// ?d_00137e20@@YAXXZ
// partial score=0.94 date=2026-08-31
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

class Rva00137E20ThingNameRegistry
{
public:
	void *find(const Rva00137E20String &name);
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

	void *entry = registry.find(name);
	bool found = entry != 0;
	return found;
}
