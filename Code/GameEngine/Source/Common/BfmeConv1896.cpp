// cl: /O2 /Ob1 /EHs-c-
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <cstring>
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *dst, const void *src, unsigned int count);
#define memmove (*bfme_memmove_ptr)
#include <algorithm>
#include <vector>
#undef memmove

extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

class BfmeNodeAK
{
public:
	BfmeNodeAK(void *key);

	_STL::vector<void *> m_bfmeValuesAK;
	void *m_bfmeKeyAK;
	BfmeNodeAK *m_bfmeNextAK;
};

struct BfmeVectorRawAK
{
	void **m_bfmeBeginAK;
	void **m_bfmeEndAK;
	void **m_bfmeCapAK;
};

class BfmeNodeAKInline
{
public:
	__forceinline BfmeNodeAKInline(void *key)
		: m_bfmeValuesAK()
	{
		m_bfmeKeyAK = key;
		m_bfmeValuesAK.clear();
		m_bfmeNextAK = 0;
	}

	_STL::vector<void *> m_bfmeValuesAK;
	void *m_bfmeKeyAK;
	BfmeNodeAKInline *m_bfmeNextAK;
};

class BfmeListAK
{
public:
	void bfmeAddAK(void *key, void *value);
	int bfmeDropAK(void *key, void *value);

	BfmeNodeAK *m_bfmeHeadAK;
	BfmeNodeAK *m_bfmeRootAK;
};

void BfmeListAK::bfmeAddAK(void *key, void *value)
{
	BfmeNodeAK **root = &m_bfmeRootAK;
	BfmeNodeAK *n = *root;

	m_bfmeHeadAK = n;
	while (n != 0)
	{
		if (n->m_bfmeKeyAK == key)
			break;
		n = n->m_bfmeNextAK;
	}
	if (n != 0)
	{
		for (unsigned int i = 0; i < n->m_bfmeValuesAK.size(); ++i)
		{
			if (n->m_bfmeValuesAK.begin()[i] == value)
				return;
		}
		n->m_bfmeValuesAK.push_back(value);
		return;
	}
	n = (BfmeNodeAK *)new BfmeNodeAKInline(key);
	n->m_bfmeValuesAK.push_back(value);
	if (*root != 0)
		n->m_bfmeNextAK = *root;
	*root = n;
}

BfmeNodeAK::BfmeNodeAK(void *key)
	: m_bfmeValuesAK()
{
	m_bfmeKeyAK = key;
	m_bfmeValuesAK.clear();
	m_bfmeNextAK = 0;
}

int BfmeListAK::bfmeDropAK(void *key, void *value)
{
	BfmeNodeAK *n = m_bfmeRootAK;

	m_bfmeHeadAK = n;

	while (n != 0)
	{
		if (n->m_bfmeKeyAK == key)
		{
			for (void **p = n->m_bfmeValuesAK.begin(); p != n->m_bfmeValuesAK.end(); p++)
			{
				if (*p == value)
				{
					void **next = p + 1;

					if (n->m_bfmeValuesAK.end() != next)
						BfmeMemMove(p, next, (char *)n->m_bfmeValuesAK.end() - (char *)next);

					((BfmeVectorRawAK *)&n->m_bfmeValuesAK)->m_bfmeEndAK--;
					return 1;
				}
			}
		}

		n = n->m_bfmeNextAK;
	}

	return 0;
}
