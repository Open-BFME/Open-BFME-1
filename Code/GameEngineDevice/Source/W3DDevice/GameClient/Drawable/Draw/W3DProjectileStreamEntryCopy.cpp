// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

// BFME extends W3DProjectileStreamDraw with a vector of these 16-byte records.
struct BfmeW3DProjectileStreamEntry
{
	unsigned int m_objectID;
	AsciiString m_name;
	unsigned int m_frame;
	unsigned int m_expirationFrame;
};

typedef BfmeW3DProjectileStreamEntry *(*BfmeProjectileStreamEntryCopyFn)(
	BfmeW3DProjectileStreamEntry *, BfmeW3DProjectileStreamEntry *,
	BfmeW3DProjectileStreamEntry *, const _STL::random_access_iterator_tag &, int *);

BfmeProjectileStreamEntryCopyFn BfmeProjectileStreamEntryCopyAnchor =
	&_STL::__copy<BfmeW3DProjectileStreamEntry *, BfmeW3DProjectileStreamEntry *, int>;
