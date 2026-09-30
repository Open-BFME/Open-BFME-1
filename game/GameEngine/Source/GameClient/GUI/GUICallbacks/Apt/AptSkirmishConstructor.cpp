// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "unicode_string.h"
template <> inline const char *StringBase<char>::str() const {
  return m_data ? m_data->data : "";
}
template <>
inline const unsigned short *StringBase<unsigned short>::str() const {
  return m_data ? m_data->data : L"";
}
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const wchar_t *s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::StringBase(
          *(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString() {
  ((StringBase<unsigned short> *)this)
      ->StringBase<unsigned short>::~StringBase();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
  ((StringBase<unsigned short> *)this)
      ->set(*(const StringBase<unsigned short> *)&s);
  return *this;
}
extern const UnicodeString BFMEUnicodeEmptyString;
#pragma comment(                                                               \
    linker,                                                                    \
    "/alternatename:?BFMEUnicodeEmptyString@@3VUnicodeString@@B=?TheEmptyString@UnicodeString@@2V1@B")

template <>
int StringBase<unsigned short>::compare(
    const StringBase<unsigned short> &) const throw();
extern void j_00010924();
extern void j_00047767();
extern void j_00049bc0();
extern void j_000338ed();
extern void j_0000acfe();
extern void j_0003df14();
extern void j_0000f31c();
extern void j_00014c4a();
extern void j_0004711d();
extern void j_00035e13();
extern void j_000394f5();
extern void j_0000a155();
extern void j_00018e3a();
extern void j_0000a655();
extern void j_00021e4f();
extern void j_0003ffda();
extern void j_0001ebb9();
extern void j_0002aced();
extern void j_0000f074();
extern void j_000095ac();
class __multiple_inheritance BfmeAptScreenSkirmish;
class __multiple_inheritance FunctorTarget;
// Storage-only PMF representation; callbacks are not invoked through this type.
// In particular ILT00010924 takes three stack arguments (RET12).
typedef void (BfmeAptScreenSkirmish::*FunctorMethod)();
struct FunctorBinding {
  FunctorBinding(FunctorMethod method, FunctorTarget *target)
      : m_target(target), m_method(method) {}
  FunctorTarget *m_target;
  unsigned field04;
  FunctorMethod m_method;
};
class Rva0057C970FunctorHolder {
public:
  Rva0057C970FunctorHolder(FunctorBinding);
  Rva0057C970FunctorHolder(const Rva0057C970FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++*(unsigned *)((char *)m_ptr + 4);
  }
  ~Rva0057C970FunctorHolder();

private:
  void *m_ptr;
};
class Rva0057C9E0FunctorHolder {
public:
  Rva0057C9E0FunctorHolder(FunctorBinding);
  Rva0057C9E0FunctorHolder(const Rva0057C9E0FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++*(unsigned *)((char *)m_ptr + 4);
  }
  ~Rva0057C9E0FunctorHolder();

private:
  void *m_ptr;
};
class Rva0057CA50FunctorHolder {
public:
  Rva0057CA50FunctorHolder(FunctorBinding);
  Rva0057CA50FunctorHolder(const Rva0057CA50FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++*(unsigned *)((char *)m_ptr + 4);
  }
  ~Rva0057CA50FunctorHolder();

private:
  void *m_ptr;
};
class Rva0057DA50Primary {
public:
  virtual ~Rva0057DA50Primary();
  char field04[0x214];
};
class __declspec(novtable) Rva00465200GameWindow {
public:
  Rva00465200GameWindow() {}
  virtual ~Rva00465200GameWindow();
  char field04[0x3c];
};
class _bfme_AptGameWindow : public Rva0057DA50Primary,
                            public Rva00465200GameWindow {
public:
  _bfme_AptGameWindow(void *);
  virtual ~_bfme_AptGameWindow();
};
class Gen00529110Owner {
public:
  Gen00529110Owner() {}
  virtual ~Gen00529110Owner();
  virtual void slot00();
};
class SkirmishScreenState {
public:
  SkirmishScreenState(Gen00529110Owner *, int);
  ~SkirmishScreenState();
  virtual void slot00();
  char field04[0x128];
};
class __declspec(novtable) Rva00566EC0Profile {
public:
  Rva00566EC0Profile() {
    union {
      void (*raw)();
      void (Rva00566EC0Profile::*member)();
    } f;
    f.raw = j_00049bc0;
    (this->*f.member)();
  }
  virtual ~Rva00566EC0Profile();
  char field04[0x18];
};
class __declspec(novtable) SkirmishPreferences {
public:
  SkirmishPreferences() {
    union {
      void (*raw)();
      void (SkirmishPreferences::*member)();
    } f;
    f.raw = j_00047767;
    (this->*f.member)();
  }
  virtual ~SkirmishPreferences();
  UnicodeString getUserName();
  char field04[0x14];
};
class SkirmishBattleHonors {
public:
  SkirmishBattleHonors(UnicodeString);
  virtual ~SkirmishBattleHonors();
  char field04[0x38];
};
class Rva0057D0C0 {
public:
  Rva0057D0C0 &operator=(const Rva0057D0C0 *);
};
class GenBase00479230 {
public:
  GenBase00479230();
  virtual ~GenBase00479230();
  void *field04;
  void *field08;
};
class Rva011051ECSkirmishField : public GenBase00479230 {
public:
  Rva011051ECSkirmishField(int x) : field0c(x) {}
  virtual ~Rva011051ECSkirmishField();
  int field0c;
};
class BfmeA1024 {
public:
  void bfmeGo1024A(int, int);
};
class WindowManager {
public:
  void bfme_setAptText(const AsciiString &, const UnicodeString &);
  void rva0046c790(const AsciiString &, const AsciiString &);
};
extern WindowManager *g_theWindowManager;
class GameTextInterface {
public:
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
  virtual UnicodeString fetch(const char *, bool * = 0);
};
extern GameTextInterface *TheGameText;
extern BfmeAptScreenSkirmish *Rva012F4B54Skirmish;
extern const char *Rva012B8044Image;
extern const char *Rva012B8048Image;
extern const char *Rva012B804CImage;
extern const char *Rva012B8050Image;
extern const char *Rva012B8054Image;
extern const char *Rva012B8058Image;
extern const char *Rva012B805CImage;
extern const char *Rva012B8060Image;
extern const char *Rva012B8064Image;

class BfmeAptScreenSkirmish : public _bfme_AptGameWindow,
                              public Gen00529110Owner {
public:
  BfmeAptScreenSkirmish(void *);
  virtual ~BfmeAptScreenSkirmish();
  SkirmishScreenState field25c;
  char field388[8];
  Rva00566EC0Profile field390;
  SkirmishPreferences field3ac;
  SkirmishBattleHonors field3c4;
  int field400;
  int field404;
  bool field408;
  bool field409;
  char field40a[2];
  void *field40c;
  void *field410;
  void *field414;
  void *field418;
  void *field41c;
  void *field420;
  Rva011051ECSkirmishField field424;
  bool field434;
  char field435[3];
  UnicodeString field438;
};
static __forceinline FunctorMethod rawMethod(unsigned address) {
  union {
    struct {
      unsigned code;
      int delta;
    } raw;
    FunctorMethod method;
  } f;
  f.raw.code = address;
  f.raw.delta = 0;
  return f.method;
}
class RegistryView {
public:
  typedef void (RegistryView::*Plain)(const AsciiString &,
                                      Rva0057C970FunctorHolder);
  typedef void (RegistryView::*Arg)(const AsciiString &, void *,
                                    Rva0057C9E0FunctorHolder);
  static __forceinline Plain plain() {
    union {
      void (*raw)();
      Plain p;
    } f;
    f.raw = j_000338ed;
    return f.p;
  }
  static __forceinline Plain bind() {
    union {
      void (*raw)();
      Plain p;
    } f;
    f.raw = j_0000f31c;
    return f.p;
  }
  static __forceinline Arg arg() {
    union {
      void (*raw)();
      Arg p;
    } f;
    f.raw = j_0000acfe;
    return f.p;
  }
};
typedef void (*RefCall)(const AsciiString &, Rva0057CA50FunctorHolder);
static __forceinline void registerPlain(BfmeAptScreenSkirmish *screen,
                                        RegistryView *registry,
                                        const char *name,
                                        FunctorMethod method) {
  AsciiString key(name);
  (registry->*RegistryView::plain())(
      key, Rva0057C970FunctorHolder(
               FunctorBinding(method, (FunctorTarget *)screen)));
}
static __forceinline void registerBind(BfmeAptScreenSkirmish *screen,
                                       const char *name, FunctorMethod method) {
  AsciiString key(name);
  (((RegistryView *)g_theWindowManager)->*RegistryView::bind())(
      key, Rva0057C970FunctorHolder(
               FunctorBinding(method, (FunctorTarget *)screen)));
}
static __forceinline void registerArg(BfmeAptScreenSkirmish *screen,
                                      RegistryView *registry, const char *name,
                                      void *arg, FunctorMethod method) {
  AsciiString key(name);
  (registry->*RegistryView::arg())(key, arg,
                                   Rva0057C9E0FunctorHolder(FunctorBinding(
                                       method, (FunctorTarget *)screen)));
}
static __forceinline void registerRef(BfmeAptScreenSkirmish *screen,
                                      const char *name, FunctorMethod method) {
  AsciiString key(name);
  ((RefCall)j_0003df14)(key, Rva0057CA50FunctorHolder(FunctorBinding(
                                 method, (FunctorTarget *)screen)));
}
BfmeAptScreenSkirmish::BfmeAptScreenSkirmish(void *context)
    : _bfme_AptGameWindow(context), field25c(this, 7), field390(), field3ac(),
      field3c4(BFMEUnicodeEmptyString), field400(0), field404(-1),
      field408(true), field409(false), field40c(0), field410(0), field414(0),
      field418(0), field41c(0), field420(0), field424(10), field434(true),
      field438() {
  if (!Rva012F4B54Skirmish) {
    Rva012F4B54Skirmish = this;
    if (field3ac.getUserName().compare(BFMEUnicodeEmptyString) != 0) {
      SkirmishBattleHonors value(field3ac.getUserName());
      *(Rva0057D0C0 *)&field3c4 = (const Rva0057D0C0 *)&value;
    }
    {
      AsciiString icon("AptGondorImage");
      AsciiString key(Rva012B8044Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("AptRohanImage");
      AsciiString key(Rva012B8048Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("AptIsengardImage");
      AsciiString key(Rva012B804CImage);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("AptMordorImage");
      AsciiString key(Rva012B8050Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("ScrollShroud");
      AsciiString key(Rva012B8054Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("ScrollShroud");
      AsciiString key(Rva012B8058Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("ScrollShroud");
      AsciiString key(Rva012B805CImage);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("ScrollShroud");
      AsciiString key(Rva012B8060Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    {
      AsciiString icon("ScrollShroud");
      AsciiString key(Rva012B8064Image);
      ((BfmeA1024 *)g_theWindowManager)->bfmeGo1024A((int)&key, (int)&icon);
    }
    RegistryView *registry = (RegistryView *)(Rva00465200GameWindow *)this;
    registerPlain(this, registry, "AptSkirmish::OnInitialized",
                  rawMethod((unsigned)j_00014c4a));
    registerPlain(this, registry, "AptSkirmish::OnClosed", rawMethod((unsigned)j_0004711d));
    registerPlain(this, registry, "AptSkirmish::Exit", rawMethod((unsigned)j_00035e13));
    registerPlain(this, registry, "AptSkirmish::Back", rawMethod((unsigned)j_000394f5));
    registerPlain(this, registry, "AptSkirmish::StartGame",
                  rawMethod((unsigned)j_0000a155));
    registerPlain(this, registry, "AptSkirmish::Profile", rawMethod((unsigned)j_00018e3a));
    registerPlain(this, registry, "AptSkirmish::SkirmishProfile",
                  rawMethod((unsigned)j_0000a655));
    registerPlain(this, registry, "AptSkirmish::Skirmish::PersonaCancel",
                  rawMethod((unsigned)j_00021e4f));
    registerPlain(this, registry, "AptSkirmish::Skirmish::PersonaAccept",
                  rawMethod((unsigned)j_0003ffda));
    registerPlain(this, registry, "AptSkirmish::Skirmish::PersonaRemove",
                  rawMethod((unsigned)j_0001ebb9));
    registerPlain(this, registry, "AptSkirmish::Skirmish::PersonaOk",
                  rawMethod((unsigned)j_0002aced));
    registerBind(this, "Skirmish/tooltipPlayerLevelIcon", rawMethod((unsigned)j_0000f074));
    registerArg(this, registry, "LevelBarCurrent", (void *)0,
                rawMethod((unsigned)j_00010924));
    registerArg(this, registry, "LevelBarA", (void *)1,
                rawMethod((unsigned)j_00010924));
    registerArg(this, registry, "LevelBarB", (void *)2,
                rawMethod((unsigned)j_00010924));
    registerArg(this, registry, "LevelBarC", (void *)3,
                rawMethod((unsigned)j_00010924));
    registerArg(this, registry, "LevelBarD", (void *)4,
                rawMethod((unsigned)j_00010924));
    registerRef(this, "AptSkirmish::InitGadgets", rawMethod((unsigned)j_000095ac));
    {
      AsciiString key("APT:OnlineOrNetwork");
      g_theWindowManager->bfme_setAptText(key,
                                          TheGameText->fetch("APT:Skirmish"));
    }
  }
}
