// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Drawable;
typedef unsigned int DrawableID;

class GameClient
{
public:
	Drawable *findDrawableByID(DrawableID id);

private:
	unsigned char m_prefix[0x14];
	_STL::hash_map<DrawableID, Drawable *> m_lookup;
};

// ?findDrawableByID@GameClient@@QAEPAVDrawable@@I@Z
Drawable *GameClient::findDrawableByID(DrawableID id)
{
	_STL::hash_map<DrawableID, Drawable *>::iterator it = m_lookup.find(id);
	if (it == m_lookup.end())
		return 0;
	return (*it).second;
}
