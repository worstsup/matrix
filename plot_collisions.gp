set terminal pngcairo size 1024,768 enhanced font 'Verdana,10'
set output 'collisions_graph.png'

set title "Зависимость числа коллизий от размера данных"
set xlabel "Размер данных (N)"
set ylabel "Число коллизий"
set grid
set key top left
set format y "%.0f"
set logscale x

plot "collisions_h1.dat" with linespoints title "Хеш-функция 1 (DJB2)", \
     "collisions_h2.dat" with linespoints title "Хеш-функция 2 (SDBM)", \
     "collisions_h3.dat" with linespoints title "Хеш-функция 3 (ROT13)"
