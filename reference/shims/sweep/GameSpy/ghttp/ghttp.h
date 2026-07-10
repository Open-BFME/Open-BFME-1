/*
**  GameSpy ghttp shim — minimal declarations for sweep compilation
*/

#pragma once

#ifndef __GHTTP_H__
#define __GHTTP_H__

void ghttpStartup(void);
void ghttpCleanup(void);
void ghttpSetProxy(const char* proxy);

#endif // __GHTTP_H__
