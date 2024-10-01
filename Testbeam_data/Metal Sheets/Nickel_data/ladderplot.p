set terminal png size 1000,600 font "Helvetica,18"
set output 'metalsheetladderplot_overnight_nickel.png'
set title 'Nickel scattering widths'
set xlabel "Time (in s)"
set ylabel "Width (in Pixels)"
set yrange [0:300]
plot "output_measurement_203.dat" u 2:3 t "nickel sheets" lc "red" pt 1