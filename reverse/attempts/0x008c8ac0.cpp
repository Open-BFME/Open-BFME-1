// ?_FunctionAptActionEquals2@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// partial score=0.24 date=2026-09-02
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

extern AptStringBlock g_aptEmptyString;
extern AptStringPool *g_aptStringPool;

class EAStringC
{
public:
	EAStringC()
	{
		m_block = &g_aptEmptyString;
		++m_block->m_refs;
	}

	~EAStringC()
	{
		if (--m_block->m_refs == 0)
			g_aptStringPool->m_free(m_block);
	}

	int Find(char c, int start);

	bool equals(const EAStringC &other) const
	{
		unsigned length = m_block->m_length;
		if (length != other.m_block->m_length)
			return false;
		if (m_block == other.m_block)
			return true;
		const char *left = m_block->m_text;
		const char *right = other.m_block->m_text;
		while (length-- != 0) {
			if (*left++ != *right++)
				return false;
		}
		return true;
	}

	AptStringBlock *m_block;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	int toInteger() const;
	float toFloat() const;
	void getName(EAStringC *out) const;

	unsigned type() const { return m_bits & 0x3f; }
	bool isUndefined() const { return ((m_bits >> 15) & 1) == 0; }
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
extern AptValue *g_aptBooleanFreeList;
extern AptValueRegistry *g_aptValueRegistry;
extern void *(__cdecl *g_aptAllocate)(unsigned size);
extern void *g_AptValueVtable[];
extern void *g_AptBooleanVtable[];

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

static __forceinline bool IsPrimitive(AptValue *value)
{
	unsigned type = value->type();
	return !value->isUndefined()
		&& (type == 7 || type == 6 || type == 5 || type == 1 || type == 42);
}

static __forceinline bool IsString(AptValue *value)
{
	unsigned type = value->type();
	return !value->isUndefined() && (type == 1 || type == 42);
}

static __forceinline bool IsNumber(AptValue *value)
{
	unsigned type = value->type();
	return !value->isUndefined() && (type == 7 || type == 6);
}

static __forceinline bool IsNaNValue(AptValue *value)
{
	unsigned type = value->type();
	bool defined = !value->isUndefined();

	if ((type == 7 || type == 6) && defined)
		return false;

	if ((type == 1 || type == 42) && defined) {
		AptStringBlock *string = value->stringValue()->m_block;
		const char *text = string->m_text;
		int length = string->m_length;

		if (length == 0)
			return true;

		if (length > 2 && text[0] == '0' && text[1] == 'x') {
			char *end = 0;
			strtol(text, &end, 16);
			return *end != 0;
		}

		unsigned char last = (unsigned char)text[length - 1];
		if (last != '-' && last != '+' && last != 'e' && last != '.' && !isdigit(last))
			return true;
		unsigned char first = (unsigned char)text[0];
		if (first != '.' && first != '-' && first != '+' && !isdigit(first))
			return true;

		bool dotSeen = false;
		for (int i = 1; i < length; ++i) {
			char c = text[i];
			if (c == '.' && !dotSeen) {
				dotSeen = true;
				continue;
			}
			if (c == 'e' && i != 1) {
				if (i == 2 && (text[0] == '+' || text[0] == '-'))
					return true;
				int next = i + 1;
				if (next < length) {
					char c2 = text[next];
					if (c2 == '-' || c2 == '+') {
						++i;
						continue;
					}
					if (!isdigit((unsigned char)c2))
						return true;
				}
				continue;
			}
			if (!isdigit((unsigned char)c))
				return true;
		}
		return false;
	}

	if (defined && type != 5)
		return true;
	return AptGetSwfVersion() == 7;
}

static __forceinline AptValue *CreateBoolean(bool value)
{
	AptValue *result = g_aptBooleanFreeList;
	if (result != 0) {
		g_aptBooleanFreeList = *(AptValue **)((char *)result + 8);
	} else {
		result = (AptValue *)g_aptAllocate(12);
		if (result == 0)
			return 0;
		*(void **)result = g_AptValueVtable;
		result->m_bits = (result->m_bits & 0xf0008005) | 0x40008005;
	}

	AptValueRegistry *registry = g_aptValueRegistry;
	if (registry->m_count < registry->m_capacity) {
		registry->m_values[registry->m_count++] = result;
		*(void **)result = g_AptBooleanVtable;
	} else {
		result->m_bits &= 0xbfffffff;
	}
	result->m_value.m_boolean = value;
	return result;
}

static __forceinline void CollapseTwo(AptActionInterpreter *interpreter, AptValue *result)
{
	for (int index = 1; index <= 2; ++index) {
		AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];
		if (!value->maxRefCountHit())
			value->Release();
	}
	interpreter->m_stackTop -= 2;
	interpreter->m_stack[interpreter->m_stackTop++] = result;
	if (!result->maxRefCountHit())
		result->AddRef();
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
		int undefinedCount = 0;
		if (top->isUndefined())
			undefinedCount = 1;
		if (under->isUndefined())
			++undefinedCount;
		if (undefinedCount > 0) {
			CollapseTwo(interpreter, CreateBoolean(undefinedCount == 2));
			return;
		}
	}

	unsigned topType = top->type();
	unsigned underType = under->type();

	if (IsPrimitive(top) && IsPrimitive(under)) {
		if (top->isUndefined()) {
			equal = 1;
		} else if (topType == 7 && IsDefinedType(under, 7)) {
			equal = under->toInteger() == top->toInteger();
		} else if (topType == 6 && IsDefinedType(under, 6)) {
			equal = top->toFloat() == under->toFloat();
		} else if ((topType == 1 || topType == 42) && IsString(under)) {
			equal = top->stringValue()->equals(*under->stringValue());
		} else {
			goto mixedCompare;
		}
		CollapseTwo(interpreter, CreateBoolean(equal != 0));
		return;
	}

	if (topType != underType) {
		if (top->isUndefined() && under->isUndefined())
			equal = 1;
		CollapseTwo(interpreter, CreateBoolean(equal != 0));
		return;
	}

mixedCompare:
	{
		bool stringLadder = false;
		if (!IsNumber(top) || IsNaNValue(under)) {
			if (!IsNumber(under) || IsNaNValue(top))
				stringLadder = true;
		}

		if (stringLadder) {
			bool topString = IsString(top);
			bool underBoolean = IsDefinedType(under, 5);
			bool underString = IsString(under);

			if (topString && !underBoolean) {
				EAStringC topScratch;
				EAStringC underScratch;
				top->getName(&topScratch);
				under->getName(&underScratch);
				equal = topScratch.equals(underScratch);
				CollapseTwo(interpreter, CreateBoolean(equal != 0));
				return;
			}

			bool identityCompare = false;
			if (!topString || underString) {
				if (!underBoolean || topString)
					identityCompare = true;
			}
			if (identityCompare)
				equal = under == top;
			else
				equal = under->toInteger() == top->toInteger();

			CollapseTwo(interpreter, CreateBoolean(equal != 0));
			return;
		}

		bool topHasDot = false;
		bool underHasDot = false;
		if (IsString(top) || IsDefinedType(top, 6)) {
			if (!IsDefinedType(top, 6) && top->stringValue()->Find('.', 0) != -1)
				topHasDot = true;
		}
		if (IsString(under) || IsDefinedType(under, 6)) {
			if (!IsDefinedType(under, 6) && under->stringValue()->Find('.', 0) != -1)
				underHasDot = true;
		}

		float topFloat;
		float underFloat;
		if (IsDefinedType(top, 7)) {
			int topInt = top->toInteger();
			if (!underHasDot) {
				equal = under->toInteger() == topInt;
				CollapseTwo(interpreter, CreateBoolean(equal != 0));
				return;
			}
			topFloat = (float)topInt;
			underFloat = under->toFloat();
		} else if (IsDefinedType(under, 7)) {
			int underInt = under->toInteger();
			if (!topHasDot) {
				equal = underInt == top->toInteger();
				CollapseTwo(interpreter, CreateBoolean(equal != 0));
				return;
			}
			topFloat = top->toFloat();
			underFloat = (float)underInt;
		} else {
			topFloat = top->toFloat();
			underFloat = under->toFloat();
		}

		float difference = topFloat - underFloat;
		if (difference < 0.0f)
			difference = -difference;
		equal = difference < 0.001f;
	}

	CollapseTwo(interpreter, CreateBoolean(equal != 0));
}
