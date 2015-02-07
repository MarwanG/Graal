set term png size 1024,768
set output "hllBias.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "Error"
set yrange [0:0.05]
plot "linearError.txt" using 1:2 title 'Linear' with lines, \
"HllRawError.txt" using 1:2 title 'Hll Raw' with lines, \
"HllNonBiasError.txt" using 1:2 title 'Hll non bias' with lines



