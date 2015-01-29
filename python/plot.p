set term png size 1024,768
set output "hll.png"
set title "HyperLogLog"
set xlabel "Cardinality"
set ylabel "Estimation"
plot "res.txt" using 1:2 title 'Average' with lines, \
"res.txt" using 1:3 title 'Median' with lines, \
"res.txt" using 1:4 title '1%' with lines, \
"res.txt" using 1:5 title '99%' with lines, \
"linearRes.txt" using 1:2 title 'linear' with lines, \
"res.txt" using 1:1 title "x=y" with lines
