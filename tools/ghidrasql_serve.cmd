@echo off
rem GhidraSQL HTTP server on the BFME Ghidra project: SQL over functions, xrefs,
rem strings, types, disassembly and decompilation (github.com/0xeb/ghidrasql).
rem   Endpoint: POST http://127.0.0.1:8081/query  (body = SQL)   Health: GET /health
rem   Stop:     curl -X POST http://127.0.0.1:8081/shutdown       Log: build\ghidrasql.log
rem   Example:  curl -s -X POST http://127.0.0.1:8081/query --data "SELECT name, size FROM funcs WHERE addr = 0x008410C0"
rem Addresses are VAs (RVA + 0x400000). Decompiler tables need a func_addr filter,
rem or every function is decompiled.
rem   Setup (once, needs VS 2022 C++, CMake, Gradle, JDK 21, a Ghidra release under build\toolchains):
rem     git clone https://github.com/0xeb/libghidra   build\toolchains\src\libghidra
rem     git clone https://github.com/0xeb/ghidrasql   build\toolchains\src\ghidrasql
rem     cd build\toolchains\src\libghidra\ghidra-extension && gradle installExtension -PGHIDRA_INSTALL_DIR=<ghidra>
rem     cd build\toolchains\src\ghidrasql && cmake -B build -G "Visual Studio 17 2022" -A x64 -DGHIDRASQL_LIBGHIDRA_DIR=../libghidra/cpp
rem                                       && cmake --build build --config Release
rem   Needs the analysed project build\toolchains\bfme_ghidra\bfme.gpr (tools/ghidra_decompile.py --analyze).
rem Read-only by default. `tools\ghidrasql_serve.cmd write` saves renames/comments into the project.
rem Ghidra locks an open project: stop tools\ghidra_mcp.cmd first, the two cannot share it.
for %%I in ("%~dp0..") do set ROOT=%%~fI
for /d %%G in ("%ROOT%\build\toolchains\ghidra_*") do set GHIDRA=%%~fG
for /d %%J in ("%ROOT%\build\toolchains\jdk-*") do set JAVA_HOME=%%~fJ
set PATH=%JAVA_HOME%\bin;%PATH%
set MODE=--readonly --shutdown discard
if /i "%~1"=="write" set MODE=--shutdown save
cd /d "%ROOT%"
"%ROOT%\build\toolchains\src\ghidrasql\build\bin\Release\ghidrasql.exe" --ghidra "%GHIDRA%" ^
  --project "%ROOT%\build\toolchains\bfme_ghidra" --project-name bfme --program lotrbfme.exe ^
  --no-analyze %MODE% --http --port 8081 --max-runtime 0 >> "%ROOT%\build\ghidrasql.log" 2>&1
