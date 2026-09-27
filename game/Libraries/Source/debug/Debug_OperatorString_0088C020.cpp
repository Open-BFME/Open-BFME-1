// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::operator<<(const char *) (0x0088C020): Debug vtable 0x01133058
// slot 14, the slot every string insertion in the debug library calls
// through.  Zero Hour twin: debug_debug.cpp.  BFME keeps the forced width
// signed (+0x9F44) and the fill character at +0x9F48.

#include <string.h>

class Debug
{
public:
    virtual void pad00(void);
    virtual void pad01(void);
    virtual void pad02(void);
    virtual void pad03(void);
    virtual void pad04(void);
    virtual void pad05(void);
    virtual void pad06(void);
    virtual void pad07(void);
    virtual void pad08(void);
    virtual void pad09(void);
    virtual void pad10(void);
    virtual void pad11(void);
    virtual void pad12(void);
    virtual void pad13(void);
    virtual Debug &operator<<(const char *str);

private:
    unsigned char m_pad04[0x9CF0];
    int curType;
    unsigned char m_pad9CF8[0x24C];
    int m_width;
    char m_fillChar;

    void AddOutput(const char *str, unsigned len);
};

// ??6Debug@@UAEAAV0@PBD@Z
Debug& Debug::operator<<(const char *str)
{
  if (curType==7)
    // yes, this is valid and simply means not to
    // write anything...
    return *this;

  // buffer large enough?
  if (!str)
    str="[NULL]";
  else if (!*str)
    return *this;

  int len=strlen(str);

  // forced width?
  if (len<m_width)
  {
    for (int k=len;k<m_width;k++)
      AddOutput(&m_fillChar,1);
  }

  // reset width after each insertion
  m_width=0;

  AddOutput(str,len);

  return *this;
}
