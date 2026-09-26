// cl: /DNDEBUG /MD /EHsc
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <new>
#include <vector>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail 0010B550 returns a vector by value through the hidden stack
// argument (RET4). The owner list starts at +8; each node carries an
// AsciiString at +8 and its successor at +108. No semantic owner is known.
class Rva0010B550Owner
{
	char unknown00[8];
	struct Rva0010B550Node *head;
public:
	_STL::vector<AsciiString> collect();
};

struct Rva0010B550Node
{
	char unknown00[8];
	AsciiString string08;
	char unknown0C[0xFC];
	Rva0010B550Node *next108;
};

_STL::vector<AsciiString> Rva0010B550Owner::collect()
{
	_STL::vector<AsciiString> result;
	Rva0010B550Node *node = head;
	while (node)
	{
		result.push_back(node->string08);
		node = node->next108;
	}
	return result;
}
