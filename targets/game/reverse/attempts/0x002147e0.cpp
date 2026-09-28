// ?apply@Rva002147E0Owner@@QAEXMPAUDamageInfo@@@Z
// partial score=0.383249 date=2026-09-28
// ?apply@Rva002147E0Owner@@QAEXMPAUDamageInfo@@@Z
// cl: /EHsc
// Scratch conversion probe for retail RVA 0x002147E0 (394 bytes).
struct DamageInfo
{
	unsigned char beforeSourceID[8];
	int sourceID;
};

struct Player;
struct Object;
struct Module;

struct Rva003A04A0Filter
{
	bool accepts(Object *, Player *);
};

struct NameKeyGenerator
{
	unsigned int nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct GameLogic
{
	Object *findObjectByID(int);
};
extern GameLogic *TheBfmeGameLogic;
extern float BfmeZeroRange;

struct Player;

struct Object
{
	Player *getControllingPlayer() const;
	bool testStatus(int) const;
	Module *findModule(unsigned int) const;
	void onDie(DamageInfo *);
};

struct Module
{
	void rva002A21F0();
	void rva002A30D0();
	unsigned char pad[0x2c];
	unsigned int timer;
};

struct Rva002147E0Owner
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual float health() const;
	void apply(float, DamageInfo *);
	unsigned char *moduleData() const
	{
		return *(unsigned char **)((char *)this - 12);
	}
	Object *object() const
	{
		return *(Object **)((char *)this - 8);
	}
	void rva002103A0(float, DamageInfo *);
};

void Rva002147E0Owner::apply(float amount, DamageInfo *info)
{
 if(amount == 0.0f) return;
 {
  Object *objectPointer=object();
  unsigned char *data=moduleData();
  bool fatal=false;
  bool accepted=false;
  if(-health()>=amount) {
   fatal=true;
   if(!data[0x60]) accepted=true;
   else if(info) {
    Object *savedObject=objectPointer;
    objectPointer=TheBfmeGameLogic->findObjectByID(info->sourceID);
    if(objectPointer && ((Rva003A04A0Filter*)(data+0x5c))->accepts(objectPointer,savedObject->getControllingPlayer())) accepted=true;
    objectPointer=savedObject;
   }
  }
  rva002103A0(amount,info);
  static unsigned int respawnUpdateKey=TheNameKeyGenerator->nameToKey("RespawnUpdate");
  Module *module=objectPointer->findModule(respawnUpdateKey);
  if(!accepted) {
   if(!fatal || !module) return;
   if(objectPointer->testStatus(0x4f)) {
    module->rva002A21F0();
    module->timer=0;
    objectPointer->onDie(info);
    return;
   }
   module->rva002A30D0();
   objectPointer->onDie(info);
   return;
  }
  if(module) module->rva002A21F0();
 }
}
