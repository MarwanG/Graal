set term png size 1024,768
set output "hll.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "error"
set yrange [0:0.02]
set grid 
plot "test.txt" using 1:2 title 'hll raw' with lines, \
"testlinear.txt" using 1:2 title 'linear' with lines
