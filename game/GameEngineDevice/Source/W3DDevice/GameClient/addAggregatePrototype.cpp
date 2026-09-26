// ?addAggregatePrototype@@YAXPBDPAURva00971FA0Obj@@@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: 0x00971FA0 (181 B gap): register a render-object prototype
// built from a name and an owned object; drops the object when the name is
// missing or already registered.
struct Rva00971FA0Obj { virtual ~Rva00971FA0Obj(); };
class Rva00971CE0AggregatePrototype
{
public:
	Rva00971CE0AggregatePrototype(const char *name, void *object);
	char m_body[0x24];
};
bool Render_Obj_Exists(const char *name);
void Add_Prototype(void *prototype);
void addAggregatePrototype(const char *name, Rva00971FA0Obj *object)
{
	if (name && object) {
		if (Render_Obj_Exists(name)) {
			delete object;
			return;
		}
		Add_Prototype(new Rva00971CE0AggregatePrototype(name, object));
	} else if (object) {
		delete object;
	}
}
