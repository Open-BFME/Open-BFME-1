// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail RVA 004C1B60 /156. Named UI callers establish the ControlBar
// receiver (the BfmeConv1022 caller loads VA012F33F8/TheControlBar); the method and temporary adapter retain address-derived names.
// The adapter installs vtable VA10FD964 with six slots. Its base table
// VA10EDAA0 contains a scalar destructor followed by five pure virtuals.
// Existing PartitionFilterPossibleToAttack labels on this table do not prove
// this UI adapter identity and are deliberately not used here.
// EH cleanupC290E0 reaches base destructor4C1150 installing10EDAA0.
class GameWindow { public: unsigned winGetStyle(); };
void *GadgetButtonGetData(GameWindow *);
struct BfmeMsgDN;
// The non-destructor slots are placeholders in this partial ABI view. This
// TU never calls them; their retail targets are 4C1AE0, 4C1160, 4C1C30,
// 4C1180 and 4C1240, in order. No semantic method identities are claimed.
class Rva004C1150AdapterBase {
public:
 virtual ~Rva004C1150AdapterBase() {}
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
};
class ControlBar;
class Rva004C1B60Adapter:public Rva004C1150AdapterBase {
public:
 Rva004C1B60Adapter(ControlBar *owner,GameWindow *window,void *data)
  :m_owner(owner),m_window(window),m_data(data) {}
 virtual ~Rva004C1B60Adapter() {}
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 ControlBar *m_owner;GameWindow *m_window;void *m_data;
};
class ControlBar {
public:
 void rva004C1B60(GameWindow *,void *);
 void bfmeShowDN(BfmeMsgDN *);
};
void ControlBar::rva004C1B60(GameWindow *window,void *data)
{
 if(!data) {
  if(!window) return;
  if(window->winGetStyle()&1) {
   data=GadgetButtonGetData(window);
   if(!data) return;
  } else if(!(window->winGetStyle()&0x200) && !(window->winGetStyle()&0x80)) return;
 }
 Rva004C1B60Adapter adapter(this,window,data);
 bfmeShowDN((BfmeMsgDN *)&adapter);
}
