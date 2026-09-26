// Preserve owned ranges and reference sites; a function's address count is not its extent.
import ghidra.app.script.GhidraScript;
import ghidra.framework.Application;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.TreeSet;

public class worldbuilder_analysis extends GhidraScript {
    private long base;

    private String rva(Address address) {
        return address != null && address.isMemoryAddress()
            ? String.format("0x%08X", address.getOffset() - base) : "";
    }

    private String text(String value) {
        return value.replace("\\", "\\\\").replace("\t", "\\t")
            .replace("\n", "\\n").replace("\r", "\\r");
    }

    private PrintWriter writer(Path directory, String name) throws Exception {
        return new PrintWriter(Files.newBufferedWriter(directory.resolve(name), StandardCharsets.UTF_8));
    }

    public void run() throws Exception {
        if (getScriptArgs().length != 1) throw new IllegalArgumentException("Expected output directory");
        Path directory = Paths.get(getScriptArgs()[0]);
        Files.createDirectories(directory);
        base = currentProgram.getImageBase().getOffset();
        FunctionManager functions = currentProgram.getFunctionManager();
        long functionCount = 0, callCount = 0, stringCount = 0;
        try (PrintWriter out = writer(directory, "function_ranges.tsv")) {
            out.print("entry_rva\towned_bytes\tranges\tthunk_target_rva\tname\n");
            FunctionIterator it = functions.getFunctions(true);
            while (it.hasNext()) {
                monitor.checkCancelled();
                Function function = it.next();
                StringBuilder ranges = new StringBuilder();
                AddressRangeIterator owned = function.getBody().getAddressRanges(true);
                while (owned.hasNext()) {
                    AddressRange range = owned.next();
                    if (ranges.length() > 0) ranges.append(";");
                    ranges.append(rva(range.getMinAddress())).append(":").append(rva(range.getMaxAddress()));
                }
                Function thunk = function.isThunk() ? function.getThunkedFunction(false) : null;
                out.print(rva(function.getEntryPoint()) + "\t" + function.getBody().getNumAddresses() + "\t"
                    + ranges + "\t" + (thunk == null ? "" : rva(thunk.getEntryPoint())) + "\t"
                    + text(function.getName()) + "\n");
                functionCount++;
            }
        }
        try (PrintWriter out = writer(directory, "calls.tsv")) {
            out.print("instruction_rva\tcaller_rva\ttarget_rva\tflow_type\n");
            InstructionIterator it = currentProgram.getListing().getInstructions(true);
            while (it.hasNext()) {
                monitor.checkCancelled();
                Instruction instruction = it.next();
                if (!instruction.getFlowType().isCall()) continue;
                Function caller = functions.getFunctionContaining(instruction.getAddress());
                String prefix = rva(instruction.getAddress()) + "\t"
                    + (caller == null ? "" : rva(caller.getEntryPoint())) + "\t";
                TreeSet<String> destinations = new TreeSet<String>();
                for (Address address : instruction.getFlows()) destinations.add(rva(address));
                if (destinations.isEmpty()) destinations.add("");
                for (String destination : destinations) {
                    out.print(prefix + destination + "\t" + instruction.getFlowType() + "\n");
                    callCount++;
                }
            }
        }
        try (PrintWriter out = writer(directory, "string_references.tsv")) {
            out.print("string_rva\treference_rva\tfunction_rva\tvalue\n");
            DataIterator it = currentProgram.getListing().getDefinedData(true);
            while (it.hasNext()) {
                monitor.checkCancelled();
                Data data = it.next();
                if (!(data.getValue() instanceof String)) continue;
                TreeSet<String> references = new TreeSet<String>();
                ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(data.getAddress());
                while (refs.hasNext()) {
                    Address from = refs.next().getFromAddress();
                    Function function = functions.getFunctionContaining(from);
                    references.add(rva(from) + "\t" + (function == null ? "" : rva(function.getEntryPoint())));
                }
                for (String ref : references) {
                    out.print(rva(data.getAddress()) + "\t" + ref + "\t" + text((String)data.getValue()) + "\n");
                    stringCount++;
                }
            }
        }
        try (PrintWriter out = writer(directory, "analysis_metadata.tsv")) {
            out.print("key\tvalue\n");
            out.print("program_sha256\t" + currentProgram.getExecutableSHA256() + "\n");
            out.print("ghidra_version\t" + Application.getApplicationVersion() + "\n");
            out.print("java_version\t" + System.getProperty("java.version") + "\n");
            out.print("language\t" + currentProgram.getLanguageID() + "\n");
            out.print("compiler_spec\t" + currentProgram.getCompilerSpec().getCompilerSpecID() + "\n");
            out.print("functions\t" + functionCount + "\n");
            out.print("call_rows\t" + callCount + "\n");
            out.print("string_reference_rows\t" + stringCount + "\n");
        }
        println("WorldBuilder: " + functionCount + " function ranges, " + callCount
            + " call rows, " + stringCount + " string-reference rows");
    }
}
