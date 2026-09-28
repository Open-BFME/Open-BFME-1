// cl: /O2 /Ob2 /MD
// Retail INT3-bounded IME message handler at 0048DED0. Field layout agrees
// with the existing IMEManager constructor and composition/candidate methods.
extern "C" {
__declspec(dllimport) void* __stdcall GetKeyboardLayout(unsigned long);
unsigned long __stdcall ImmGetProperty(void*, unsigned long);
__declspec(dllimport) int __stdcall IsWindowUnicode(void*);
__declspec(dllimport) long __stdcall DefWindowProcW(void*,unsigned,int,int);
__declspec(dllimport) long __stdcall DefWindowProcA(void*,unsigned,int,int);
}
class Rva0048CE70 { public: unsigned short decode(unsigned,unsigned); };
class Rva0048CFA0 { public: void getResultsString(); };
class GameWindow;
class GameWindowManager { public:
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
virtual void slot0A();
virtual void slot0B();
virtual void slot0C();
virtual void slot0D();
virtual void slot0E();
virtual void slot0F();
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
virtual void slot1A();
virtual void slot1B();
virtual void slot1C();
virtual void slot1D();
virtual void slot1E();
virtual void slot1F();
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
virtual void slot2A();
virtual void slot2B();
virtual void slot2C();
virtual void slot2D();
virtual void slot2E();
virtual void slot2F();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual unsigned winSendInputMsg(GameWindow*,unsigned,unsigned,unsigned);
};
extern GameWindowManager* TheWindowManager;
class IMEManager { public:
virtual bool serviceIMEMessage(void*,unsigned,int,int);
void updateCompositionString();
void openCandidateList(int);
void updateCandidateList(int);
protected:
void closeCandidateList(int);
unsigned m_pad04;
int m_result;
GameWindow* m_window;
char m_pad10[12];
bool m_composing;
unsigned short m_compositionString[0x801];
unsigned short m_resultsString[0x801];
char m_pad2022[0x1002];
int m_compositionCursorPos;
int m_compositionStringLength;
int m_indexBase;
char m_pad3030[20];
bool m_unicodeIME;
int m_compositionCharsDisplayed;
};
bool IMEManager::serviceIMEMessage(void* window,unsigned message,int wParam,int lParam)
{
 switch(message) {
 case 0x286: {
  unsigned short ch=((Rva0048CE70*)this)->decode(wParam,0);
  if(m_window && (ch>32 || ch==13)) {
   TheWindowManager->winSendInputMsg(m_window,25,wParam&0xffff,lParam);
   m_result=0; return true;
  } return false;
 }
 case 0x102: {
  unsigned short ch=(unsigned short)wParam;
  if(m_window && (ch>=32 || ch==13)) {
   TheWindowManager->winSendInputMsg(m_window,25,ch,lParam);
   m_result=0; return true;
  } return false;
 }
 case 0x285: return false;
 case 0x10d:
  m_composing=true; m_compositionCharsDisplayed=0;
  updateCompositionString(); m_result=1; return true;
 case 0x10e:
  updateCompositionString(); m_composing=false;
  m_compositionCharsDisplayed=0; m_result=1; return true;
 case 0x10f:
  if(lParam&0x800) {
   if(m_window) {
    m_composing=false;
    while(m_compositionCharsDisplayed>0) {
     TheWindowManager->winSendInputMsg(m_window,21,14,2);
     --m_compositionCharsDisplayed;
    }
    unsigned short* ch=m_resultsString;
    ((Rva0048CFA0*)this)->getResultsString();
    while(*ch) { TheWindowManager->winSendInputMsg(m_window,25,*ch,0); ++ch; }
    m_composing=true;
   }
   m_compositionCharsDisplayed=0;
  }
  if(lParam&8) updateCompositionString();
  m_result=1; return true;
 case 0x281: {
  void* layout=GetKeyboardLayout(0);
  unsigned long props=ImmGetProperty(layout,4);
  m_indexBase=(props>>18)&1;
  m_unicodeIME=(props>>19)&1;
  if(IsWindowUnicode(window)) m_result=DefWindowProcW(window,0x281,wParam,lParam&0x7fffffff);
  else m_result=DefWindowProcA(window,0x281,wParam,lParam&0x7fffffff);
  return true;
 }
 case 0x282:
  m_result=1;
  switch(wParam) {
   case 5: openCandidateList(lParam); m_result=1; return true;
   case 4: closeCandidateList(lParam); m_result=1; return true;
   case 3: updateCandidateList(lParam); m_result=1; return true;
   case 1: return true;
case 2: return true;
case 6: return true;
case 7: return true;
case 8: return true;
case 9: return true;
case 10: return true;
case 11: return true;
case 12: return true;
   case 14: if(lParam==23) return false; return true;
   default: m_result=1; return true;
  }
 case 0x284: m_result=1; return true;
 }
 return false;
}

