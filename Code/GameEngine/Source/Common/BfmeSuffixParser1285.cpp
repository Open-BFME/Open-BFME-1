extern "C" int __cdecl isdigit(int value);
extern "C" int __cdecl atoi(const char *text);

struct BfmeStringData1285
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

struct BfmeString1285
{
	BfmeStringData1285 *m_data;
};

struct BfmeNode1285;

struct BfmeIterator1285
{
	BfmeStringData1285 *m_name;
	BfmeNode1285 *m_taggedNode;
};

class BfmeIteratorList1285
{
public:
	BfmeIterator1285 *bfmeFirst1285();
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *iterator);
};

struct BfmeNodeInfo1285
{
	char m_padding00[0x10];
	BfmeIteratorList1285 *m_list10;
};

struct BfmeNode1285
{
	void *m_vtable;
	unsigned int m_flags04;
	char m_padding08[4];
	BfmeString1285 m_name0c;
	char m_padding10[0x3c];
	BfmeNode1285 *m_next4c;
	BfmeNodeInfo1285 *m_info50;
};

class BfmeRouteManager1285
{
public:
	bool bfmeAllows1285(BfmeNode1285 *node);
};

extern BfmeStringData1285 g_bfmeEmptyString1285;
extern float g_bfmeDirectionWeight1285;
extern float g_bfmeInvalidScore1285;
extern BfmeRouteManager1285 *g_bfmeHolderBU;
extern float g_bfmeMinimumScore1285;

static __forceinline int bfmeAbs1285(int value)
{
	return value < 0 ? -value : value;
}

static __declspec(noinline) float bfmeDirectionalScore1285(
	int direction, int referenceFirst, int referenceSecond,
	int candidateFirst, int candidateSecond)
{
	int dy;
	int dx = candidateSecond - referenceSecond;
	dy = candidateFirst - referenceFirst;
	switch (direction) {
	case 14:
		if (dx >= 0)
			return g_bfmeInvalidScore1285;
		{
			int primary = bfmeAbs1285(dx);
			int perpendicular = bfmeAbs1285(dy);
			return (float)perpendicular * g_bfmeDirectionWeight1285 + primary;
		}
	case 15:
		if (dx <= 0)
			return g_bfmeInvalidScore1285;
		return (float)bfmeAbs1285(dy) * g_bfmeDirectionWeight1285 + dx;
	case 1:
		if (dy >= 0)
			return g_bfmeInvalidScore1285;
		{
			int primary = bfmeAbs1285(dy);
			int perpendicular = bfmeAbs1285(dx);
			return (float)perpendicular * g_bfmeDirectionWeight1285 + primary;
		}
	case 2:
		if (dy <= 0)
			return g_bfmeInvalidScore1285;
		return (float)bfmeAbs1285(dx) * g_bfmeDirectionWeight1285 + dy;
	}
	return g_bfmeInvalidScore1285;
}

static __declspec(noinline) bool bfmeParseSuffix1285(
	BfmeString1285 *value, int *first, int *second)
{
	BfmeStringData1285 *data = value->m_data;
	if (data == &g_bfmeEmptyString1285)
		return false;

	char *cursor = &data->m_text[data->m_length - 1];
	if (!isdigit(*cursor))
		return false;
	while (isdigit(*cursor)) {
		--cursor;
	}
	if (second != 0)
		*second = atoi(cursor + 1);
	if (*cursor-- != '_')
		return false;
	if (!isdigit(*cursor))
		return false;
	while (isdigit(*cursor)) {
		--cursor;
	}
	if (first != 0)
		*first = atoi(cursor + 1);
	return true;
}

BfmeNode1285 *bfmeFindDirectional1285(
	int direction, BfmeNode1285 *current, BfmeNode1285 *reference)
{
	while (current != 0) {
		float bestScore = 1000000000.0f;
		int referenceFirst = 0;
		int referenceSecond = 0;
		BfmeNode1285 *bestNode = 0;
		if (reference != 0) {
			bfmeParseSuffix1285(&reference->m_name0c, &referenceFirst, &referenceSecond);
		}

		for (BfmeIterator1285 *iterator = current->m_info50->m_list10->bfmeFirst1285();
			 iterator != 0;
			 iterator = current->m_info50->m_list10->bfmeNext1285(iterator)) {
			BfmeNode1285 *candidate = reinterpret_cast<BfmeNode1285 *>(
				reinterpret_cast<unsigned int>(iterator->m_taggedNode) & ~1U);
			unsigned int flags = candidate->m_flags04;
			int kind = flags & 0x3f;
			if (kind < 12 || kind > 19 ||
				(static_cast<unsigned char>(~(flags >> 15)) & 1) != 0 ||
				reference == candidate || (kind != 13 && kind != 18 && kind != 14)) {
				continue;
			}

			int candidateSecond;
			int candidateFirst;
			if (!bfmeParseSuffix1285(reinterpret_cast<BfmeString1285 *>(iterator),
				&candidateFirst, &candidateSecond)) {
				continue;
			}
			if (g_bfmeHolderBU->bfmeAllows1285(candidate))
				continue;
			if (reference == 0) {
				bestNode = candidate;
				break;
			}

			float score = bfmeDirectionalScore1285(direction, referenceFirst,
				referenceSecond, candidateFirst, candidateSecond);
			if (score >= g_bfmeMinimumScore1285 && score < bestScore) {
				bestScore = score;
				bestNode = candidate;
			}
		}

		if (bestNode != 0) {
			unsigned int flags = bestNode->m_flags04;
			if ((flags & 0x3f) != 13 ||
				(static_cast<unsigned char>(~(flags >> 15)) & 1) != 0)
				return bestNode;
			reference = 0;
			current = bestNode;
		} else {
			reference = current;
			current = current->m_next4c;
		}
	}

	return 0;
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
