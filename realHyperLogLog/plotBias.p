set term png size 1024,768
set output "hllBias.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "Error"
set yrange [0:0.05]
plot "hll_linear_bias.txt" using 1:2 title 'Linear' with lines, \
"hll_raw_bias.txt" using 1:2 title 'Hll Raw' with lines, \
   "hll_corrected_bias.txt" using 1:2 title "HLL Corrected" with lines



