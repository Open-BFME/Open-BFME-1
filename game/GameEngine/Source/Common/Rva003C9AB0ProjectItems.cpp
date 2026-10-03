// cl: /DNDEBUG /MD
//
// The refresh003CAD90 caller reaches this body through the 0x00033EBA ILT.
// The retail loop walks the owner range at +0x30 and +0x34, calls the
// projector with each item source at +0x04, and stores two point words at the
// target's +0x10 and +0x14 fields. The projector entry at 0x003C9470 is the
// matched Rva003C9470Owner::fallback body; its two-word output is this pair.

struct Gen003BC9C0Pair {
	volatile unsigned int x;
	volatile unsigned int y;
};

struct Gen003C9470Owner {
	void fill(void *source, Gen003BC9C0Pair *out);
};

struct Rva003C9470Context;
class Rva003C9470Key {};
struct Rva003C9470Output;

class Rva003C9470Owner {
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);

private:
	char m_pad00[0x24];
	Rva003C9470Context *m_context;
};

struct Rva003C9AB0Target {
	char m_pad[0x10];
	unsigned int x;
	unsigned int y;
};

struct Rva003C9AB0Item {
	int m_0;
	char m_source[0xe8];
	Rva003C9AB0Target *m_target;
};

struct Rva003C9AB0Owner {
	char m_pad[0x30];
	Rva003C9AB0Item **m_begin;
	Rva003C9AB0Item **m_end;

	unsigned int size() const {
		Rva003C9AB0Item **end = m_end;
		Rva003C9AB0Item **begin = m_begin;
		return end - begin;
	}

	void projectItems(int unused, Gen003C9470Owner *projector);
};

void Rva003C9AB0Owner::projectItems(int unused,
	Gen003C9470Owner *projector)
{
	Rva003C9AB0Owner *owner = this;
	unsigned int i = 0;
	unsigned int count = owner->size();
	if (i < count) {
		do {
			Gen003BC9C0Pair p;
			((Rva003C9470Owner *)projector)->fallback(
				(Rva003C9470Key *)owner->m_begin[i]->m_source,
				(Rva003C9470Output *)&p);
			Rva003C9AB0Target *t = owner->m_begin[i]->m_target;
			unsigned int x = p.x;
			unsigned int y = p.y;
			t->x = x;
			t->y = y;
			++i;
		} while (i < owner->size());
	}
}
