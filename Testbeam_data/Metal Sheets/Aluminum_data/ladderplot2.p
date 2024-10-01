set terminal png size 1000,600 font "Helvetica,18"
set output 'metalsheetladderplot_aluminium_dataset2.png'
set title 'Aluminium scattering widths dataset 2'
set xlabel "Time (in s)"
set ylabel "Width (in Pixels)"
set yrange [5:36]
plot "output_measurement_221.dat" u 2:3 t "aluminium sheets" lc "red" pt 1