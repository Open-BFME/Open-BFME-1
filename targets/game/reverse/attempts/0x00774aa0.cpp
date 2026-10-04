// ?run@Seat00774AA0Owner@@QAEXMHPAUSeatBones@@PAUSeatRecord@@H@Z
// partial score=1.0 date=2026-10-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct SeatRecord {char pad[0xac];unsigned char flags;};
struct SeatLogic {char pad[0x6b];bool flag;};
struct SeatState {char pad[0x54];bool flag;};
extern SeatLogic *seatLogic;
extern SeatState *seatState;
struct SeatBones {void **begin,**end;};
class Seat00774AA0Owner {
public:
 void run(float,int,SeatBones *,SeatRecord *,int);
 void add(void **);
 void validate(float,int,SeatRecord *,int);
 void turret(SeatRecord *);
};
struct Seat00774AA0Receiver:SeatRecord{void barrel(Seat00774AA0Owner *);};
void Seat00774AA0Owner::run(float a,int b,SeatBones *bones,SeatRecord *record,int e){
 if(!record)return;
 if(!(record->flags&16) && ((seatLogic && seatLogic->flag)||(seatState && seatState->flag))){
  for(void **it=bones->begin;it!=bones->end;++it)add(it);
  record->flags|=16;
 }
 validate(a,b,record,e);turret(record);static_cast<Seat00774AA0Receiver*>(record)->barrel(this);
}
