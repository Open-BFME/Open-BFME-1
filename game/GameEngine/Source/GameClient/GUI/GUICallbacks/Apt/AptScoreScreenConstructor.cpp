// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
// Retail00578160..00578C94: complete ScoreScreen constructor.
// Identity/layout/ABI evidence: targets/game/reverse/identity_evidence/00578160-score-screen-constructor.md

#include "ascii_string.h"
#include <vector>
struct Gen00574BC0 {
  int field00;
  AsciiString field04;
};
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

class GameWindow;
class __multiple_inheritance BfmeAptScreenScoreScreen;
class __multiple_inheritance FunctorTarget;
// The seven plain callbacks consume one32-bit argument (RET4). Their
// address-derived names assert only the witnessed screen binding and ABI.
// Provider PMF casts below normalize equivalent three-word callback payloads;
// this constructor stores them and does not invoke them through the cast type.
typedef void (BfmeAptScreenScoreScreen::*FunctorMethod)(const char *);

// VC7.1 aligns each eight-byte PMF at+8; +4 is unwritten native padding.
struct FunctorBinding {
  FunctorBinding(FunctorMethod method, FunctorTarget *target)
      : m_target(target), m_method(method) {}

  FunctorTarget *m_target;
  FunctorMethod m_method;
};

typedef char CheckBindingSize[sizeof(FunctorBinding) == 16 ? 1 : -1];

class Rva00572CA0FunctorHolder {
public:
  Rva00572CA0FunctorHolder(FunctorBinding binding);
  Rva00572CA0FunctorHolder(const Rva00572CA0FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++*(unsigned *)((char *)m_ptr + 4);
  }
  ~Rva00572CA0FunctorHolder();

private:
  void *m_ptr;
};

class Rva00578160Primary {
public:
  virtual ~Rva00578160Primary();
  char field04[0x214];
};
class __declspec(novtable) Rva00465200GameWindow {
public:
  Rva00465200GameWindow() {}
  virtual ~Rva00465200GameWindow();
  char field04[0x3c];
};
class _bfme_AptGameWindow : public Rva00578160Primary,
                            public Rva00465200GameWindow {
public:
  _bfme_AptGameWindow(void *);
  virtual ~_bfme_AptGameWindow();
};

struct Rva00578160Fields278 {
  int m_slot278;
  int m_slot27c;
  int m_slot280;
  int m_slot284;
  int m_slot288;
};

struct Rva00578160Fields294 {
  int m_slots294[21];
};

class FunctorWrapperHead {
public:
  FunctorWrapperHead() : m_refCount(0) {}
  virtual void functorWrapperAnchor();
  unsigned m_refCount;
};
typedef void (BfmeAptScreenScoreScreen::*ProviderMethod)(int, char *, bool);
typedef void (BfmeAptScreenScoreScreen::*InitMethod)(const char *, void *,
                                                     GameWindow *);
struct ProviderBinding {
  ProviderBinding(ProviderMethod method, FunctorTarget *target)
      : m_target(target), m_method(method) {}
  FunctorTarget *m_target;
  ProviderMethod m_method;
};
struct InitBinding {
  InitBinding(InitMethod method, FunctorTarget *target)
      : m_target(target), m_method(method) {}
  FunctorTarget *m_target;
  InitMethod m_method;
};
// The independent49-byte wrapper constructors install VA0110A964/0110A970.
class Rva00571780FunctorWrapper : public FunctorWrapperHead {
public:
  Rva00571780FunctorWrapper(const ProviderBinding &b) : m_binding(b) {}
  ProviderBinding m_binding;
};
class Rva005717D0FunctorWrapper : public FunctorWrapperHead {
public:
  Rva005717D0FunctorWrapper(const InitBinding &b) : m_binding(b) {}
  InitBinding m_binding;
};
class Rva00572D10FunctorHolder {
public:
  __forceinline Rva00572D10FunctorHolder(ProviderBinding binding) {
    m_ptr = new Rva00571780FunctorWrapper(binding);
    if (m_ptr)
      ++m_ptr->m_refCount;
  }
  Rva00572D10FunctorHolder(const Rva00572D10FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++m_ptr->m_refCount;
  }
  ~Rva00572D10FunctorHolder();

private:
  Rva00571780FunctorWrapper *m_ptr;
};
class Rva00572D80FunctorHolder {
public:
  __forceinline Rva00572D80FunctorHolder(InitBinding binding) {
    m_ptr = new Rva005717D0FunctorWrapper(binding);
    if (m_ptr)
      ++m_ptr->m_refCount;
  }
  Rva00572D80FunctorHolder(const Rva00572D80FunctorHolder &s) throw()
      : m_ptr(s.m_ptr) {
    if (m_ptr)
      ++m_ptr->m_refCount;
  }
  ~Rva00572D80FunctorHolder();

private:
  Rva005717D0FunctorWrapper *m_ptr;
};
extern void j_000338ed();
extern void j_0000acfe();
extern void j_0003df14();
class Rva00464ED0RegistryView {
public:
  typedef void (Rva00464ED0RegistryView::*Plain)(const AsciiString &,
                                                 Rva00572CA0FunctorHolder);
  typedef void (Rva00464ED0RegistryView::*Arg)(const AsciiString &, void *,
                                               Rva00572D10FunctorHolder);
  static __forceinline Plain plain() {
    union {
      void (*raw)();
      Plain p;
    } f;
    f.raw = j_000338ed;
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
typedef void (*RefCall)(const AsciiString &, Rva00572D80FunctorHolder);
class WindowManager {
public:
  __declspec(noinline) void bfme_showBackground(int kind);
};

extern WindowManager *g_rva012F19E8WindowManager;
extern const char *Rva012B7F9CNames[11];
BfmeAptScreenScoreScreen *Rva012F4B50ScoreScreen = 0;

class BfmeAptScreenScoreScreen : public _bfme_AptGameWindow {
public:
  BfmeAptScreenScoreScreen(void *context);
  virtual ~BfmeAptScreenScoreScreen();
  void rva005731E0(int, char *, bool);
  void _bfme_getPlayerColor(int, char *, bool);
  void _bfme_getPlayerFaction(int, char *, bool);
  void rva00570260(int, char *, bool);
  void bfmeProvide(const char *, void *, bool);
  void rva00570300(int, char *, bool);
  void bfmeProvideObjectiveChecked(const char *, void *, bool);
  void heroVetUpgrade(int, char *, bool);
  void _bfme_onInitGadget(const char *, void *, GameWindow *);

  void rva005701D0(const char *);
  void rva005731C0(const char *);
  void rva00570200(const char *);
  void rva005780E0(const char *);
  void rva005731D0(const char *);
  void _bfme_renameAccept(const char *);
  void rva00570220(const char *);

private:
  int m_slot258;
  int field25c;
  unsigned char m_flag260;
  unsigned char m_flag261;
  char m_pad262[2];
  _STL::vector<Gen00574BC0> m_rows;
  char m_pad270[8];
  Rva00578160Fields278 m_opaque278;
  int m_slot28c;
  char m_pad290[4];
  Rva00578160Fields294 m_zero294;
  _STL::vector<bool> field2e8;
  int m_slot2fc;
  AsciiString m_s300;
  int m_slot304;
  bool field308[8];
  int m_slot310;
  int m_slot314;
  int m_slot318;
  int m_slot31c;
  AsciiString m_s320;
  int m_slot324;
  int m_slot328;
  int m_slot32c;
  AsciiString m_s330;
};

typedef char CheckAptBaseSize[sizeof(_bfme_AptGameWindow) == 0x258 ? 1 : -1];
typedef char CheckScoreSize[sizeof(BfmeAptScreenScoreScreen) == 0x334 ? 1 : -1];
typedef char CheckProviderBinding[sizeof(ProviderBinding) == 16 ? 1 : -1];
typedef char CheckInitBinding[sizeof(InitBinding) == 16 ? 1 : -1];
typedef char
    CheckProviderWrapper[sizeof(Rva00571780FunctorWrapper) == 24 ? 1 : -1];
typedef char CheckInitWrapper[sizeof(Rva005717D0FunctorWrapper) == 24 ? 1 : -1];

static __forceinline void registerPlain(BfmeAptScreenScoreScreen *screen,
                                        Rva00464ED0RegistryView *registry,
                                        const char *label,
                                        FunctorMethod method) {
  AsciiString key(label);
  (registry->*Rva00464ED0RegistryView::plain())(
      key, Rva00572CA0FunctorHolder(
               FunctorBinding(method, (FunctorTarget *)screen)));
}

static __forceinline void registerArg(BfmeAptScreenScoreScreen *screen,
                                      Rva00464ED0RegistryView *registry,
                                      const char *label, void *value,
                                      ProviderMethod method) {
  AsciiString key(label);
  (registry->*Rva00464ED0RegistryView::arg())(
      key, value,
      Rva00572D10FunctorHolder(
          ProviderBinding(method, (FunctorTarget *)screen)));
}
static __forceinline void registerRef(BfmeAptScreenScoreScreen *screen,
                                      const char *label, InitMethod method) {
  AsciiString key(label);
  ((RefCall)j_0003df14)(key, Rva00572D80FunctorHolder(
                                 InitBinding(method, (FunctorTarget *)screen)));
}
BfmeAptScreenScoreScreen::BfmeAptScreenScoreScreen(void *context)
    : _bfme_AptGameWindow(context), m_slot258(0), field25c(5), m_flag260(0),
      m_flag261(0), m_rows(), m_slot28c(0), field2e8(), m_slot2fc(0), m_s300(),
      m_slot304(0), m_slot310(0), m_slot314(0), m_slot318(0), m_slot31c(-1),
      m_s320(), m_slot324(0), m_slot328(0), m_slot32c(0), m_s330("APT:NULL") {
  if (Rva012F4B50ScoreScreen == 0) {
    Rva012F4B50ScoreScreen = this;
    memset(&m_opaque278, 0, sizeof(m_opaque278));
    memset(m_zero294.m_slots294, 0, sizeof(m_zero294.m_slots294));
    memset(field308, 0, sizeof(field308));

    Rva00464ED0RegistryView *registry =
        (Rva00464ED0RegistryView *)((char *)this + 0x218);

    registerPlain(this, registry, "AptScoreScreen::OnInitialized",
                  &BfmeAptScreenScoreScreen::rva005701D0);
    registerPlain(this, registry, "AptScoreScreen::Exit",
                  &BfmeAptScreenScoreScreen::rva005731C0);
    registerPlain(this, registry, "AptScoreScreen::Save",
                  &BfmeAptScreenScoreScreen::rva00570200);
    registerPlain(this, registry, "AptScoreScreen::Continue",
                  &BfmeAptScreenScoreScreen::rva005780E0);
    registerPlain(this, registry, "AptScoreScreen::RestartGame",
                  &BfmeAptScreenScoreScreen::rva005731D0);
    registerPlain(this, registry, "AptScoreScreen::RenameAccept",
                  &BfmeAptScreenScoreScreen::_bfme_renameAccept);
    registerPlain(this, registry, "AptScoreScreen::RenameCancel",
                  &BfmeAptScreenScoreScreen::rva00570220);

    ProviderMethod provider = reinterpret_cast<ProviderMethod>(
        &BfmeAptScreenScoreScreen::rva005731E0);
    for (int index = 0; index < 11; ++index) {
      AsciiString name(Rva012B7F9CNames[index]);
      (registry->*Rva00464ED0RegistryView::arg())(
          name, (void *)index,
          Rva00572D10FunctorHolder(
              ProviderBinding(provider, (FunctorTarget *)this)));
    }

    AsciiString playerName;
    int playerIndex = 0;
    ProviderBinding playerColor(&BfmeAptScreenScoreScreen::_bfme_getPlayerColor,
                                (FunctorTarget *)this);
    ProviderBinding playerFaction(
        &BfmeAptScreenScoreScreen::_bfme_getPlayerFaction,
        (FunctorTarget *)this);
    for (; playerIndex < 8; ++playerIndex) {
      playerName.format((AsciiString) "ScoreScreen:PlayerColor:%d",
                        playerIndex);
      (registry->*Rva00464ED0RegistryView::arg())(
          playerName, (void *)playerIndex,
          Rva00572D10FunctorHolder(playerColor));
      playerName.format((AsciiString) "ScoreScreen:PlayerFaction:%d",
                        playerIndex);
      (registry->*Rva00464ED0RegistryView::arg())(
          playerName, (void *)playerIndex,
          Rva00572D10FunctorHolder(playerFaction));
      if (playerIndex != 0) {
        playerName.format((AsciiString) "Separator%d", playerIndex);
        (registry->*Rva00464ED0RegistryView::arg())(
            playerName, (void *)playerIndex,
            Rva00572D10FunctorHolder(
                ProviderBinding(reinterpret_cast<ProviderMethod>(
                                    &BfmeAptScreenScoreScreen::rva00570260),
                                (FunctorTarget *)this)));
      }
    }

    registerArg(this, registry, "ScoreBattleStat", (void *)0,
                reinterpret_cast<ProviderMethod>(
                    &BfmeAptScreenScoreScreen::bfmeProvide));
    registerArg(this, registry, "ScoreBonusObjectives", (void *)1,
                reinterpret_cast<ProviderMethod>(
                    &BfmeAptScreenScoreScreen::bfmeProvide));
    registerArg(this, registry, "ScoreHeroVeterancy", (void *)2,
                reinterpret_cast<ProviderMethod>(
                    &BfmeAptScreenScoreScreen::bfmeProvide));
    registerArg(this, registry, "ScoreUnitVeterancy", (void *)3,
                reinterpret_cast<ProviderMethod>(
                    &BfmeAptScreenScoreScreen::bfmeProvide));
    registerArg(this, registry, "ScoreTerritoryBonus", (void *)4,
                reinterpret_cast<ProviderMethod>(
                    &BfmeAptScreenScoreScreen::bfmeProvide));

    provider = reinterpret_cast<ProviderMethod>(
        &BfmeAptScreenScoreScreen::rva00570300);
    for (int group = 0; group < 7; ++group) {
      for (int stat = 0; stat < 3; ++stat) {
        playerName.format((AsciiString) "battleStat%c%d", 'A' + group,
                          stat + 1);
        (registry->*Rva00464ED0RegistryView::arg())(
            playerName, (void *)(group * 3 + stat),
            Rva00572D10FunctorHolder(
                ProviderBinding(provider, (FunctorTarget *)this)));
      }
    }

    playerIndex = 0;
    provider = reinterpret_cast<ProviderMethod>(
        &BfmeAptScreenScoreScreen::bfmeProvideObjectiveChecked);
    for (; playerIndex < 8; ++playerIndex) {
      playerName.format((AsciiString) "objectiveChecked%d", playerIndex + 1);
      (registry->*Rva00464ED0RegistryView::arg())(
          playerName, (void *)playerIndex,
          Rva00572D10FunctorHolder(
              ProviderBinding(provider, (FunctorTarget *)this)));
    }

    provider = reinterpret_cast<ProviderMethod>(
        &BfmeAptScreenScoreScreen::heroVetUpgrade);
    playerIndex = 0;
    for (; playerIndex < 12; ++playerIndex) {
      playerName.format((AsciiString) "heroVetUpgrade%d", playerIndex + 1);
      (registry->*Rva00464ED0RegistryView::arg())(
          playerName, (void *)playerIndex,
          Rva00572D10FunctorHolder(
              ProviderBinding(provider, (FunctorTarget *)this)));
    }

    registerRef(this, "AptScoreScreen::InitGadgets",
                &BfmeAptScreenScoreScreen::_bfme_onInitGadget);
    g_rva012F19E8WindowManager->bfme_showBackground(1);
  }
}
