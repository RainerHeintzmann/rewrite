using REPL
d = REPL.REPLCompletions.latex_symbols
open(ARGS[1], "w") do io
    for k in sort(collect(keys(d)))
        println(io, k, "\t", d[k])
    end
end
println(length(d), " entries, Julia ", VERSION)
