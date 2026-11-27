// ?transition00409610@BuffEntry00409E20@@QAE_NHHPAX0H@Z
// Retail 0x00409610: BuffEntry transition called by BuffState00409E20::apply
// (six 0x44-byte records). Address-derived identity; class ownership unproved.
// The saved effect state s08 is volatile only to give it its retail stack home.

struct EffectHandle00409E20 {
	virtual void Slot00(int);
	char bytes04[4];
	int field08;
	int field0c;
};
struct BuffEntry00409E20 {
	int field00; bool field04; char bytes05[3]; int field08; int field0c;
	int field10; int field14; EffectHandle00409E20 *field18; void *field1c; char bytes20[0x24];
	bool transition00409610(int type,int mode,void *arg,void *owner,int count);
};
class ThingTemplate;
class Xfer;
struct Snapshot0040A260 {
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void transfer(Xfer *);
};
struct BuffLogic {
	Snapshot0040A260 *addBuff(const ThingTemplate *,void *);
};
// Original pointer cell VA 0x012EF4F0; use its existing recorded owner type.
class Manager012EF4F0;
extern Manager012EF4F0 *g_012EF4F0;
struct GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrame00409610 { char bytes00[0x3c]; int field3c; };

bool BuffEntry00409E20::transition00409610(int type,int mode,void *arg,void *owner,int count) {
	int k = type;
	void *p = arg;
	void *q = owner;
	if (k >= 6 || k < 1 || !p || !q) {
		return 0;
	}
	if (!field18) {
		field08 = k;
		field0c = mode;
		field1c = p;
		field18 = (EffectHandle00409E20 *)((BuffLogic *)g_012EF4F0)->addBuff((const ThingTemplate *)p,q);
	} else if (p != field1c) {
		volatile int s08 = field18->field08;
		int s0c = field18->field0c;
		field18->Slot00(1);
		field18 = 0;
		field08 = k;
		field0c = mode;
		field1c = p;
		field18 = (EffectHandle00409E20 *)((BuffLogic *)g_012EF4F0)->addBuff((const ThingTemplate *)p,q);
		if (field18) {
			field18->field08 = s08;
			field18->field0c = s0c;
		}
	}
	if (field18) {
		field10 = count;
		field04 = 1;
		field14 = ((GameLogicFrame00409610 *)TheGameLogic)->field3c + count;
		return 1;
	}
	field04 = 0;
	return 0;
}
