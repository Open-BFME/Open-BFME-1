// Rva009F5970StateCtor.cpp calls 0x009F59D0 with one unsigned argument, and retail ends with ret 4.
// The caller does not prove the owning class, so this source keeps the retail address in its class name.
// Retail calls the matched Vector_base<Gen_t_009f51f0_p8cd> constructor and vector<ICoord2D> assignment.
// Both element layouts contain two Int values.
// Retail reads each node link at +0x0C, then passes that node to the matched linkNode_009F4D80 method.
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// stlport

#include "coord.h"
#include <vector>

struct Gen_t_009f51f0_p8cd { Int x, y; };

struct Rva009F59D0Node
{
	char m_pad00[0x0c];
	Rva009F59D0Node *m_next;
};

struct Gen009F5040Node;

class Gen_dtor_009f2600
{
public:
	void cleanup();
};

class Gen009F5040
{
public:
	void linkNode_009F4D80(Gen009F5040Node *node);
};

class Rva009F59D0
{
public:
	void method(unsigned level);

	Int m_0000[6];
	_STL::vector<ICoord2D> m_0018[17];
	Rva009F59D0Node *m_00E4;
	char m_00E8[4];
	Int m_00EC;
	char m_00F0[4];
};

void Rva009F59D0::method(unsigned level)
{
	if (level > 11)
		return;

	int mask = 1 << level;
	if (mask == m_00EC)
		return;
	m_00EC = mask;

	unsigned count = 1;
	while (level != 0) {
		--level;
		count = count * 4 + 1;
	}

	((Gen_dtor_009f2600 *)this)->cleanup();

	for (int i = 0; i < 17; ++i) {
		Gen_t_009f51f0_p8cd fillValue = {0, 0};
		_STL::vector<Gen_t_009f51f0_p8cd> fresh(count, fillValue);
		m_0018[i] = *reinterpret_cast<const _STL::vector<ICoord2D> *>(&fresh);
	}

	Rva009F59D0Node *node = m_00E4;
	while (node != 0) {
		((Gen009F5040 *)this)->linkNode_009F4D80(
			reinterpret_cast<Gen009F5040Node *>(node));
		node = node->m_next;
	}
}
