// ?d_009ab9d0@@YAEPAXPAFHPAE2@Z
// partial score=0.0 date=2026-09-22
// Address-derived VP6 coefficient decoder. The retail entry has no proven
// semantic name; offsets and tables below come from its decoded instructions.
struct Rva009AB9D0BoolState {
	unsigned char pad[4];
	unsigned range;
	unsigned code;
	int bitsRemaining;
	unsigned inputCursor;
	const unsigned char *inputBase;
	int step();
};

extern int __cdecl Rva009B4800DecodeBool(Rva009AB9D0BoolState *, int);

static __forceinline int Rva009AB9D0StepInline(Rva009AB9D0BoolState *bits)
{
	unsigned range = bits->range;
	unsigned code = bits->code;
	int count = bits->bitsRemaining;
	const unsigned half = (range + 1) >> 1;
	const unsigned threshold = half << 24;
	int bit = code >= threshold;
	if (bit) {
		range -= half;
		code -= threshold;
	} else {
		range = half;
	}
	range += range;
	code += code;
	if (--count == 0) {
		code |= bits->inputBase[bits->inputCursor++];
		count = 8;
	}
	bits->range = range;
	bits->code = code;
	bits->bitsRemaining = count;
	return bit;
}

static __forceinline unsigned Rva009AB9D0ReadLiteral(Rva009AB9D0BoolState *bits, int token)
{
	const unsigned char *table = (const unsigned char *)(0x01142720 + token * 16);
	unsigned value = *(const unsigned short *)table;
	int shift = *(const short *)(table + 2);
	do {
		value += Rva009B4800DecodeBool(bits, table[4 + shift]) << shift;
		--shift;
	} while (shift >= 0);
	return value;
}

static __forceinline int Rva009AB9D0Token(Rva009AB9D0BoolState *bits, const unsigned char *p)
{
	if (!Rva009B4800DecodeBool(bits, p[3])) {
		if (!Rva009B4800DecodeBool(bits, p[4]))
			return 2;
		return 3 + Rva009B4800DecodeBool(bits, p[5]);
	}
	int token;
	if (!Rva009B4800DecodeBool(bits, p[6]))
		token = 5 + Rva009B4800DecodeBool(bits, p[7]);
	else if (!Rva009B4800DecodeBool(bits, p[8]))
		token = 7 + Rva009B4800DecodeBool(bits, p[9]);
	else
		token = 9 + Rva009B4800DecodeBool(bits, p[10]);
	return Rva009AB9D0ReadLiteral(bits, token);
}

static __forceinline int Rva009AB9D0Run(Rva009AB9D0BoolState *bits, const unsigned char *p)
{
	if (!Rva009B4800DecodeBool(bits, p[0])) {
		if (!Rva009B4800DecodeBool(bits, p[1]))
			return 1 + Rva009B4800DecodeBool(bits, p[2]);
		return 3 + Rva009B4800DecodeBool(bits, p[3]);
	}
	if (!Rva009B4800DecodeBool(bits, p[4])) {
		if (!Rva009B4800DecodeBool(bits, p[5]))
			return 5 + Rva009B4800DecodeBool(bits, p[6]);
		return 7 + Rva009B4800DecodeBool(bits, p[7]);
	}
	int run = 9;
	for (int i = 0; i < 6; ++i)
		run += Rva009B4800DecodeBool(bits, p[8 + i]) << i;
	return run;
}

unsigned char __cdecl d_009ab9d0(void *raw, short *coefficients, int plane,
	unsigned char *left, unsigned char *above)
{
	unsigned char *context = (unsigned char *)raw;
	Rva009AB9D0BoolState *bits = (Rva009AB9D0BoolState *)(context +
		(*(int *)(context + 0x944) || !context[0x19D] ? 0x170 : 0x150));
	const int *mapping = *(const int **)(*(int *)(context + 0x13C) + 0x13C);
	const unsigned char *dc = context + 0x542 + 5 * (plane * 3 + *left + *above);
	const unsigned char *large = context + 0x3A0 + 11 * plane;
	unsigned char prior;

	if (!Rva009B4800DecodeBool(bits, dc[0])) {
		prior = 0;
		*left = *above = 0;
	} else {
		*left = *above = 1;
		if (!Rva009B4800DecodeBool(bits, dc[2])) {
			prior = 1;
			coefficients[0] = bits->step() ? -1 : 1;
		} else {
			prior = 2;
			unsigned value = Rva009AB9D0Token(bits, large);
			coefficients[0] = bits->step() ? -(short)value : (short)value;
		}
	}

	unsigned index = 1;
	while (index < 64) {
		const int category = ((const int *)0x011427E0)[index];
		const unsigned char *prob = context + 0x3B6 + plane * 0xC6 +
			(category + prior * 6) * 11;
		if ((index < 2 || prior) && !Rva009B4800DecodeBool(bits, prob[0])) {
			if (!Rva009B4800DecodeBool(bits, prob[1])) {
				++index;
				break;
			}
			const unsigned char *run = context + 0x560 + (index > 5 ? 14 : 0);
			index += Rva009AB9D0Run(bits, run);
			prior = 0;
		} else {
			unsigned value;
			if (!Rva009B4800DecodeBool(bits, prob[2])) {
				prior = 1;
				value = 1;
			} else {
				prior = 2;
				value = Rva009AB9D0Token(bits, prob);
			}
			coefficients[mapping[context[0x5BC + index]]] =
				Rva009AB9D0StepInline(bits) ? -(short)value : (short)value;
			++index;
		}
	}
	return context[0x5FC + (unsigned char)(index - 1)];
}
