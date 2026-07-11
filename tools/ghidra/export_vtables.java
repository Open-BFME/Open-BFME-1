// Ghidra headless script: export every recovered vtable and its slot -> function map.
// Usage (after the binary has been analyzed once, see README.md):
//   analyzeHeadless /tmp/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
//     -scriptPath tools/ghidra -postScript export_vtables.java $PWD/reverse/vtables.tsv
//
// Output (gitignored, derived): vtables.tsv with columns
//   vtable_rva  label  slot  func_rva  func_name
// Used to read BFME's EXACT class vtable slot order (e.g. File, Object) instead of
// triangulating slots by hand from call sites.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import java.io.*;

public class export_vtables extends GhidraScript {
    public void run() throws Exception {
        String out = getScriptArgs().length > 0 ? getScriptArgs()[0] : "vtables.tsv";
        PrintWriter w = new PrintWriter(new FileWriter(out));
        w.println("vtable_rva\tlabel\tslot\tfunc_rva\tfunc_name");
        long base = currentProgram.getImageBase().getOffset();
        Memory mem = currentProgram.getMemory();
        AddressSpace space = currentProgram.getAddressFactory().getDefaultAddressSpace();
        FunctionManager fm = currentProgram.getFunctionManager();
        SymbolTable st = currentProgram.getSymbolTable();

        SymbolIterator it = st.getAllSymbols(true);
        int nv = 0;
        while (it.hasNext()) {
            Symbol s = it.next();
            String nm = s.getName();
            if (nm == null) continue;
            String low = nm.toLowerCase();
            if (!(low.contains("vftable") || low.contains("vtable"))) continue;
            Address addr = s.getAddress();
            long vrva = addr.getOffset() - base;
            int written = 0;
            for (int slot = 0; slot < 512; slot++) {
                Address sl = addr.add(slot * 4L);
                int val;
                try { val = mem.getInt(sl); } catch (Exception e) { break; }
                long target = Integer.toUnsignedLong(val);
                if (target == 0) break;
                Address fa;
                try { fa = space.getAddress(target); }
                catch (Exception e) { break; }
                Function f = fm.getFunctionAt(fa);
                if (f == null) {
                    // first slot of a vtable may be an offset-to-top / RTTI pointer (often 0 or
                    // not a function); skip a leading non-function, stop after the body ends.
                    if (slot == 0) continue;
                    break;
                }
                long frva = f.getEntryPoint().getOffset() - base;
                w.printf("0x%X\t%s\t%d\t0x%X\t%s%n",
                        vrva, nm.replace("\t", " "), slot, frva, f.getName().replace("\t", " "));
                written++;
            }
            if (written > 0) nv++;
        }
        w.close();
        println("wrote " + nv + " vtables to " + out);
    }
}
