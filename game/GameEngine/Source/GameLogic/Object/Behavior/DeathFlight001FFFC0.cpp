// cl: /DNDEBUG /MD /EHsc
// Retail 0x001FFFC0 (313 bytes). Address-derived owner: a slow-death
// interface reads module data at this-0x20 and Object at this-0x1C.
// Copies an adjusted flight endpoint and invokes the PhysicsBehavior transition.
// The AI call routes through 0x00042B9A to 0x0027B000: ECX receiver;
// float + two coordinate pointers + 24-byte value; all returns pop 0x24.
extern "C" double sin(double); extern "C" double cos(double);
#pragma intrinsic(sin,cos)
class DamageInfo;
class SlowDeathBehavior { public: virtual void beginSlowDeath(const DamageInfo *); };
struct Rva0029AB10Coord3D { float x,y,z; };
struct SixWords001FFFC0 { unsigned int words[6]; };
struct Data001FFFC0 { char pad000[0x224]; SixWords001FFFC0 field224; float field23c; };
struct Speed001FFFC0 { char pad000[0x470]; float field470; };
class PhysicsBehavior { public: char pad00[0x5d]; bool field5d; void rva0029AB10(const Rva0029AB10Coord3D *,float,unsigned int); };
class AI001FFFC0 { public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00c();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01c();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02c();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03c();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04c();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05c();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06c();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07c();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08c();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09c();
virtual void slot0a0();
virtual void slot0a4();
virtual void slot0a8();
virtual void slot0ac();
virtual void slot0b0();
virtual void slot0b4();
virtual void slot0b8();
virtual void slot0bc();
virtual void slot0c0();
virtual void slot0c4();
virtual void slot0c8();
virtual void slot0cc();
virtual void slot0d0();
virtual void slot0d4();
virtual void slot0d8();
virtual void slot0dc();
virtual void slot0e0();
virtual void slot0e4();
virtual void slot0e8();
virtual void slot0ec();
virtual void slot0f0();
virtual void slot0f4();
virtual void slot0f8();
virtual void slot0fc();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10c();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11c();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12c();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13c();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14c();
virtual Speed001FFFC0 *slot150();
int rva0027B000(float, Rva0029AB10Coord3D *, Rva0029AB10Coord3D *, SixWords001FFFC0);
};
class TerrainLogic { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual float slot18(float,float,void *);
};
extern TerrainLogic *TheTerrainLogic;
struct Object001FFFC0 { char pad00[0x38]; Rva0029AB10Coord3D field38; float field44; char pad48[0x114-0x48]; unsigned int field114; char pad118[0x204-0x118]; AI001FFFC0 *field204; PhysicsBehavior *field208; };
class DeathFlight001FFFC0 { public:
char pad00[0xa0]; Rva0029AB10Coord3D fielda0;
void begin(const DamageInfo *info);
};
void DeathFlight001FFFC0::begin(const DamageInfo *info)
{
 Data001FFFC0 *data=*(Data001FFFC0 **)((char *)this-0x20);
 ((SlowDeathBehavior *)this)->SlowDeathBehavior::beginSlowDeath(info);
 Object001FFFC0 *object=*(Object001FFFC0 **)((char *)this-0x1c);
 Rva0029AB10Coord3D position; position.x=object->field38.x; position.y=object->field38.y; position.z=object->field38.z;
 AI001FFFC0 *ai=object->field204;
 PhysicsBehavior *physics=object->field208;
 if(ai) {
  if(object->field114 & 0x10000000) {
   Speed001FFFC0 *speed=ai->slot150();
   if(!speed) return;
   float distance=speed->field470*5.0f;
   if(distance>50.0f) {
    float angle=object->field44;
    position.x += (float)cos(angle)*distance;
    position.y += (float)sin(angle)*distance;
    physics->field5d=true;
   }
  }
  ai->rva0027B000(data->field23c,&position,&position,data->field224);
 }
 position.z=TheTerrainLogic->slot18(position.x,position.y,0);
 fielda0=position;
 physics->rva0029AB10(&fielda0,0.0f,0x41f00000);
}


