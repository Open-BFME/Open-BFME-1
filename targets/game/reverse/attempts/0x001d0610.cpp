// ?updateObjValuesFromMapProperties@Object@@QAEXPAVDict@@@Z
// partial score=1.0 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Object::updateObjValuesFromMapProperties -- BFME 1.03 RVA 001D0610 / 1951 B.
// Identity: AIPlayer::onStructureProduced and Bridge constructor call this body
// through its ILT. Ported from the ZH Object.cpp property updater, with every
// BFME-only path reconstructed from the retail image.
// Keep the BFME storage/vtable views local: the reference Object declaration
// is used for the method identity; no ZH member offset is used by this body.
// Object offsets: name 84; model flags 110 (320 bits); vision 194/198;
// contain 1FC; body 200; AI 204; selectable 340. The contain and selectable
// fields are name_oracle witnesses. Virtual slots and all remaining offsets
// are explicit address-qualified views; no new semantic member identity.
// Callee ABI was checked with callee_protos.py and the actual target bodies.
// Ambient ownership matches DrawableXfer.cpp and DrawableCaptionAndAmbient.cpp:
// refcount at +4; mangle consumes a by-value holder; assignment takes its address.

#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Upgrade.h"
#include "GameLogic/Object.h"

inline AsciiString::~AsciiString(){((StringBase<char>*)this)->StringBase<char>::~StringBase();}
template<class T> inline void StringBase<T>::clear(){releaseBuffer();}
template<class T> inline bool StringBase<T>::isEmpty() const {return !m_data || m_data->length==0;}

template<class T> __forceinline T& rva001D0610Field(void *p, int off) { return *(T*)((char*)p+off); }
class Rva001D0610AudioInfo {public: virtual ~Rva001D0610AudioInfo(); long refs;
 void addRef(){InterlockedIncrement(&refs);} void releaseRef(){if(InterlockedDecrement(&refs)<=0)delete this;}
};
template<class T> class Rva001D0610Ref {public: T *p; Rva001D0610Ref():p(0){} Rva001D0610Ref(const Rva001D0610Ref& r):p(r.p){if(p)p->addRef();} ~Rva001D0610Ref(){if(p)p->releaseRef();} };
class Rva001D0610Drawable;
class Rva001D0610Horde {public:
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
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot4a();
virtual void slot4b();
virtual void slot4c();
virtual void slot4d();
virtual void slot4e();
virtual void slot4f();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot168(int);

};
class Rva001D0610Contain {public:
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
virtual Rva001D0610Horde *slot68();

};
class Rva001D0610Body {public:
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
virtual void slot54(float,bool);
virtual void slot58(float,bool);
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
virtual void slot84(bool);

};
class Rva001D0610Audio {public:
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
virtual void slot43();
virtual void slot44();
virtual void slot114(Rva001D0610AudioInfo*);

};
extern Rva001D0610Audio *Rva012ED668;
class Rva001D0610Override {public:void *rva00087A80();};
class Rva001D0610Drawable {public:
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
virtual void slot34();

 void rva00411F80(bool); void rva0041AA90(bool); void rva0041CCD0(const BitFlags<320>&,unsigned,unsigned);
 void rva0041ABE0(); void rva0041B040(bool); void rva00417330(Rva001D0610Ref<Rva001D0610AudioInfo>); void rva0041AD20(const Rva001D0610Ref<Rva001D0610AudioInfo>&);
 void scale(float v){float current=rva001D0610Field<float>(this,0x1f8);rva001D0610Field<float>(this,0x1f8)=current*v;rva0041AA90(true);}
 bool enabled() {return rva001D0610Field<bool>(this,0x141);}
 void *getFinalTemplate(){void *p=rva001D0610Field<void*>(this,4);if(p && rva001D0610Field<void*>(p,4))return ((Rva001D0610Override*)rva001D0610Field<void*>(p,4))->rva00087A80();return p;}

};
class Rva001D0610AI {public:void rva0027DEF0(int);void rva0026ED10();void rva0026ED70(void*);};
class Rva001D0610Lua {public:void *rva002EBF60(const AsciiString&);};
extern Rva001D0610Lua *Rva012F060C;
extern const StaticNameKey Rva012A7800;
void rva000B6030(Dict*,Rva001D0610Drawable*,void*,bool*,Rva001D0610Ref<Rva001D0610AudioInfo>*,bool*);
class Rva001D0610Object {public:
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
virtual Rva001D0610Drawable *slot28();

 Rva001D0610Body* body(){return rva001D0610Field<Rva001D0610Body*>(this,0x200);}
 Rva001D0610Contain* contain(){return rva001D0610Field<Rva001D0610Contain*>(this,0x1fc);}
 Rva001D0610AI* ai(){return rva001D0610Field<Rva001D0610AI*>(this,0x204);}
 Rva001D0610Drawable* drawable(){return rva001D0610Field<Rva001D0610Drawable*>(this,0x80);}
 bool rva001C98C0()const;
 void selectable(bool b){rva001D0610Field<bool>(this,0x340)=b;if(drawable())drawable()->rva00411F80(b);}
 void condition(int bit,bool set){ BitFlags<320> &flags=rva001D0610Field<BitFlags<320> >(this,0x110);
 if(set){if(flags.test(bit))return;flags.set(bit);}else{if(!flags.test(bit))return;flags.set(bit,0);}
 if(drawable())drawable()->rva0041CCD0(flags,0,0);if(ai())ai()->rva0026ED10();}

};

void Object::updateObjValuesFromMapProperties(Dict* properties)
{
	Rva001D0610Object *o=(Rva001D0610Object*)this;
	Bool exists;

	AsciiString valStr;
	Bool valBool = false;
	Int valInt = 0;
	Real valReal = 0.0f;

	valStr = properties->getAsciiString(TheKey_objectName, &exists);
	if (exists) {
		rva001D0610Field<AsciiString>(this,0x84)=valStr;
	}

	valInt = properties->getInt(TheKey_objectMaxHPs, &exists);
	if (exists && valInt >= 0) {
		Rva001D0610Body* body = o->body();
		if (body)	{
			body->slot58(valInt,false);
		}
	}

	Rva001D0610Horde *horde;
 if (o->contain() && (horde=o->contain()->slot68())!=0) {
  horde->slot168(properties->getInt(TheKey_objectInitialHealth,&exists));
 } else {
  valInt=properties->getInt(TheKey_objectInitialHealth,&exists);
  if(exists){Rva001D0610Body *body=o->body();if(body)body->slot54(valInt,false);}
 }

	// set the aggressiveness/mood
	valInt = properties->getInt(TheKey_objectAggressiveness, &exists);
	if (exists) {
		Rva001D0610AI *ai = o->ai();
		if (ai)
		{
			ai->rva0027DEF0(valInt);
		}
	}
	
	// set recruitable
	valBool = properties->getBool(TheKey_objectRecruitableAI, &exists);
	if (exists) {
		if (o->ai())
		{
			rva001D0610Field<bool>(o->ai(),0x32c)=valBool;
		}
	}
	
	// set selectable
	valBool = properties->getBool(TheKey_objectSelectable, &exists);
	if (exists) {
		if (valBool != o->rva001C98C0()) {
			o->selectable(valBool);
		}
	}
	
	// set the stopping distance
	valReal = properties->getReal(TheKey_objectStoppingDistance, &exists);
	if (exists && valReal >= 0.5f)
	{
		if (o->ai() && rva001D0610Field<void*>(o->ai(),0x1cc))
		{
			void *loco = rva001D0610Field<void*>(o->ai(),0x1cc);
			rva001D0610Field<float>(loco,0x38)=valReal;
		}
	}
	
	// set the disabledness of this object
	valBool = properties->getBool(TheKey_objectEnabled, &exists);
	if (exists) {
		setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !valBool);
	}

	// set the disabledness of this object
	valBool = properties->getBool(TheKey_objectPowered, &exists);
	if (exists) {
		setScriptStatus(OBJECT_STATUS_SCRIPT_UNPOWERED, !valBool);
	}

	// set the invulnerability of the object
	valBool = properties->getBool(TheKey_objectIndestructible, &exists);
	if (exists) {
		Rva001D0610Body* body = o->body();
		if (body)	{
			body->slot84(valBool);
		}
	}

	// set the sellability of the object
	valBool = properties->getBool(TheKey_objectUnsellable, &exists);
	if (exists) {
		setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, valBool);
	}

	//Set the player targetable setting of the object
	valBool = properties->getBool( TheKey_objectTargetable, &exists );
	if( exists ) 
	{
		setScriptStatus(OBJECT_STATUS_SCRIPT_TARGETABLE, valBool);
		Rva001D0610Drawable *d=o->slot28();if(d)d->slot34();
	}

	// adjust the vision distance of this object, overriding its default vision distance
	valInt = properties->getInt(TheKey_objectVisualRange, &exists);
	if (exists)
	{
		if (valInt < 0)
			valInt = 0;
		rva001D0610Field<float>(this,0x194) = INT_TO_REAL(valInt);
	}

	// adjust the shroud clearing distance of this object, overriding its default distance
	valInt = properties->getInt(TheKey_objectShroudClearingDistance, &exists);
	if (exists)
	{
		if (valInt < 0)
			valInt = 0.0f;
		rva001D0610Field<float>(this,0x198) = INT_TO_REAL(valInt);
	}


	Int upgradeNum = 0;
	do 
	{
		AsciiString keyName;
		keyName.format("%s%d", TheNameKeyGenerator->keyToName(TheKey_objectGrantUpgrade).str(), upgradeNum);
		valStr = properties->getAsciiString(NAMEKEY(keyName), &exists);

		if (exists) 
		{
			const UpgradeTemplate *ut = TheUpgradeCenter->findUpgrade(valStr);
			if (ut)
				giveUpgrade(ut);
		}
		else 
		{
			valStr.clear();
		}

		++upgradeNum;
	} while (!valStr.isEmpty());
	
	Rva001D0610Drawable *drawable = o->slot28();
  if ( drawable )
  {
    float scale=properties->getReal(Rva012A7800,&exists);
    if(exists && scale!=1.0f)drawable->scale(scale);
    valInt = properties->getInt(TheKey_objectTime, &exists);
    if (exists)
    {
      switch (valInt)
      {
      case 1:
        o->condition(7,false);
        break;
      case 2:
        o->condition(7,true);
        break;
      default:
        break;
      }
    }
    
    valInt = properties->getInt(TheKey_objectWeather, &exists);
    if (exists)
    {
      switch (valInt)
      {
      case 1:
        o->condition(8,false);
        break;
      case 2:
        o->condition(8,true);
        break;
      default:
        break;
      }
    }
    

    valStr=properties->getAsciiString(TheKey_objectScriptAttachment,&exists);
    if(exists && !valStr.isEmpty()){
     Rva001D0610AI *ai=o->ai();void *script=Rva012F060C->rva002EBF60(valStr);if(ai)ai->rva0026ED70(script);
    }
    bool forceOff=false;
    bool enabled=false;
    Rva001D0610Ref<Rva001D0610AudioInfo> info;
    rva000B6030(properties,drawable,drawable->getFinalTemplate(),&forceOff,&info,&enabled);
    if(forceOff)drawable->rva0041ABE0();
    else {
     if(!enabled)drawable->rva0041B040(false);
     if(info.p){drawable->rva00417330(info);Rva012ED668->slot114(info.p);drawable->rva0041AD20(info);}
     if(enabled && !drawable->enabled())drawable->rva0041B040(true);
    }
  }
}
