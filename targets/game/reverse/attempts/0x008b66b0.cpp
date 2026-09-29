// ?rva008B66B0@Rva008B6880@@QAEHHHH@Z
// partial score=0.84 date=2026-09-30
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B66B0; matched invoke() passes year month day and uses result as weekday index.
extern "C" double __cdecl floor(double);
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
bool __stdcall isLeapYear(int);
class Rva008B6880 {
public:
    int rva008B66B0(int year, int month, int day);
    bool isLeapYear(int);
};
inline bool leap008B66B0(int year) {
    bool result=false;
    if(year%4==0) {
        if(year%100!=0) return true;
        result=year%400==0;
    }
    return result;
}
int Rva008B6880::rva008B66B0(int year,int month,int day) {
    int century=year/100;
    int last=year%100;
    int reference=month+1;
    int anchors[4]={3,2,0,5};
    int index;
    if(century<19) index=4-abs(century-19)%4;
    else index=abs(century-19)%4;
    int anchor=anchors[index];
    int base=year-last;
    if(month==1) reference=28+(leap008B66B0(year)?1:0);
    else if(month%2==0) {
        if(month==8) reference=5;
        else if(month==4) reference=9;
        else if(month==6) reference=11;
        else if(month==10) reference=7;
        else if(month==2) reference=7;
        else if(month==0) {
            reference=31+(isLeapYear(year)?1:0);
        }
    }
    if(anchor<0 || reference<0) return -1;
    int adjusted=day;
    if(reference>day) adjusted=reference-(reference-day)%7+7;
    int value=((int)floor((year-base)*0.25f)-base+anchor+year)%7;
    return (value+(adjusted-reference)%7)%7;
}
