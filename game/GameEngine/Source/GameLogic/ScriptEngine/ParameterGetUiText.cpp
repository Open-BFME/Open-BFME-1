// cl: /Iinputs/reference/shims/zhcanonascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Parameter::getUiText at RVA 0x00352E80: 3667 code bytes, one NOP,
// and 344 bytes of native switch tables, ending at 0x00353E2C.
// Named matched Condition::getUiText and ScriptAction::getUiText callers
// reach this const method through its ILT. The original Scripts.cpp method
// supplies the algorithm; retail adds parameter kinds and changes enum values.
// The 64-entry table proves every case value; kinds without an independent
// BFME enum declaration keep address-derived names. Parameter_WriteParameter
// independently witnesses type+0, integer+8, real+0xC, string+0x10 and coord+0x14.
//
// The coordinate call follows ILT 0x3A882 to the existing 41-byte body at
// 0x0034FEE0. Its type==16 guard and coordinate copy prove the original
// Parameter::getCoord3D behavior; its existing address-bound ABI is retained.
// String constructors, releaseBuffer, format, concat, isEmpty and assignment
// are the independently resolved retail callees, with native WWLib headers.
// Retail's Kind/Object Status/Buildable fallback strings contain the legacy
// trigraph results (?^ and ?]); preserve the actual compiled text.
// Array operands: borders VA010E8430; buildability VA012AC3B0; surfaces
// VA012B3E34; shake intensities VA012B3E40; spline names VA012B577C;
// emotion names VA012A687C (BitFlags<10>::s_bitNameList). Spline names keep their address identity.
extern "C" unsigned __cdecl strlen(const char *);
#pragma intrinsic(strlen)
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "basetype.h"
#include "Common/BorderColors.h"

template<> inline bool StringBase<char>::isNotEmpty() const { return m_data && m_data->length != 0; }
template<> inline void StringBase<char>::set(const char *s) { set(s,s ? (int)strlen(s) : 0); }

class KindOfMaskType { public: static const char *getNameFromSingleBit(int); };
struct BfmeVecYG;
class BfmeThingYG { public: void bfmeReadYG(BfmeVecYG *) const; };
extern const char *BuildableStatusNames[];
extern const char *Surfaces[];
extern const char *ShakeIntensities[];
extern const char *Rva012B577CNames[];
#include "Common/BitFlags.h"

class Parameter {
public:
 enum ParameterType {
  INT=0,
  REAL,
  SCRIPT,
  TEAM,
  COUNTER,
  FLAG,
  COMPARISON,
  WAYPOINT,
  BOOLEAN,
  TRIGGER_AREA,
  TEXT_STRING,
  SIDE,
  SOUND,
  SCRIPT_SUBROUTINE,
  UNIT,
  OBJECT_TYPE,
  COORD3D,
  ANGLE,
  TEAM_STATE,
  RELATION,
  AI_MOOD,
  DIALOG,
  MUSIC,
  MOVIE,
  WAYPOINT_PATH,
  LOCALIZED_TEXT,
  BRIDGE,
  KIND_OF_PARAM,
  ATTACK_PRIORITY_SET,
  Rva00352E80Type29,
  RADAR_EVENT_TYPE,
  SPECIAL_POWER,
  SCIENCE,
  UPGRADE,
  COMMANDBUTTON_ABILITY,
  BOUNDARY,
  BUILDABLE,
  SURFACES_ALLOWED,
  SHAKE_INTENSITY,
  COMMAND_BUTTON,
  FONT_NAME,
  OBJECT_STATUS,
  COMMANDBUTTON_ALL_ABILITIES,
  SKIRMISH_WAYPOINT_PATH,
  COLOR,
  EMOTICON,
  OBJECT_PANEL_FLAG,
  FACTION_NAME,
  OBJECT_TYPE_LIST,
  REVEALNAME,
  SCIENCE_AVAILABILITY,
  Rva00352E80Type51,
  PERCENT,
  Rva00352E80Type53,
  Rva00352E80Type54,
  Rva00352E80Type55,
  Rva00352E80Type56,
  Rva00352E80Type57,
  Rva00352E80Type58,
  Rva00352E80Type59,
  Rva00352E80Type60,
  Rva00352E80Type61,
  Rva00352E80Type62,
  Rva00352E80Type63
 };
 ParameterType m_paramType;
 bool m_initialized;
 int m_int;
 float m_real;
 AsciiString m_string;
 Coord3D m_coord;
 AsciiString getUiText() const;
};

AsciiString Parameter::getUiText() const {
 AsciiString uiText;
 AsciiString uiString=m_string;
 if (!uiString.isNotEmpty()) uiString.set("???");
 Coord3D pos;
 switch(m_paramType) {
 default: break;
 case SOUND:
 case Rva00352E80Type59: uiText.format("Sound '%s'",uiString.str()); break;
 case SCRIPT: uiText.format("Script '%s'",uiString.str()); break;
 case TEAM_STATE: uiText.format("'%s'",uiString.str()); break;
 case SCRIPT_SUBROUTINE: uiText.format("Subroutine '%s'",uiString.str()); break;
 case ATTACK_PRIORITY_SET: uiText.format("Attack priority set '%s'",uiString.str()); break;
 case WAYPOINT: uiText.format("Waypoint '%s'",uiString.str()); break;
 case WAYPOINT_PATH: uiText.format("Waypoint Path '%s'",uiString.str()); break;
 case Rva00352E80Type51: uiText.format("Camera '%s'",uiString.str()); break;
 case TRIGGER_AREA: uiText.format(" area '%s'",uiString.str()); break;
 case COMMAND_BUTTON: uiText.format("Command button: '%s'",uiString.str()); break;
 case FONT_NAME: uiText.format("Font: '%s'",uiString.str()); break;
 case LOCALIZED_TEXT: uiText.format("Localized String: '%s'",uiString.str()); break;
 case TEXT_STRING: uiText.format("String: '%s'",uiString.str()); break;
 case TEAM: uiText.format("Team '%s'",uiString.str()); break;
 case Rva00352E80Type55: uiText.format("TeamRef '%s'",uiString.str()); break;
 case UNIT: uiText.format("Unit '%s'",uiString.str()); break;
 case Rva00352E80Type54: uiText.format("UnitRef '%s'",uiString.str()); break;
 case BRIDGE: uiText.format("Bridge '%s'",uiString.str()); break;
 case ANGLE: uiText.format("%.2f degrees",m_real*180/PI); break;
 case PERCENT: uiText.format("%.2f%%",m_real*100.0f); break;
 case COORD3D:
  reinterpret_cast<const BfmeThingYG *>(this)->bfmeReadYG(reinterpret_cast<BfmeVecYG *>(&pos));
  uiText.format("(%.2f,%.2f,%.2f)",pos.x,pos.y,pos.z); break;
 case Rva00352E80Type61:
 case Rva00352E80Type62:
 case OBJECT_TYPE: uiText.format("'%s'",uiString.str()); break;
 case KIND_OF_PARAM:
  if(m_int>=0 && m_int<181) uiText.format("Kind is '%s'",KindOfMaskType::getNameFromSingleBit(m_int));
  else uiText.format("Kind is '?^");
  break;
 case SIDE: uiText.format("Player '%s'",uiString.str()); break;
 case COUNTER: uiText.format("'%s'",uiString.str()); break;
 case INT: uiText.format(" %d ",m_int); break;
 case BOOLEAN: uiText.concat(m_int?"TRUE":"FALSE"); break;
 case REAL: uiText.format("%.2f",m_real); break;
 case RELATION: uiText.format("Relation '%s'",uiString.str()); break;
 case FLAG: uiText.format("Flag named '%s'",uiString.str()); break;
 case COMPARISON:
  switch(m_int) {
  case 0: uiText.format("Less Than"); break;
  case 1: uiText.format("Less Than or Equal"); break;
  case 2: uiText.format("Equal To"); break;
  case 3: uiText.format("Greater Than or Equal To"); break;
  case 4: uiText.format("Greater Than"); break;
  case 5: uiText.format("Not Equal To"); break;
  default: break;
  } break;
 case Rva00352E80Type57:
  switch(m_int) {
  case 0: uiText.format("Add"); break;
  case 1: uiText.format("Subtract"); break;
  case 2: uiText.format("Multiply"); break;
  case 3: uiText.format("Divide"); break;
  default: break;
  } break;
 case AI_MOOD:
  switch(m_int) {
  case -3: uiText.format("Peaceful"); break;
  case -2: uiText.format("Sleep"); break;
  case -1: uiText.format("Passive"); break;
  case 0: uiText.format("Normal"); break;
  case 1: uiText.format("Alert"); break;
  case 2: uiText.format("Aggressive"); break;
  default: break;
  } break;
 case Rva00352E80Type56:
  switch(m_int) {
  case 1: uiText.format("far"); break;
  case 0: uiText.format("near"); break;
  default: break;
  } break;
 case Rva00352E80Type29:
  switch(m_int) {
  case 1: uiText.format("Theoden Alert"); break;
  case 0: uiText.format("Gandalf Alert"); break;
  default: break;
  } break;
 case RADAR_EVENT_TYPE:
  switch(m_int) {
  case 0: uiText.format("Information"); break;
  case 1: uiText.format("Construction"); break;
  case 2: uiText.format("Upgrade"); break;
  case 3: uiText.format("Under Attack"); break;
  case 4: uiText.format("Infiltration"); break;
  case 5: uiText.format("Banner"); break;
  default: break;
  } break;
 case DIALOG: uiText.format("'%s'",uiString.str()); break;
 case SKIRMISH_WAYPOINT_PATH: uiText.format("'%s'",uiString.str()); break;
 case COLOR: uiText.format(" R:%d G:%d B:%d ",(m_int&0x00ff0000)>>16,(m_int&0x0000ff00)>>8,(m_int&0x000000ff)); break;
 case MUSIC: uiText.format("'%s'",uiString.str()); break;
 case MOVIE: uiText.format("'%s'",uiString.str()); break;
 case SPECIAL_POWER: uiText.format("Special power '%s'",uiString.str()); break;
 case SCIENCE: uiText.format("Science '%s'",uiString.str()); break;
 case SCIENCE_AVAILABILITY: uiText.format("Science availability '%s'",uiString.str()); break;
 case UPGRADE: uiText.format("Upgrade '%s'",uiString.str()); break;
 case COMMANDBUTTON_ABILITY:
 case COMMANDBUTTON_ALL_ABILITIES: uiText.format("Ability '%s'",uiString.str()); break;
 case EMOTICON: uiText.format("Emoticon '%s'",uiString.str()); break;
 case BOUNDARY: uiText.format("Boundary %s",BORDER_COLORS[m_int % BORDER_COLORS_SIZE].m_colorName); break;
 case BUILDABLE:
  if(m_int>=0 && m_int<4) uiText.format("Buildable (%s)",BuildableStatusNames[m_int]);
  else uiText.format("Buildable (?]");
  break;
 case SURFACES_ALLOWED:
  if(m_int>0 && m_int<=3) uiText.format("Surfaces Allowed: %s",Surfaces[m_int-1]);
  else uiText.format("Surfaces Allowed: ???");
  break;
 case SHAKE_INTENSITY:
  if(m_int>0 && m_int<6) uiText.format("Shake Intensity: %s",ShakeIntensities[m_int]);
  else uiText.format("Shake Intensity: ???");
  break;
 case OBJECT_STATUS:
  if(m_string.isEmpty()) uiText.format("Object Status is '?^");
  else uiText.format("Object Status is '%s'",m_string.str());
  break;
 case FACTION_NAME: uiText.format("Faction Name: %s",uiString.str()); break;
 case Rva00352E80Type53: {
  const char *name="???";
  if(m_int>0 && m_int<=3) name=Rva012B577CNames[m_int-1];
  uiText.format("Spline Path Pad: %s",name); break;
 }
 case OBJECT_TYPE_LIST: uiText.format("'%s'",uiString.str()); break;
 case REVEALNAME: uiText.format("Reveal Name: %s",uiString.str()); break;
 case OBJECT_PANEL_FLAG: uiText.format("Object Flag: %s",uiString.str()); break;
 case Rva00352E80Type58: uiText.format("ModelCondition State: %s",uiString.str()); break;
 case Rva00352E80Type60: uiText.format("Reverb Room Type: %s",uiString.str()); break;
 case Rva00352E80Type63:
  if(m_int>=0 && m_int<10) uiText.format("Emotion: %s",BitFlags<10>::getBitNames()[m_int]);
  else uiText="Emotion: ???";
  break;
 }
 return uiText;
}
