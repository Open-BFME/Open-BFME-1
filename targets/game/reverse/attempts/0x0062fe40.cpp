// ?Rva0062FE40@@YAHHHPADHHH@Z
// partial score=0.7415 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /I. /Igame/Libraries/Source/WWVegas/WWLib
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <stdlib.h>
extern unsigned char checkingForPatchBeforeGameSpy, mustDownloadPatch, cantConnectBeforeOnline;
extern int checksLeftBeforeOnline, timeThroughOnline;
void Rva0062FA20(int mandatory, AsciiString url);
void Rva0062EA60StartOnline();
int Rva0062FE40(int request, int status, char *buffer, int bytes, int stamp, int run)
{
 if(run!=timeThroughOnline) return 1;
 --checksLeftBeforeOnline;
 if(status!=0) {
  if(checkingForPatchBeforeGameSpy) {
   cantConnectBeforeOnline=1;
   if(!checksLeftBeforeOnline) Rva0062EA60StartOnline();
  }
  return 1;
 }
 {
  AsciiString message(buffer), line;
  while(message.nextToken(&line,"\r\n")) {
   AsciiString type, requirement, url;
   bool ok=true;
   ok &= line.nextToken(&type," ");
   ok &= line.nextToken(&requirement," ");
   ok &= line.nextToken(&url," ");
   if(ok && type.compare("patch")==0) {
    Rva0062FA20(atoi(requirement.str()),url);
    if(atoi(requirement.str())) mustDownloadPatch=1;
   }
  }
  if(!checksLeftBeforeOnline) Rva0062EA60StartOnline();
 }
 return 1;
}
