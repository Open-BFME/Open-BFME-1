// ?d_00064bf0@@YAXXZ
// partial score=0.876 date=2026-09-28
// cl: /DNDEBUG /MD /EHs-c-
// Rva003BBE50TreeStep.cpp calls ILT 0x00026887 with the tree pointer,
// an unsigned key, and a 28-byte output.

struct BfmeNodeZA
{
	unsigned char m_bfmeHead[4];
	BfmeNodeZA *m_bfmeRoot;
	BfmeNodeZA *m_bfmeLeft;
	BfmeNodeZA *m_bfmeRight;
	unsigned char m_bfmeBody[0x18];
	unsigned int m_bfmeKey;
};

struct BfmeIterZA
{
	BfmeNodeZA *m_bfmeNode;
};

struct BfmeWantZA
{
	unsigned char m_bfmeHead[0x18];
	unsigned int m_bfmeKey;
};

class BfmeTreeZA
{
public:
	BfmeIterZA bfmeLowerZA(const BfmeWantZA *want) const;

private:
	BfmeNodeZA *m_bfmeHead;
};

struct Rva00064BF0Value
{
	unsigned char m_value00[0x18];
	unsigned int m_value18;
};

class Rva00064BF0Tree
{
public:
	bool rva00064BF0(unsigned int key, Rva00064BF0Value *out);

private:
	BfmeTreeZA m_bfmeTree;
	unsigned int m_rva00064BF0_04;
};

class Rva000643C0Value
{
public:
	Rva000643C0Value(void *owner);
	float m_real00;
	float m_real04;
	float m_real08;
	float m_real0C;
	float m_real10;
	float m_real14;
	void *m_owner18;
};

struct Rva000643F0Triple
{
	int m_value00;
	int m_value04;
	int m_value08;
};

struct Rva00064410Point
{
	float x;
	float y;
	float z;
};

class Rva000643F0Value
{
public:
	Rva000643F0Triple *copyTo(Rva000643F0Triple *destination) const;
	int m_value00;
	int m_value04;
	int m_value08;
};

class Rva00063F90Blend
{
public:
	float eval(void) const;

private:
	unsigned char m_pad[0x10];
	float m_t;
};

class Rva00063FD0Blend
{
public:
	float eval(void) const;

private:
	unsigned char m_pad[0x14];
	float m_s;
};

float bfmeBezier(float a, float b, float c, float d, float t);
float bfmeSpline1266(float p0, float p1, float p2, float p3, float t);
extern const float g_bfmeUint32Scale;
extern void j_00039f54();
typedef Rva00064410Point *(*Rva00064BF0Calc)(Rva00064410Point *,
	const Rva00064410Point *, const Rva00064410Point *,
	const Rva00064410Point *, const Rva00064410Point *, float);

namespace _STL
{
struct _Rb_tree_node_base;
}

extern "C" _STL::_Rb_tree_node_base *__cdecl
bfme_RbGlobalBoolDecrement_82B8E0(_STL::_Rb_tree_node_base *node);

extern void j_0001a465();
extern void j_0001f25d();

bool Rva00064BF0Tree::rva00064BF0(unsigned int key, Rva00064BF0Value *out)
{
	if (*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 4) == 0)
		return false;

	BfmeNodeZA *first = (*reinterpret_cast<BfmeNodeZA **>(this))->m_bfmeLeft;
	if (key <= first->m_bfmeKey)
	{
		*out = *reinterpret_cast<const Rva00064BF0Value *>(first->m_bfmeBody);
		return false;
	}
	BfmeNodeZA *last = reinterpret_cast<BfmeNodeZA *>(
		bfme_RbGlobalBoolDecrement_82B8E0(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(
				*reinterpret_cast<BfmeNodeZA **>(this))));
	if (key > last->m_bfmeKey)
	{
		*out = *reinterpret_cast<const Rva00064BF0Value *>(last->m_bfmeBody);
		return false;
	}
	Rva000643C0Value query(reinterpret_cast<void *>(key));
	BfmeIterZA found = m_bfmeTree.bfmeLowerZA(
		reinterpret_cast<const BfmeWantZA *>(&query));
	if (found.m_bfmeNode == first)
	{
		*out = *reinterpret_cast<const Rva00064BF0Value *>(first->m_bfmeBody);
		return false;
	}
	if (found.m_bfmeNode == *reinterpret_cast<BfmeNodeZA **>(this))
	{
		*out = *reinterpret_cast<const Rva00064BF0Value *>(last->m_bfmeBody);
		return false;
	}

	BfmeIterZA previous;
	previous.m_bfmeNode = reinterpret_cast<BfmeNodeZA *>(
		bfme_RbGlobalBoolDecrement_82B8E0(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(found.m_bfmeNode)));
	BfmeIterZA beforePrevious = previous;
	if (previous.m_bfmeNode != first)
	{
		typedef void (BfmeIterZA::*Rva00064BF0IterStep)(void);
		union
		{
			void (*raw)(void);
			Rva00064BF0IterStep member;
		} step;
		step.raw = j_0001a465;
		(beforePrevious.*step.member)();
	}

	BfmeIterZA afterFound = found;
	if (found.m_bfmeNode != last)
	{
		typedef void (BfmeIterZA::*Rva00064BF0IterStep)(void);
		union
		{
			void (*raw)(void);
			Rva00064BF0IterStep member;
		} step;
		step.raw = j_0001f25d;
		(afterFound.*step.member)();
	}

	int numerator;
	numerator = static_cast<int>(key - previous.m_bfmeNode->m_bfmeKey);
	float t = static_cast<float>(numerator);
	if (numerator < 0)
		t += g_bfmeUint32Scale;
	int denominator;
	denominator = static_cast<int>(found.m_bfmeNode->m_bfmeKey
		- previous.m_bfmeNode->m_bfmeKey);
	float width = static_cast<float>(denominator);
	if (denominator < 0)
		width += g_bfmeUint32Scale;
	float ratio = t / width;

	float blend = bfmeBezier(
		0.0f,
		reinterpret_cast<const Rva00063FD0Blend *>(previous.m_bfmeNode->m_bfmeBody)->eval(),
		reinterpret_cast<const Rva00063F90Blend *>(found.m_bfmeNode->m_bfmeBody)->eval(),
		1.0f,
		ratio);

	Rva00064410Point p3;
	Rva00064410Point p2;
	Rva00064410Point p1;
	Rva00064410Point p0;
	Rva00064410Point result;
	union
	{
		void (*raw)(void);
		Rva00064BF0Calc typed;
	} evaluate;
	evaluate.raw = j_00039f54;
	// The matched calc body leaves the result pointer in EAX.
	Rva00064410Point *calculated = evaluate.typed(
		&result,
		reinterpret_cast<const Rva00064410Point *>(
			reinterpret_cast<const Rva000643F0Value *>(
				beforePrevious.m_bfmeNode->m_bfmeBody)->copyTo(
					reinterpret_cast<Rva000643F0Triple *>(&p0))),
		reinterpret_cast<const Rva00064410Point *>(
			reinterpret_cast<const Rva000643F0Value *>(
				previous.m_bfmeNode->m_bfmeBody)->copyTo(
					reinterpret_cast<Rva000643F0Triple *>(&p1))),
		reinterpret_cast<const Rva00064410Point *>(
			reinterpret_cast<const Rva000643F0Value *>(
				found.m_bfmeNode->m_bfmeBody)->copyTo(
					reinterpret_cast<Rva000643F0Triple *>(&p2))),
		reinterpret_cast<const Rva00064410Point *>(
			reinterpret_cast<const Rva000643F0Value *>(
				afterFound.m_bfmeNode->m_bfmeBody)->copyTo(
					reinterpret_cast<Rva000643F0Triple *>(&p3))),
		blend);

	float *destination = reinterpret_cast<float *>(out);
	float *point = reinterpret_cast<float *>(calculated);
	destination[0] = point[0];
	destination[1] = point[1];
	destination[2] = point[2];
	destination[3] = bfmeSpline1266(
		*reinterpret_cast<const float *>(beforePrevious.m_bfmeNode->m_bfmeBody + 0x0c),
		*reinterpret_cast<const float *>(previous.m_bfmeNode->m_bfmeBody + 0x0c),
		*reinterpret_cast<const float *>(found.m_bfmeNode->m_bfmeBody + 0x0c),
		*reinterpret_cast<const float *>(afterFound.m_bfmeNode->m_bfmeBody + 0x0c),
		blend);
	out->m_value18 = key;
	return true;
}
