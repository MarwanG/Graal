set term png size 1024,768
set output "hllCorrect.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "Estimation"
plot "resHLLBRUT.txt" using 1:2 title 'Average' with lines
