// Address-derived status fallback at retail 0x003C9470.

extern const char g_bfmeEmptyAscii[];

struct Rva003C9470ObjectPair
{
	unsigned int m_x;
	unsigned int m_y;
};

struct Rva003C9470ResultPair
{
	volatile float m_x;
	volatile float m_y;
};

struct Rva003C9470Output
{
	union
	{
		volatile float m_x;
		unsigned int m_rawX;
	};
	union
	{
		volatile float m_y;
		unsigned int m_rawY;
	};

	Rva003C9470Output &operator=(const Rva003C9470ResultPair &that)
	{
		m_x = that.m_x;
		m_y = that.m_y;
		return *this;
	}
};

class Rva003C6F60Object
{
public:
	char m_pad00[0x28];
	void *m_name;
	char m_pad2C[0x48];
	unsigned char m_hasPair;

};

struct Rva003C9470ContextResult;

struct Rva003C9470Context
{
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Rva003C9470ContextResult *lookup(const char *name, int mode);
};

struct Rva003C9470ContextResult
{
	virtual void releaseSlot();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
virtual Rva003C9470ResultPair *getPair();

	int m_refCount;
};

struct BfmeObj923G;
extern BfmeObj923G *__stdcall bfmeFind923G(void *owner);
extern void j_00034982();

class Rva003C9470Key
{
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);

private:
	char m_pad00[0x24];
	Rva003C9470Context *m_context;
};

bool Rva003C9470Owner::fallback(Rva003C9470Key *key,
	Rva003C9470Output *output)
{
	Rva003C6F60Object *object = (Rva003C6F60Object *)bfmeFind923G(key);
	if (object == 0)
		return false;

	if (object->m_hasPair)
	{
		Rva003C9470ObjectPair pairBuffer;
		union
		{
			void (*plain)();
			int *(Rva003C6F60Object::*member)(int *);
		} copy;
		copy.plain = j_00034982;
		int *pair = (object->*copy.member)((int *)&pairBuffer);
		output->m_rawX = pair[0];
		output->m_rawY = pair[1];
		return true;
	}

	const char *name = (const char *)object->m_name;
	if (name != 0)
		name += 8;
	else
		name = g_bfmeEmptyAscii;
	Rva003C9470ContextResult *result = m_context->lookup(name, 0);
	if (result == 0)
		return false;

	Rva003C9470ResultPair *pair = result->getPair();
	float x = pair->m_x;
	float y = pair->m_y;
	output->m_x = x;
	output->m_y = y;
	int refCount = result->m_refCount;
	--refCount;
	result->m_refCount = refCount;
	if (refCount == 0)
		result->releaseSlot();
	return true;
}
