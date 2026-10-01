// ?Rva00377740@Rva00377740Interface@@QAEHXZ
// partial score=1.0 date=2026-10-01
// cl: /O2 /EHsc
struct Rva00377740Flags { unsigned words[10]; Rva00377740Flags(); };
struct Rva00377740Data { char prefix[0x28]; float wait28,wait2c,wait30; };
struct Rva00377740Owner {
 bool rva00377550(); void rva00373ED0();void rva00376590(bool);void rva00373530(bool);
 void rva00374420(const Rva00377740Flags&,const Rva00377740Flags&);void rva00371EE0(int,bool);
 bool rva00371B00();void rva00376C70();void rva00373B30();void rva00377060();
};
struct Rva00377740Interface {
 int Rva00377740();
 Rva00377740Owner *owner(){return (Rva00377740Owner*)((char*)this-0x10);}
 char prefix[0x8c];int state;char gap90[8];float timer;
};
int Rva00377740Interface::Rva00377740() {
 bool elapsed=false;
 Rva00377740Data *data=*(Rva00377740Data**)((char*)this-0xc);
 if(timer>0.0f) { timer-=0.2f; if(timer<0.0f){timer=0;elapsed=true;} }
 switch(state) {
 case 0: {Rva00377740Owner *p=owner();if(p->rva00377550())state=4;p->rva00373ED0();return 5;}
 case 1: state=2;owner()->rva00376590(false);timer=data->wait28;return 1;
 case 2: if(data->wait28==timer+0.2f)owner()->rva00373530(false);
 if(elapsed){state=3;Rva00377740Flags a,b;b.words[6]|=0x8000;a.words[6]|=0x10000;owner()->rva00374420(b,a);timer=data->wait30;return 1;}break;
 case 3: if(elapsed){state=4;Rva00377740Flags a,b;b.words[6]|=0x10000;Rva00377740Owner *p=owner();p->rva00374420(b,a);p->rva00371EE0(5,false);return 1;}break;
 case 4: {Rva00377740Owner *p=owner();if(p->rva00371B00())p->rva00376C70();else p->rva00373B30();return 1;}
 case 5: if(elapsed){state=0;owner()->rva00377060();timer=data->wait2c;}break;
 }
 return 1;
}
