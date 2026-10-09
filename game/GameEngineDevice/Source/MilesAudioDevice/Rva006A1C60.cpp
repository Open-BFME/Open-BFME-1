// cl: /O2 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x006A1C60, 752 bytes.
// See identity_evidence/006a1c60-audio-region-scan.md.
// These are address-qualified ABI/layout views, not additional engine classes.
// Keep each indexed vector read: caching an entry reference changes allocation.
#include <vector>
extern void j_00001ece();
extern void j_0000a7db();
extern void j_0000d6ed();
extern void j_00010343();
extern void j_0001f253();
struct Rva006A1C60Coord {
	float x,y,z;
};
struct Rva006A1C60Event {
	char pad[0x28];
	int field28;
	unsigned objectID;
	int ownerType;
	unsigned rva000B2280() {
		typedef unsigned (Rva006A1C60Event::*Fn)();
		union {void (*p)();
			Fn f;} u;
		u.p=j_00010343;
		return (this->*u.f)();
	}
};
struct Rva006A1C60Region {
	bool rva0018FA20(Rva006A1C60Coord &p) const {
		typedef bool (Rva006A1C60Region::*Fn)(Rva006A1C60Coord &)const;
		union {void (*p)();
			Fn f;} u;
		u.p=j_0000a7db;
		return (this->*u.f)(p);
	}
};
struct Rva006A1C60Object {
	bool rva001BEA90(const Rva006A1C60Region *p) const {
		typedef bool (Rva006A1C60Object::*Fn)(const Rva006A1C60Region *)const;
		union {void (*p)();
			Fn f;} u;
		u.p=j_0000d6ed;
		return (this->*u.f)(p);
	}
};
struct Rva006A1C60Logic {
	Rva006A1C60Object *rva0009A510(unsigned id) {
		typedef Rva006A1C60Object *(Rva006A1C60Logic::*Fn)(unsigned);
		union {void (*p)();
			Fn f;} u;
		u.p=j_0001f253;
		return (this->*u.f)(id);
	}
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva006A1C60Inner {
	char pad[0x14];
	Rva006A1C60Event *event;
	int pad18;
	Rva006A1C60Coord pos;
	int pad28;
	float volume;
	int index;
	char pad34[10];
	bool hasPos;
};
struct Rva006A1C60Wrapper {
	Rva006A1C60Inner *inner;
};
struct Rva006A1C60Settings {
	char pad[0x78];
	float range;
};
struct Rva006A1C60Pair {
	Rva006A1C60Region *region;
	float value;
};
class Rva006A1C60 {
	char pad0[12];
	Rva006A1C60Settings *settings;
	char pad10[0x626];
	bool changed;
	char pad637[0x4a5];
	std::vector<Rva006A1C60Pair> regions;

	public:

	void body(Rva006A1C60Wrapper *w, unsigned char *out);
	Rva006A1C60Coord *rva00695F80(Rva006A1C60Coord *p,Rva006A1C60Event *e,bool *v) {
		typedef Rva006A1C60Coord *(Rva006A1C60::*Fn)(Rva006A1C60Coord *,Rva006A1C60Event *,bool *);
		union {void (*p)();
			Fn f;} u;
		u.p=j_00001ece;
		return (this->*u.f)(p,e,v);
	}
};
// Ported from Open BFME 2 Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp.
// ?rva006A1C10@@YA_NAAURva006A1C60Wrapper@@PBURva006A1C60Coord@@PAURva006A1C60Region@@@Z
static bool rva006A1C10(Rva006A1C60Wrapper &playing, const Rva006A1C60Coord *pos, Rva006A1C60Region *trigger)
{
    if (playing.inner->event->ownerType == 2 && TheGameLogic) {
        Rva006A1C60Object *object = ((Rva006A1C60Logic *)TheGameLogic)->rva0009A510(playing.inner->event->rva000B2280());
        if (object)
            return object->rva001BEA90(trigger);
    }
    return trigger->rva0018FA20(*(Rva006A1C60Coord *)pos);
}
void Rva006A1C60::body(Rva006A1C60Wrapper *w,unsigned char *out) {
	if(regions.empty()) {
		*out = w->inner->volume != 1.0f ? 1 : 0;
		w->inner->volume=1.0f;
		return;
	}
	if(w->inner->event->field28) {
		*out=w->inner->volume!=0.0f ? 1 : 0;
		w->inner->volume=0.0f;
		return;
	}
	bool valid;
	Rva006A1C60Coord pos;
	rva00695F80(&pos,w->inner->event,&valid);
	if(!valid) {
		if(!w->inner->hasPos) {
			*out=w->inner->volume!=1.0f ? 1 : 0;
			w->inner->volume=1.0f;
			return;
		}
		if(!changed) {
			*out=0;
			return;
		}
		pos=w->inner->pos;

	}
	else if(!changed) {
		float x=pos.x-w->inner->pos.x;
		float y=pos.y-w->inner->pos.y;
		float range=settings->range;
		if(x<=range && x>=-range && y<=range && y>=-range) {
			*out=0;
			return;
		}

	}
	w->inner->pos=pos;
	w->inner->hasPos=true;
	int start=w->inner->index;
	if(start<0) start=0;
	else if((unsigned)start>=regions.size()) start=regions.size()-1;
	int i=start;
	int best=start;
	float value=1.0f;
	do {
		if(regions[i].value<value) {
			Rva006A1C60Region *region=regions[i].region;
			bool contains;
			contains=rva006A1C10(*w, &pos, region);
			if(contains) {
				value=regions[i].value;
				best=i;
			}

		}
		if(i==0) i=regions.size();
		--i;

	}while(i!=start);
	*out=value!=w->inner->volume ? 1 : 0;
	w->inner->volume=value;
	w->inner->index=best;
}
