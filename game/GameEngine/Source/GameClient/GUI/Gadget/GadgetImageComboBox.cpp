// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail FunctionLexicon RVA 0x00EA9474 pairs GadgetImageComboBoxSystem
// with ILT RVA 0x000199AC -> body RVA 0x004B6190. See astra_Q/listbox.identity.txt.
class AsciiString;
// The ZH header lacks retail's (AsciiString,int) constructor and uses a
// different lifetime/layout. Retail constructor 0x000B2CC0 and destructor
// 0x000B31F0 use a 0x70-byte object (also witnessed by the caller frame).
class AudioEventRTS {
public:
    AudioEventRTS(const AsciiString&,int);
    ~AudioEventRTS();
private:
    unsigned char m_rva000B2CC0[0x70];
};

#define _H_AUDIOEVENTRTS_ // use the retail int-parameter lifetime declaration below
#include "PreRTS.h"
#include "Common/GameAudio.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetListBox.h"
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString& other)
{
    ((StringBase<WideChar>*)this)->StringBase<WideChar>::StringBase(*(const StringBase<WideChar>*)&other);
}

class Rva004B6190Audio { public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual unsigned slot_44(const AudioEventRTS*);
};

struct Rva004B6190Data {
    unsigned m_00;
    GameWindow* m_04;
    GameWindow* m_08;
    unsigned m_0c;
};
class Rva004B5C90 { public: void invoke(bool); GameWindow* m_00; };
class Rva004B5AA0 { public: int m(const Image*,int,int,int); GameWindow* m_00; };
class BfmeThing925C { public: void bfmeGo925C(); };
class BfmeThing925D { public: void bfmeGo925D(void*); };
class BfmeThing926A { public: void bfmeGo926A(void*,void*); };
class BfmeC1040 { public: int bfmeGo1040C(); };
class BfmeThingCCH { public: int bfmeGoCCH(void*); };
extern void bfmeGo1017Y(int, int, int);

class Rva004B5C90WindowManager { public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
    virtual void slot_54();
    virtual void slot_58();
    virtual void slot_5c();
    virtual void slot_60();
    virtual void slot_64();
    virtual void slot_68();
    virtual void slot_6c();
    virtual void slot_70();
    virtual void slot_74();
    virtual void slot_78();
    virtual void slot_7c();
    virtual void slot_80();
    virtual void slot_84();
    virtual void slot_88();
    virtual void slot_8c();
    virtual void slot_90();
    virtual void slot_94();
    virtual void slot_98();
    virtual void slot_9c();
    virtual void slot_a0();
    virtual void slot_a4();
    virtual void slot_a8();
    virtual void slot_ac();
    virtual void slot_b0();
    virtual void slot_b4();
    virtual void slot_b8();
    virtual void slot_bc();
    virtual GameWindow* slot_c0();
};
extern void Rva004B7A10SetScrollButtonsHidden(GameWindow*,bool);
struct Rva004B5C90ListData {
    char m_gap00[0x28]; int m_28; int m_2c; int m_30; int m_34;
};
__declspec(noinline) void Rva004B5C90::invoke(bool hide)
{
    GameWindow* list=((Rva004B6190Data*)m_00->winGetUserData())->m_08;
    if(!list) return;
    ICoord2D windowSize;
    if(hide) {
        ICoord2D listSize;
        if(list->winIsHidden()) return;
        m_00->winGetSize(&windowSize.x,&windowSize.y);
        list->winGetSize(&listSize.x,&listSize.y);
        list->winHide(true);
        GameWindow* current=m_00;
        if(((Rva004B5C90WindowManager*)TheWindowManager)->slot_c0()==current)
            TheWindowManager->winSetLoneWindow(0);
        m_00->winSetSize(windowSize.x,windowSize.y-listSize.y);
    } else {
        ICoord2D listSize;
        if(!list->winIsHidden()) {
            return;
        }
        TheWindowManager->winSetLoneWindow(m_00);
        list->winHide(false);
        m_00->winGetSize(&windowSize.x,&windowSize.y);
        Rva004B5C90ListData* listData=(Rva004B5C90ListData*)((Rva004B6190Data*)m_00->winGetUserData())->m_08->winGetUserData();
        Rva004B6190Data* data=(Rva004B6190Data*)m_00->winGetUserData();
        listData->m_30=listData->m_34;
        listSize=windowSize;
        int total=listData->m_28+8;
        int maximum=data->m_00;
        int height;
        if(maximum >= total) {
            height=total;
            Rva004B7A10SetScrollButtonsHidden(list,true);
        } else {
            height=maximum;
            Rva004B7A10SetScrollButtonsHidden(list,false);
        }
        m_00->winSetSize(windowSize.x,windowSize.y+height);
        list->winSetPosition(0,windowSize.y);
        list->winSetSize(listSize.x,height);
    }
}


__declspec(noinline) void BfmeThing925C::bfmeGo925C() {
    GameWindow* window=*(GameWindow**)this;
    if(window) GadgetListBoxReset(((Rva004B6190Data*)window->winGetUserData())->m_08);
}
__declspec(noinline) void BfmeThing925D::bfmeGo925D(void* value) {
    GameWindow* window=*(GameWindow**)this;
    if(window) *(void**)((char*)((Rva004B6190Data*)window->winGetUserData())->m_08->winGetUserData()+0x34)=value;
}
__declspec(noinline) void BfmeThing926A::bfmeGo926A(void* a,void* b) {
    GameWindow* window=*(GameWindow**)this;
    if(window) {
        GameWindow* list=((Rva004B6190Data*)window->winGetUserData())->m_08;
        GadgetListBoxSetItemData(list,b,(int)a,0);
    }
}
__declspec(noinline) int BfmeC1040::bfmeGo1040C() {
    GameWindow* window=*(GameWindow**)this;
    if(!window) return -1;
    int value=-1;
    GameWindow* list=((Rva004B6190Data*)window->winGetUserData())->m_08;
    GadgetListBoxGetSelected(list,&value);
    return value;
}
__declspec(noinline) int BfmeThingCCH::bfmeGoCCH(void* what) {
    GameWindow* window=*(GameWindow**)this;
    if(!window) return 0;
    GameWindow* list=((Rva004B6190Data*)window->winGetUserData())->m_08;
    return (int)GadgetListBoxGetItemData(list,(int)what,0);
}
__declspec(noinline) int Rva004B5AA0::m(const Image* image,int height,int width,int color) {
    if(!m_00) return -1;
    GameWindow* list=((Rva004B6190Data*)m_00->winGetUserData())->m_08;
    unsigned char* data=(unsigned char*)((Rva004B6190Data*)m_00->winGetUserData())->m_08->winGetUserData();
    if(*(short*)(data+0x2c)>=*(short*)data) GadgetListBoxSetListLength(list,2*(int)*(short*)data);
    return GadgetListBoxAddEntryImage(list,image,-1,0,width,height,true,color);
}

WindowMsgHandledType GadgetImageComboBoxInput(GameWindow* window, UnsignedInt msg,
    WindowMsgData mData1, WindowMsgData mData2)
{
    GameWindow* adapter=window;
    WinInstanceData* instData=window->winGetInstanceData();
    switch(msg) {
    case GWM_CHAR:
        if(mData1!=KEY_TAB) return MSG_IGNORED;
        if(mData2 & KEY_STATE_DOWN) {
            if(TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT) {
                TheWindowManager->winPrevTab(window);
                return MSG_HANDLED;
            } else {
                TheWindowManager->winNextTab(window);
                return MSG_HANDLED;
            }
        }
        break;
    case GWM_LEFT_UP: {
        if(TheAudio) {
            AudioEventRTS click("GUIComboBoxClick",2);
            ((Rva004B6190Audio*)TheAudio)->slot_44(&click);
        }
        GameWindow* list=((Rva004B6190Data*)window->winGetUserData())->m_08;
        ((Rva004B5C90*)&adapter)->invoke(!list->winIsHidden());
        bfmeGo1017Y(0,1,1);
        return MSG_HANDLED;
    }
    case GWM_LEFT_DRAG:
        if(instData->m_style & GWS_MOUSE_TRACK)
            TheWindowManager->winSendSystemMsg(window->winGetOwner(),0x4000,(WindowMsgData)window,0);
        break;
    case GWM_SCRIPT_CREATE: {
        GameWindow* child=TheWindowManager->winGetWindowFromId(window,(Int)mData1);
        if(child) {
            Rva004B6190Data* data=(Rva004B6190Data*)window->winGetUserData();
            if(child->winGetStyle() & 1) {
                data->m_04=child;
            } else if(child->winGetStyle() & 0x20) {
                data->m_08=child;
                ((unsigned char*)((Rva004B6190Data*)window->winGetUserData())->m_08->winGetUserData())[0x12]=1;
                ((unsigned char*)((Rva004B6190Data*)window->winGetUserData())->m_08->winGetUserData())[0x13]=1;
                ((unsigned char*)((Rva004B6190Data*)window->winGetUserData())->m_08->winGetUserData())[0x0e]=1;
            }
        }
        break;
    }
    case GWM_LEFT_DOWN:
        if(((Rva004B5C90WindowManager*)TheWindowManager)->slot_c0()==window)
            return MSG_IGNORED;
        break;
    case GWM_RIGHT_UP:
    case GWM_WHEEL_UP:
    case GWM_WHEEL_DOWN:
        break;
    default:
        return MSG_IGNORED;
    }
    return MSG_HANDLED;
}

WindowMsgHandledType GadgetImageComboBoxSystem(GameWindow* window,unsigned msg,unsigned mData1,unsigned mData2)
{
    GameWindow* adapter=window;
    WinInstanceData* instData=window->winGetInstanceData();
    Rva004B6190Data* data=(Rva004B6190Data*)window->winGetUserData();
    switch(msg) {
    case 1: {
        Rva004B6190Data* created=new Rva004B6190Data;
        memset(created,0,sizeof(*created));
        window->winSetUserData(created);
        window->winSetOwner(window->winGetParent());
        break;
    }
    case 2:
        TheWindowManager->winSetLoneWindow(0);
        if(data) { delete data; window->winSetUserData(0); }
        break;
    case 0x17:
        if(!mData1) instData->m_state&=~2;
        else instData->m_state|=2;
        TheWindowManager->winSendSystemMsg(window->winGetOwner(),0x4003,mData1,window->winGetWindowId());
        *(bool*)mData2=true;
        break;
    case 0x4000: break;
    case 0x4001: instData->setText(*(UnicodeString*)mData1); break;
    case 0x4004: {
        GameWindow* list=((Rva004B6190Data*)window->winGetUserData())->m_08;
        if(list && list->winIsHidden()) {
            list->winSetSize(mData1,mData2);
            GameWindow* button=data->m_04;
            ICoord2D size;
            const Image* image=*(const Image**)((char*)button+0x48);
            if(image) {
                size=*image->getImageSize();
                float scale=(float)(int)mData2/size.y;
                size.x=(int)(size.x*scale); size.y=(int)(size.y*scale);
            }
            button->winSetPosition(mData1-size.x,0);
            data->m_04->winSetSize(size.x,size.y);
        }
        break;
    }
    case 0x4005:
        if(!((Rva004B6190Data*)window->winGetUserData())->m_08->winIsHidden()) ((Rva004B5C90*)&adapter)->invoke(true);
        break;
    case 0x4008:
        if((GameWindow*)mData1==data->m_04) {
            if(TheAudio) { AudioEventRTS click("GUIComboBoxClick",2); ((Rva004B6190Audio*)TheAudio)->slot_44(&click); }
            ((Rva004B5C90*)&adapter)->invoke(!((Rva004B6190Data*)window->winGetUserData())->m_08->winIsHidden());
        }
        break;
    case 0x402c: ((BfmeThing925D*)&adapter)->bfmeGo925D((void*)mData2);break;
    case 0x402b: *(int*)mData2=((BfmeC1040*)&adapter)->bfmeGo1040C();break;
    case 0x402a: ((BfmeThing926A*)&adapter)->bfmeGo926A((void*)mData1,(void*)mData2);break;
    case 0x4029:
        *(int*)mData2=((BfmeThingCCH*)&adapter)->bfmeGoCCH((void*)mData1);
        // fall through
    case 0x4014:
        ((Rva004B5C90*)&adapter)->invoke(true);
        TheWindowManager->winSendSystemMsg(window->winGetOwner(),0x4025,(unsigned)window,0);
        break;
    case 0x4024: ((BfmeThing925C*)&adapter)->bfmeGo925C(); break;
    case 0x4023: break;
    case 0x4022: return (WindowMsgHandledType)((Rva004B5AA0*)&adapter)->m((const Image*)mData1,mData2,-1,-1);
    default: return MSG_IGNORED;
    }
    return MSG_HANDLED;
}
