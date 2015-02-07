set term png size 1024,768
set output "hllRaw.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "Estimation"
plot "hll_raw.txt" using 1:2 title 'Hll Raw' with lines, \
   "hll_linear.txt" using 1:2 title "Linear" with lines, \
   "hll_corrected.txt" using 1:2 title "Corrected" with lines



