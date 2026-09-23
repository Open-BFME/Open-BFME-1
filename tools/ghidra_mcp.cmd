@echo off
rem Headless Ghidra MCP server (pyghidra-mcp) over streamable HTTP on the BFME project.
rem   Endpoint: http://127.0.0.1:8000/mcp        Log: build\pyghidra_mcp.log
rem   Setup (once): python -m venv build\toolchains\pyghidra-mcp-venv
rem                 build\toolchains\pyghidra-mcp-venv\Scripts\python -m pip install pyghidra-mcp
rem                 (needs a Ghidra release and a JDK 21 under build\toolchains\, and the analysed
rem                  project build\toolchains\bfme_ghidra\bfme.gpr from tools/ghidra_decompile.py --analyze)
rem   Register: codex  -> ~/.codex/config.toml  [mcp_servers.ghidra] url = "http://127.0.0.1:8000/mcp"
rem             claude -> claude mcp add --transport http ghidra http://127.0.0.1:8000/mcp
rem Tools: decompile_function(binary_name, name_or_address), disassemble, list_xrefs, search_strings,
rem        search_symbols_by_name, read_bytes, gen_callgraph, ... Addresses are VAs (RVA + 0x400000).
rem Ghidra's ProjectLocator rejects path elements starting with '.', so resolve the root absolutely.
for %%I in ("%~dp0..") do set ROOT=%%~fI
for /d %%G in ("%ROOT%\build\toolchains\ghidra_*") do set GHIDRA_INSTALL_DIR=%%~fG
for /d %%J in ("%ROOT%\build\toolchains\jdk-*") do set JAVA_HOME=%%~fJ
set PATH=%JAVA_HOME%\bin;%PATH%
cd /d "%ROOT%"
"%ROOT%\build\toolchains\pyghidra-mcp-venv\Scripts\pyghidra-mcp.exe" --transport streamable-http --project-path "%ROOT%\build\toolchains\bfme_ghidra\bfme.gpr" >> "%ROOT%\build\pyghidra_mcp.log" 2>&1
