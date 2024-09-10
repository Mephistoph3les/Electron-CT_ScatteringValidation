set terminal png size 700,1000
set output 'PEEK_ladderplot_dataset1.png'
set title 'PEEK Scattering Widths Dataset 1'
set xlabel "Time (in s)"
set ylabel "Width (in Pixels)"
set yrange [5:55]
set xrange [0:300]
plot "output_measurement_190.dat" u 2:3 t "no material" lc "red" pt 1, "output_measurement_191.dat" u 2:3 t "1 mm" lc "goldenrod" pt 1, "output_measurement_192.dat" u 2:3 t "6 mm" lc "orange" pt 1, "output_measurement_193.dat" u 2:3 t "11 mm" lc "brown" pt 1, "output_measurement_194.dat" u 2:3 t "16 mm" lc "web-blue" pt 1, "output_measurement_195.dat" u 2:3 t "21 mm" lc "dark-spring-green" pt 1, "output_measurement_196.dat" u 2:3 t "26 mm" lc "black" pt 1, "output_measurement_197.dat" u 2:3 t "31 mm" lc "midnight-blue" pt 1, "output_measurement_198.dat" u 2:3 t "36 mm" lc "dark-plum" pt 1
