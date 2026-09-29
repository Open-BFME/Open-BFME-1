// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// BFME 1.03: native parser derived from the ZH GameWindowManagerScript.cpp twin.
// The parent argument is witnessed by [entry esp+12] and RET 12; the old lift omitted it.
// WindowLayoutInfo 0x2c layout is witnessed by its constructor at 0x004888a0.
// Local color/font parser bodies preserve MSVC private register ABIs.
#include "ascii_string.h"
#include <list>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
template<typename T> inline void StringBase<T>::set(const T *s) {set(s,s ? strlen(s):0);}
template<typename T> inline int StringBase<T>::compare(const T *s) const {
 int a=m_data ? m_data->length:0;const T *d=m_data ? m_data->data:(const T *)"";
 int b=s ? strlen(s):0;int n=a<b?a:b;int c=memcmp(d,s,n);return c ? c:a-b;
}
inline AsciiString &AsciiString::operator=(const char*s){StringBase<char>::set(s);return *this;}
class GameWindow {public:unsigned winGetStatus();void winSetStatus(unsigned);};
class GameFont;
class File {public:virtual ~File()=0;virtual void open()=0;virtual void close()=0;virtual int read(void*,int)=0;virtual int write(const void*,int)=0;virtual int seek(int,int)=0;virtual void nextLine(char*,int)=0;virtual bool scanInt(int&)=0;virtual bool scanReal(float&)=0;virtual bool scanString(AsciiString&)=0;};
class FileSystem {public:File *openFile(const char*,int);};extern FileSystem *TheFileSystem;
class WindowLayoutInfo {public:
 WindowLayoutInfo();~WindowLayoutInfo();WindowLayoutInfo &operator=(const WindowLayoutInfo&);
 unsigned version;void *init,*update,*shutdown,*field_10;
 AsciiString initNameString,updateNameString,shutdownNameString,field_20,field_24;
 std::list<GameWindow*> windows;
};
// Retail vtables 0x010f8b60 and 0x01126ed0: script slot +0x68; color slot +0x104.
class GameWindowManager {public:
virtual void slot_000();
virtual void slot_004();
virtual void slot_008();
virtual void slot_00C();
virtual void slot_010();
virtual void slot_014();
virtual void slot_018();
virtual void slot_01C();
virtual void slot_020();
virtual void slot_024();
virtual void slot_028();
virtual void slot_02C();
virtual void slot_030();
virtual void slot_034();
virtual void slot_038();
virtual void slot_03C();
virtual void slot_040();
virtual void slot_044();
virtual void slot_048();
virtual void slot_04C();
virtual void slot_050();
virtual void slot_054();
virtual void slot_058();
virtual void slot_05C();
virtual void slot_060();
virtual void slot_064();
virtual GameWindow *winCreateFromScript(AsciiString,WindowLayoutInfo*,GameWindow*);
virtual void slot_06C();
virtual void slot_070();
virtual void slot_074();
virtual void slot_078();
virtual void slot_07C();
virtual void slot_080();
virtual void slot_084();
virtual void slot_088();
virtual void slot_08C();
virtual void slot_090();
virtual void slot_094();
virtual void slot_098();
virtual void slot_09C();
virtual void slot_0A0();
virtual void slot_0A4();
virtual void slot_0A8();
virtual void slot_0AC();
virtual void slot_0B0();
virtual void slot_0B4();
virtual void slot_0B8();
virtual void slot_0BC();
virtual void slot_0C0();
virtual void slot_0C4();
virtual void slot_0C8();
virtual void slot_0CC();
virtual void slot_0D0();
virtual void slot_0D4();
virtual void slot_0D8();
virtual void slot_0DC();
virtual void slot_0E0();
virtual void slot_0E4();
virtual void slot_0E8();
virtual void slot_0EC();
virtual void slot_0F0();
virtual void slot_0F4();
virtual void slot_0F8();
virtual void slot_0FC();
virtual void slot_100();
virtual int winMakeColor(unsigned char,unsigned char,unsigned char,unsigned char);
};
void readUntilSemicolon(File*,char*,int);
extern GameWindowManager *TheWindowManager;
// Retail parseColor calls the window manager vtable at +0x104 (0x0048466f).
static bool parseColor(int *color,char *buffer) {
 char *c;unsigned char red,green,blue;
 c=strtok(buffer," \t\n\r");red=atoi(c);
 c=strtok(0," \t\n\r");green=atoi(c);
 c=strtok(0," \t\n\r");blue=atoi(c);
 *color=TheWindowManager->winMakeColor(red,green,blue,255);return true;
}
static bool parseDefaultColor(int*color,File*inFile,char*buffer) {AsciiString str;inFile->scanString(str);readUntilSemicolon(inFile,buffer,2048);if(!strcmp(buffer,"TRANSPARENT"))*color=0xffffff;else parseColor(color,buffer);return true;}
static bool parseDefaultFont(GameFont*,File*inFile,char*buffer) {AsciiString str;inFile->scanString(str);readUntilSemicolon(inFile,buffer,2048);return true;}
bool parseLayoutBlock(File*,char*,unsigned,WindowLayoutInfo*);
GameWindow *parseWindow(File*,char*);GameWindow *popWindow();
static GameWindow *windowStack[10];static GameWindow **stackPtr;
static int defEnabledColor,defDisabledColor,defBackgroundColor,defHiliteColor,defSelectedColor,defTextColor;
static GameFont *defFont;
GameWindow *GameWindowManager::winCreateFromScript(AsciiString filenameString,WindowLayoutInfo *info,GameWindow *parent) {
 const char *filename=filenameString.str();static char buffer[2048];GameWindow *firstWindow=0,*window;
 char filepath[260]="Window\\";File *inFile;WindowLayoutInfo scriptInfo;AsciiString asciibuf;
 bool inherit=parent ? ((parent->winGetStatus() & 0x8000000)!=0):false;
 memset(windowStack,0,sizeof(windowStack));stackPtr=windowStack;
 defEnabledColor=0;defDisabledColor=0;defBackgroundColor=0;defHiliteColor=0;defSelectedColor=0;defTextColor=0;defFont=0;
 if(parent)*stackPtr++=parent;
 if(strchr(filename,'\\')==0)sprintf(filepath,"Window\\%s",filename);else strcpy(filepath,filename);
 inFile=TheFileSystem->openFile(filepath,1);if(inFile==0)return 0;
 int version;inFile->read(0,15);inFile->scanInt(version);inFile->nextLine(0,0);
 if(version>=2) {if(!parseLayoutBlock(inFile,buffer,version,&scriptInfo))return 0;}
 else {scriptInfo.initNameString="APT:None";scriptInfo.updateNameString="APT:None";scriptInfo.shutdownNameString="APT:None";scriptInfo.field_20="APT:None";}
 while(true) {
 if(!inFile->scanString(asciibuf))break;
 if(asciibuf.compare("END")==0)continue;
 if(asciibuf.compare("ENABLEDCOLOR")==0){if(!parseDefaultColor(&defEnabledColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("DISABLEDCOLOR")==0){if(!parseDefaultColor(&defDisabledColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("HILITECOLOR")==0){if(!parseDefaultColor(&defHiliteColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("SELECTEDCOLOR")==0){if(!parseDefaultColor(&defSelectedColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("TEXTCOLOR")==0){if(!parseDefaultColor(&defTextColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("BACKGROUNDCOLOR")==0){if(!parseDefaultColor(&defBackgroundColor,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("FONT")==0){if(!parseDefaultFont(defFont,inFile,buffer)){inFile->close();inFile=0;return 0;}}
 else if(asciibuf.compare("WINDOW")==0){window=parseWindow(inFile,buffer);if(inherit)window->winSetStatus(0x8000000);if(firstWindow==0)firstWindow=window;scriptInfo.windows.push_back(window);}
 }
 inFile->close();inFile=0;if(info)*info=scriptInfo;if(parent)popWindow();return firstWindow;
}
