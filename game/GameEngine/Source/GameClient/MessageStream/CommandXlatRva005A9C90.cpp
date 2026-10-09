// cl: /DNDEBUG /MD
// stlport
typedef int Int;
typedef bool Bool;

struct ICoord2D {
  Int x;
  Int y;
};
struct IRegion2D {
  ICoord2D lo;
  ICoord2D hi;
  Int width() const { return hi.x - lo.x; }
  Int height() const { return hi.y - lo.y; }
};

union GameMessageArgumentType {
  Int integer;
  ICoord2D pixel;
  IRegion2D pixelRegion;
};

class GameMessage {
public:
  const GameMessageArgumentType *getArgument(Int argIndex) const;
};

class Object;
class Drawable;

class InGameUI {
public:
  unsigned char m_pad000[0x12b1];
  Bool m_forceAttackMode; ///< +0x12B1
  Bool isInForceAttackMode() const { return m_forceAttackMode; }
};
extern InGameUI *TheInGameUI;

class View {
public:
  virtual void rva005A9C90ViewSlot00();
  virtual void rva005A9C90ViewSlot04();
  virtual void rva005A9C90ViewSlot08();
  virtual void rva005A9C90ViewSlot0C();
  virtual void rva005A9C90ViewSlot10();
  virtual void rva005A9C90ViewSlot14();
  virtual void rva005A9C90ViewSlot18();
  virtual void rva005A9C90ViewSlot1C();
  virtual void rva005A9C90ViewSlot20();
  virtual Drawable *pickDrawable(const ICoord2D *screen, Bool forceAttack,
                                 Int pickType); ///< +0x24
};
extern View *TheTacticalView;

class ContainModuleInterface {
public:
  virtual void rva005A9C90ContainSlot00();
  virtual void rva005A9C90ContainSlot04();
  virtual void rva005A9C90ContainSlot08();
  virtual void rva005A9C90ContainSlot0C();
  virtual void rva005A9C90ContainSlot10();
  virtual void rva005A9C90ContainSlot14();
  virtual void rva005A9C90ContainSlot18();
  virtual void rva005A9C90ContainSlot1C();
  virtual void rva005A9C90ContainSlot20();
  virtual void rva005A9C90ContainSlot24();
  virtual void rva005A9C90ContainSlot28();
  virtual void rva005A9C90ContainSlot2C();
  virtual void rva005A9C90ContainSlot30();
  virtual void rva005A9C90ContainSlot34();
  virtual void rva005A9C90ContainSlot38();
  virtual void rva005A9C90ContainSlot3C();
  virtual void rva005A9C90ContainSlot40();
  virtual void rva005A9C90ContainSlot44();
  virtual void rva005A9C90ContainSlot48();
  virtual void rva005A9C90ContainSlot4C();
  virtual void rva005A9C90ContainSlot50();
  virtual void rva005A9C90ContainSlot54();
  virtual void rva005A9C90ContainSlot58();
  virtual void rva005A9C90ContainSlot5C();
  virtual void rva005A9C90ContainSlot60();
  virtual void rva005A9C90ContainSlot64();
  virtual void *rva005A9C90ContainSlot68(); ///< +0x68
};

#define OBJECT_TU_MEMBERS Bool testStatus(Int status) const;
#include "../../GameLogic/Object/object.h"

class Drawable {
public:
  unsigned char m_pad000[0xfc];
  Object *m_object; ///< +0xFC
  Object *getObject() const { return m_object; }
};

#include "../../Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

class ControlBar {
public:
  Int objectSelectPredicate(Object *obj);
};
extern ControlBar *TheControlBar;

class CommandTranslator {
private:
  void rva005A9C90(const GameMessage *msg);
};

// ?rva005A9C90@CommandTranslator@@AAEXPBVGameMessage@@@Z
// Open BFME 2: Code/GameEngine/Source/GameClient/MessageStream/CommandXlatTargetProbe.cpp.
void CommandTranslator::rva005A9C90(const GameMessage *msg) {
  if (TheInGameUI->isInForceAttackMode()) return;
  const IRegion2D &r = msg->getArgument(0)->pixelRegion;
  if (r.height() != 0 || r.width() != 0) return;
  Drawable *draw = TheTacticalView->pickDrawable(&r.lo, false, 4);
  if (!draw) return;
  Object *obj = draw->getObject();
  if (!obj) return;
  if (obj->testStatus(0x25)) {
    Object *container = obj->m_containedBy;
    if (!container) {
      container = TheGameLogic->findObjectByID(obj->m_producerID);
      if (!container) return;
    }
    ContainModuleInterface *contain = container->m_contain;
    void *accepts = contain ? contain->rva005A9C90ContainSlot68() : 0;
    if (!accepts) return;
    obj = container;
  }
  TheControlBar->objectSelectPredicate(obj);
}
