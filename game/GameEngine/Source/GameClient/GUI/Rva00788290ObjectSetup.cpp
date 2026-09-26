// cl: /O2 /Ob0

struct Rva00788290Source
{
	char m_pad00[0x1c];
	int m_value1c;
	int m_value20;
};

class Rva00788290Object
{
	public:
	char m_pad00[0x1c];
	int m_state1c;
	int m_value20;
	char m_pad24[0x1c];
	int m_value40;
	int m_value44;
	char m_pad48[0x10];
	unsigned int m_flags58;
	Rva00788290Source *m_source5c;
};

class Rva00788290Allocation
{
public:
	Rva00788290Allocation *bfmeConstruct00788290(Rva00788290Object *source);
	char m_storage[0x30];
};

void *__cdecl bfmeAllocate00788290(unsigned int size);

// @?bfmeSetup00788290@@YAPAXPAVRva00788290Object@@@Z 0x00788290
void *__cdecl bfmeSetup00788290(Rva00788290Object *object)
{
	if (object == 0)
		return 0;

	if ((object->m_flags58 & 0x406) == 0) {
		volatile Rva00788290Source *source = object->m_source5c;
		object->m_value40 = source->m_value1c;
		object->m_value44 = source->m_value20;
		object->m_value20 = source->m_value1c;
		object->m_state1c = 1;
		return object->m_source5c;
	}

	void *memory = bfmeAllocate00788290(sizeof(Rva00788290Allocation));
	if (memory != 0)
		return ((Rva00788290Allocation *)memory)->bfmeConstruct00788290(object);
	return 0;
}
