set terminal png size 700,1000
set output 'PEEK_ladderplot_dataset2.png'
set title 'PEEK Scattering Widths Dataset 2'
set xlabel "Time (in s)"
set ylabel "Width (in Pixels)"
set yrange [5:55]
set xrange [0:300]
plot "output_measurement_222.dat" u 2:3 t "no material" lc "red" pt 1, "output_measurement_223.dat" u 2:3 t "1 mm" lc "goldenrod" pt 1, "output_measurement_224.dat" u 2:3 t "6 mm" lc "orange" pt 1, "output_measurement_225.dat" u 2:3 t "11 mm" lc "brown" pt 1, "output_measurement_226.dat" u 2:3 t "16 mm" lc "web-blue" pt 1, "output_measurement_227.dat" u 2:3 t "21 mm" lc "dark-spring-green" pt 1, "output_measurement_228.dat" u 2:3 t "26 mm" lc "black" pt 1, "output_measurement_229.dat" u 2:3 t "31 mm" lc "midnight-blue" pt 1, "output_measurement_230.dat" u 2:3 t "36 mm" lc "dark-plum" pt 1
