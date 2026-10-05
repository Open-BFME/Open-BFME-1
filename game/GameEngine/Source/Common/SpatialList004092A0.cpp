// Address-derived ABI views; offsets and slot are witnessed in retail 0x004092A0.
struct Position004092A0 { float x,y,z; };
struct AudioView004092A0 {
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot1a();
 virtual void slot1b();
 virtual void slot1c();
 virtual void slot1d();
 virtual void slot1e();
 virtual void slot1f();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot2a();
 virtual void slot2b();
 virtual void slot2c();
 virtual void slot2d();
 virtual void slot2e();
 virtual void slot2f();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot3a();
 virtual void slot3b();
 virtual void slot3c();
 virtual void slot3d();
 virtual void slot3e();
 virtual void slot3f();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual const Position004092A0 *position();
};
// The retail global at 0x012ED668 is EA's AudioManager *TheAudio, defined once
// in game/GameEngine/Source/Common/Audio/GameAudio.cpp.  This TU keeps its own
// address-derived view of that object and casts at the use, so the reference
// names the one linked global.
class AudioManager;
extern AudioManager *TheAudio;
static inline AudioView004092A0 *localAudio004092A0() { return (AudioView004092A0 *)TheAudio; }
struct FieldParse;
struct AnimationSoundClientBehaviorGlobalSetting
{
 float m_minMicrophoneDistanceToDirty;
 static const FieldParse m_fieldParseTable[];
};
extern AnimationSoundClientBehaviorGlobalSetting TheAnimationSoundClientBehaviorGlobalSetting;
struct Node004092A0 {
 char bytes00[0x14]; Node004092A0 *next14, *prev18;
 void update006059F0();
};
struct SpatialList004092A0 {
 char bytes00[8]; Node004092A0 *field08,*field0c,*field10,*field14; int field18;
 Position004092A0 position1c;
 void update();
};

void SpatialList004092A0::update() {
 const Position004092A0 *pos = localAudio004092A0()->position();
 Position004092A0 delta; delta.x=pos->x; delta.y=pos->y; delta.z=pos->z;
 delta.x -= position1c.x; delta.y -= position1c.y; delta.z -= position1c.z;
 if (delta.x*delta.x + delta.y*delta.y + delta.z*delta.z > TheAnimationSoundClientBehaviorGlobalSetting.m_minMicrophoneDistanceToDirty*TheAnimationSoundClientBehaviorGlobalSetting.m_minMicrophoneDistanceToDirty && field14) {
  if (field08) { field14->next14=field08; field08->prev18=field14; }
  field08=field10;
  if (!field0c) field0c=field14;
  field10=0; field14=0;
 }
 if (!field10) position1c=*localAudio004092A0()->position();
 Node004092A0 *p=field08;
 while (p) { Node004092A0 *n=p->next14; p->update006059F0(); p=n; }
}
