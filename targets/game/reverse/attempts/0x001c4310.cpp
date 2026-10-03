// ?DescribeObject@@YA?AVAsciiString@@PBVObject@@@Z
// partial score=0.0 date=2026-10-03
// cl: /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "../../inputs/reference/shims/sweep/windows.h"
#include "PreRTS.h"
#include "Common/Team.h"
#include "Common/Player.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
template<typename T> inline bool StringBase<T>::isNotEmpty() const { return m_data && m_data->length != 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->~StringBase<wchar_t>(); }

inline Player* Object::getControllingPlayer() const {
 const Team *team=*(Team*const*)((const char*)this+0x23c);
 return team ? team->getControllingPlayer() : 0;
}
static __forceinline const AsciiString &rva001C4310TemplateName(const Object *obj) {
 const ThingTemplate *t=*(const ThingTemplate*const*)((const char*)obj+4);
 if(t && *(const void*const*)((const char*)t+4)) t=(const ThingTemplate*)t->getFinalOverride();
 return *(const AsciiString*)((const char*)t+0x20);
}
AsciiString DescribeObject(const Object *obj) {
 if(!obj)return "<No Object>";
 Player *player=obj->getControllingPlayer();
 AsciiString ret;
 const AsciiString &name=*(const AsciiString*)((const char*)obj+0x84);
 if(name.isNotEmpty()) {
  ret.format("Object %d (%s) [%s, owned by player %d (%ls)]",
   *(const ObjectID*)((const char*)obj+0x74),name.str(),rva001C4310TemplateName(obj).str(),
   player?*(const int*)((const char*)player+0x24):0,
   player?(player->*&Player::getPlayerDisplayName)().str():L"<unknown>");
 } else {
  ret.format("Object %d [%s, owned by player %d (%ls)]",
   *(const ObjectID*)((const char*)obj+0x74),rva001C4310TemplateName(obj).str(),
   player?*(const int*)((const char*)obj->getControllingPlayer()+0x24):0,
   player?(obj->getControllingPlayer()->*&Player::getPlayerDisplayName)().str():L"<unknown>");
 }
 return ret;
}
