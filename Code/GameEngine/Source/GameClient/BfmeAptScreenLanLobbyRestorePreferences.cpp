// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x005195B0, full805 bytes. The named LAN lobby constructor519F90
// and destructor5199A0 both reach this body through ILT1D9CB. The descriptive
// method name is recovered; its original spelling is not known.
// A fresh LANPreferences reload supplies six keys. The current UserName is
// kept when nonempty. This TU views only the member at screen+390 and its
// three-dword map at+394; it does not emit another screen or preference table.
#include <cstring>
#pragma intrinsic(memcmp)
class AsciiString;
template<class T> struct StringData { int refs;unsigned short length,capacity;T text[1]; };
template<class T> class StringBase
{
 friend class AsciiString;
 StringBase():m_data(0){}
 StringBase(const T *);
 StringBase(const StringBase &);
 ~StringBase();
 void set(const StringBase &);
 StringData<T> *m_data;
};
class AsciiString:private StringBase<char>
{
public:
 AsciiString(const char *s):StringBase<char>(s){}
 AsciiString(const AsciiString &s):StringBase<char>(s){}
 ~AsciiString(){}
 void set(const AsciiString &other) { StringBase<char>::set(other); }
 // Inline shape of the recovered StringBase<char>::compare(const char*)
 // in Libraries/Source/WWVegas/WWLib/string_base.cpp. A null source has
 // length zero; the intrinsic comparison receives the original zero bound.
 int compare(const char *other) const
 {
  int otherLength=other?(int)strlen(other):0;
  int length=m_data?m_data->length:0;
  const char *source=m_data?(const char *)m_data+8:(const char *)0x0107388B;
  int n=length<otherLength?length:otherLength;
  int result=memcmp(source,other,n);
  if(result==0)result=length-otherLength;
  return result;
 }
};
// The shared map-index route consumes a const AsciiString reference and
// returns the stored AsciiString by reference. Its receiver is the map base,
// four bytes after the preference object, including on the local copy.
extern void j_0003e6da();
class __single_inheritance LanPreferenceMap
{
public:
 typedef AsciiString &(LanPreferenceMap::*Index)(const AsciiString &);
 AsciiString &operator[](const AsciiString &key)
 {
  union Bits {Index member;void(*code)();} bits;bits.code=j_0003e6da;
  return (this->*bits.member)(key);
 }
private:
 char m_data[12];
};
class LANPreferences
{
public:
 LANPreferences();
 virtual ~LANPreferences();
 LanPreferenceMap m_values;
 void *m_filename;
};
class BfmeAptScreenLanLobby
{
public:
 void restorePreferencesRva005195B0();
private:
 char m_before[0x390];
 LANPreferences m_preferences;
};
void BfmeAptScreenLanLobby::restorePreferencesRva005195B0()
{
 // Explicit key lifetimes preserve right-hand lookup before left-hand
 // lookup and assignment, including the two distinct temporary keys.
 LANPreferences saved;
 {
  AsciiString sourceKey("PlayerTemplate");
  AsciiString destinationKey("PlayerTemplate");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
 {
  AsciiString sourceKey("Color");
  AsciiString destinationKey("Color");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
 {
  AsciiString sourceKey("Map");
  AsciiString destinationKey("Map");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
 if(m_preferences.m_values["UserName"].compare((const char *)0)==0)
  {
  AsciiString sourceKey("UserName");
  AsciiString destinationKey("UserName");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
 {
  AsciiString sourceKey("StartingSupplies");
  AsciiString destinationKey("StartingSupplies");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
 {
  AsciiString sourceKey("NumRemoteIPs");
  AsciiString destinationKey("NumRemoteIPs");
  AsciiString &value=saved.m_values[sourceKey];
  m_preferences.m_values[destinationKey].set(value);
 }
}

typedef char LanPreferencesSize[(sizeof(LANPreferences)==0x14)?1:-1];
