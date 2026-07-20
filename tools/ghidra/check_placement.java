// Check whether a function entry point exists at each given RVA.
// Usage: analyzeHeadless <proj> bfme -process lotrbfme.exe -noanalysis \
//   -scriptPath tools/ghidra -postScript check_placement.java <rva0> <rva1> ...
// Prints one line per RVA:  RVA <hex> ENTRY <size>  |  RVA <hex> INSIDE <funcRva>  |  RVA <hex> NONE
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

public class check_placement extends GhidraScript {
    public void run() throws Exception {
        Address imageBase = currentProgram.getImageBase();
        for (String raw : getScriptArgs()) {
            long rva = Long.decode(raw);
            Address addr = imageBase.add(rva);
            Function f = getFunctionAt(addr);
            if (f != null) {
                println("RVA " + raw + " ENTRY " + f.getBody().getNumAddresses());
            } else {
                Function cf = getFunctionContaining(addr);
                if (cf != null) {
                    println("RVA " + raw + " INSIDE " + cf.getEntryPoint());
                } else {
                    println("RVA " + raw + " NONE");
                }
            }
        }
    }
}
