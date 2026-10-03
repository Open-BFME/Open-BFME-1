// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object
class Player
{
public:
	unsigned char m_bfmeHeadCA[0x1c4];
	unsigned int m_bfmePlainCA;
	unsigned int m_bfmeAltCA;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Drawable
{
public:
	void setIndicatorColor(unsigned int colour);
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadCA[0x218];
	int m_bfmeModeCA;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;


// Native Object layout, slot10 getDrawable, Team::getControllingPlayer and
// Drawable::setIndicatorColor establish owner/callees; method stays opaque.
// The local unsigned color helper is reconstruction structure, not a second
// public getNightIndicatorColor signature. See identity_evidence/001c15f0-native-getters.md.
#define OBJECT_TU_MEMBERS void rva001C15F0(); unsigned int getIndicatorColor() const;
#include "object.h"
inline unsigned int Object::getIndicatorColor() const {
 if(m_indicatorColor) return m_indicatorColor;
 if(m_team) { Player *p=m_team->getControllingPlayer(); if(p) return p->m_bfmePlainCA; }
 return 0xff000000;
}
static unsigned int rva001C15F0NightColor(const Object *self) {
 if(self->m_indicatorColor) return self->m_indicatorColor;
 if(self->m_team) { Player *p=self->m_team->getControllingPlayer(); if(p) return p->m_bfmeAltCA; }
 return 0xff000000;
}
void Object::rva001C15F0() {
 Drawable *r=getDrawable();
 if(r==0) return;
 if(((const Rva006C9270GlobalData *)TheWritableGlobalData)->m_bfmeModeCA==4) r->setIndicatorColor(rva001C15F0NightColor(this));
 else r->setIndicatorColor(getIndicatorColor());
}
