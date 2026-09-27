// Retail 0x005B22B0: message-ID dispatch into the global UI's virtual slots.
// Control-flow reference: GameClient/MessageStream/HintSpy.cpp in Zero Hour.
// Retail message numbers and UI slots are taken from the image; the owner stays opaque.
// Keep separate mouseover cases and the command-hint case break at 0xAD:
// MSVC builds the retail switch tree before merging their identical call blocks.
class InGameUI;
extern InGameUI *TheInGameUI;
struct Message005B22B0 { char pad00[0x10]; int m_type; };
class UISlots005B22B0 {
public:
#define SLOT(n) virtual void slot##n(const Message005B22B0*);
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
#undef SLOT
};
class MessageDispatch005B22B0 { public: int dispatch(const Message005B22B0*); };
int MessageDispatch005B22B0::dispatch(const Message005B22B0 *msg)
{
 int result=0;
 switch(msg->m_type) {
 case 0x96: case 0x97:
 case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9e: case 0x9f:
 case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa6: case 0xa7: case 0xa8:
 case 0xaa: case 0xab: case 0xad: ((UISlots005B22B0*)TheInGameUI)->slot31(msg); result=1; break;
 case 0xae: case 0xaf: case 0xb0: case 0xb1: case 0xb2:
 case 0x7d6: case 0x7d7: case 0x7d8: ((UISlots005B22B0*)TheInGameUI)->slot31(msg); result=1; break;
 case 0x94: ((UISlots005B22B0*)TheInGameUI)->slot30(msg); result=1; break;
 case 0x95: ((UISlots005B22B0*)TheInGameUI)->slot30(msg); result=1; break;
 case 0x98: ((UISlots005B22B0*)TheInGameUI)->slot25(msg); break;
 case 0x423: ((UISlots005B22B0*)TheInGameUI)->slot26(msg); break;
 case 0x424: ((UISlots005B22B0*)TheInGameUI)->slot28(msg); break;
 case 0x425: case 0x426: ((UISlots005B22B0*)TheInGameUI)->slot29(msg); break;
 case 0x42b: ((UISlots005B22B0*)TheInGameUI)->slot32(msg); break;
 case 0x42e: case 0x42f: case 0x430: ((UISlots005B22B0*)TheInGameUI)->slot27(msg); break;

 }
 return result;
}
