// ?_FunctionAptActionEquals2@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// partial score=0.1682 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" int __cdecl memcmp(const void *, const void *, unsigned);
#pragma intrinsic(memcmp)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
extern "C" int __cdecl isdigit(int c);
extern "C" long __cdecl strtol(const char *text, char **end, int base);

struct AptStringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

struct AptStringPool
{
	void *m_unused;
	void (__cdecl *m_free)(AptStringBlock *block);
};

extern "C" AptStringBlock __identifier("?g_bfmeDefaultString1284@@3UAptStringBlock@@A");
#define g_aptEmptyString __identifier("?g_bfmeDefaultString1284@@3UAptStringBlock@@A")
extern "C" AptStringPool *__identifier("?g_pool01337A30@@3PAUAptStringPool@@A");
#define g_aptStringPool __identifier("?g_pool01337A30@@3PAUAptStringPool@@A")

class EAStringC
{
public:
	EAStringC()
	{
		m_block = &g_aptEmptyString;
		++m_block->m_refs;
	}

	__forceinline ~EAStringC()
	{
		if (--m_block->m_refs == 0)
			g_aptStringPool->m_free(m_block);
	}

	int Find(char c, int start);

	int length() const { return m_block->m_length; }
	char *text() const { return m_block->m_text; }
	__forceinline bool equals(const EAStringC &other) const
	{
		unsigned length = m_block->m_length;
		if (length != other.m_block->m_length) return false;
		if (m_block == other.m_block) return true;
		return memcmp(m_block->m_text, other.m_block->m_text, length) == 0;
	}

	AptStringBlock *m_block;
};

class Rva8CD130String;
class Rva8CD130Value { public: void getName(Rva8CD130String *); };

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	int toInteger() const;
	float toNumber();
	float toFloat() const { return const_cast<AptValue *>(this)->toNumber(); }
	void getName(EAStringC *out) const { ((Rva8CD130Value *)this)->getName((Rva8CD130String *)out); }

	unsigned type() const { return m_bits & 0x3f; }
	bool isUndefined() const { return ((unsigned char)~(m_bits >> 15) & 1) != 0; }
	bool maxRefCountHit() const { return ((m_bits >> 30) & 1) != 0; }

	EAStringC *stringValue()
	{
		AptValue *value = this;
		if (type() != 1)
			value = m_indirect;
		return (EAStringC *)&value->m_value;
	}

	unsigned m_bits;
	union {
		unsigned char m_boolean;
		int m_integer;
		float m_float;
		AptStringBlock *m_string;
	} m_value;
	char m_pad0c[0x14];
	AptValue *m_indirect;
};

struct AptValueRegistry
{
	int m_capacity;
	int m_count;
	AptValue **m_values;
};

extern AptValue *gpUndefinedValue;
extern "C" AptValue *__identifier("?g_rva008D2A80@@3PAVRva008D2A80@@A");
#define g_aptBooleanFreeList __identifier("?g_rva008D2A80@@3PAVRva008D2A80@@A")
extern "C" AptValueRegistry *__identifier("?g_bfmeRegistryVNF@@3PAUAptValueRegistry@@A");
#define g_aptValueRegistry __identifier("?g_bfmeRegistryVNF@@3PAUAptValueRegistry@@A")
extern void *(__cdecl *g_aptAllocate)(unsigned size);
#define g_AptValueVtable __identifier("??_7Rva00899560Value@@6B@")
#define g_AptBooleanVtable __identifier("??_7Rva008995E0Value@@6B@")

unsigned int AptGetSwfVersion();

class AptActionInterpreter
{
public:
	struct LocalContextT;
	static void _FunctionAptActionEquals2(AptActionInterpreter *interpreter,
		LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

static __forceinline bool IsDefinedType(AptValue *value, unsigned type)
{
	return value->type() == type && !value->isUndefined();
}

static __forceinline bool IsString(AptValue *value)
{
	unsigned type = value->type();
	return (type == 1 || type == 42) && !value->isUndefined();
}
static __forceinline bool IsPrimitive(AptValue *value)
{
	return IsDefinedType(value, 7) || IsDefinedType(value, 6)
		|| IsDefinedType(value, 5) || IsString(value);
}
static __forceinline bool IsNumber(AptValue *value)
{
	return IsDefinedType(value, 7) || IsDefinedType(value, 6);
}

static __forceinline bool IsNaNValue(AptValue *value)
{
	if (IsDefinedType(value, 7) || IsDefinedType(value, 6))
		return false;

	if (IsString(value))
	{
		EAStringC string;
		value->getName(&string);

		if (string.length() == 0)
			return true;

		if (string.text()[0] == '0' && string.length() > 2 && string.text()[1] == 'x')
		{
			char *end;
			strtol(string.text(), &end, 16);
			if (*end == 0)
				return false;
		}

		bool sawDot = false;
		char last = string.text()[string.length() - 1];
		if (last != '-' && last != '+' && last != 'e' && last != '.' && !isdigit(last))
			return true;

		char first = string.text()[0];
		if (first != '.' && first != '-' && first != '+' && !isdigit(first))
			return true;

		for (int index = 1; index < string.length(); ++index)
		{
			char current = string.text()[index];
			if (current == '.' && !sawDot)
			{
				sawDot = true;
				continue;
			}
			if (current == 'e' && index != 1)
			{
				if (index == 2 && (string.text()[0] == '+' || string.text()[0] == '-'))
					return true;
				int next = index + 1;
				if (next < string.length())
				{
					char following = string.text()[index + 1];
					if (following != '-' && following != '+' && !isdigit(following))
						return true;
					index = next;
				}
				continue;
			}
			if (!isdigit(current))
				return true;
		}
		return false;
	}

	if (!value->isUndefined() && value->type() != 3)
		return true;
	bool swf7 = AptGetSwfVersion() == 7;
	return swf7;
}

static __forceinline void RegisterBoolean(AptValue *result)
{
	int &count = g_aptValueRegistry->m_count;
	if (count >= g_aptValueRegistry->m_capacity)
		result->m_bits &= 0xbfffffff;
	else {
		g_aptValueRegistry->m_values[count] = result;
		++count;
	}
}
class Rva00899560Value
{
public:
	virtual void retain();
	virtual void release();
	unsigned m_flags;
	__forceinline Rva00899560Value(int type)
	{
		unsigned flags = (((m_flags & ~0x3f) | type) & 0xf000803f) | 0x8000;
		m_flags = flags;
		if (type != 0x1c && type != 0xa) {
			m_flags = flags | 0x40000000;
			RegisterBoolean((AptValue *)this);
		} else m_flags = flags & 0xbfffffff;
	}
};
class Rva008995E0Value : public Rva00899560Value
{
public:
	static void *operator new(unsigned size) { return g_aptAllocate(size); }
	__forceinline Rva008995E0Value(bool value) : Rva00899560Value(5), m_value(value) {}
	bool m_value;
};
static __forceinline AptValue *CreateBoolean(bool value)
{
	AptValue *result = (AptValue *)g_aptBooleanFreeList;
	if (result != 0) {
		g_aptBooleanFreeList = (AptValue *)result->m_value.m_string;
		RegisterBoolean(result);
		result->m_value.m_boolean = value;
		return result;
	}
	return (AptValue *)new Rva008995E0Value(value);
}
static __forceinline void PopTwo(AptActionInterpreter *interpreter)
{
	for (int index = 1; index <= 2; ++index) {
		AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];
		if (!value->maxRefCountHit()) value->Release();
	}
	interpreter->m_stackTop -= 2;
}
static __forceinline void PushBoolean(AptActionInterpreter *interpreter, bool equal)
{
	AptValue *result = CreateBoolean(equal);
	interpreter->m_stack[interpreter->m_stackTop++] = result;
	if (!result->maxRefCountHit()) result->AddRef();
}

void AptActionInterpreter::_FunctionAptActionEquals2(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	int equal = 0;
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];

	if (top->type() == 19)
		top = gpUndefinedValue;
	if (under->type() == 19)
		under = gpUndefinedValue;

	if (AptGetSwfVersion() == 7) {
		if (top->isUndefined())
			equal = 1;
		if (under->isUndefined())
			++equal;
		if (equal > 0) {
			PopTwo(interpreter);
			PushBoolean(interpreter, equal == 2);
			return;
		}
	}

	if ((IsPrimitive(top) && IsPrimitive(under)) || top->type() == under->type()) {
		if (top->isUndefined()) {
			equal = 1;
		} else if (top->type() == 7 && IsDefinedType(under, 7)) {
			equal = under->toInteger() == top->toInteger();
		} else if (top->type() == 6 && IsDefinedType(under, 6)) {
			equal = top->toNumber() == under->toNumber();
		} else if ((top->type() == 1 || top->type() == 42) && IsString(under)) {
			equal = top->stringValue()->equals(*under->stringValue());
		} else {
			goto mixedCompare;
		}
		goto finish;
	}

	if (top->isUndefined() && under->isUndefined()) equal = 1;
	goto finish;

mixedCompare:
	{
		bool stringLadder = false;
		if (!IsNumber(top) || IsNaNValue(under)) {
			if (!IsNumber(under) || IsNaNValue(top))
				stringLadder = true;
		}

		if (stringLadder) {
			if (IsString(top) && !IsDefinedType(under, 5)) {
				EAStringC topScratch;
				EAStringC underScratch;
				top->getName(&topScratch);
				under->getName(&underScratch);
				equal = topScratch.equals(underScratch);
			} else if (IsDefinedType(top, 5) && !IsString(under)) {
				equal = under->toInteger() == top->toInteger();
			} else {
				equal = under == top;
			}

			goto finish;
		}

		bool topHasDot = false;
		bool underHasDot = false;
		if (IsString(top) || IsDefinedType(top, 6)) {
			if (top->type() == 6 || top->stringValue()->Find('.', 0) != -1)
				topHasDot = true;
		}
		if (IsString(under) || IsDefinedType(under, 6)) {
			if (under->type() == 6 || under->stringValue()->Find('.', 0) != -1)
				underHasDot = true;
		}

		float difference;
		if (IsDefinedType(top, 7)) {
			int topInt = top->toInteger();
			if (!underHasDot) {
				equal = under->toInteger() == topInt;
				goto finish;
			}
			difference = (float)topInt - under->toNumber();
		} else if (IsDefinedType(under, 7)) {
			int underInt = under->toInteger();
			if (!topHasDot) {
				equal = underInt == top->toInteger();
				goto finish;
			}
			difference = top->toNumber() - underInt;
		} else {
			float topFloat = top->toNumber();
			difference = topFloat - under->toNumber();
		}

		equal = (float)fabs(difference) < 0.001f;
	}

	finish:
	PopTwo(interpreter);
	PushBoolean(interpreter, equal != 0);
}
