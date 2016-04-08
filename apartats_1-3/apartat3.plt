reset

set pm3d
unset surface
set view map

set cbrange[0:25]

set terminal postscript color enhanced

# t=0
set output 'plots/a3-t0.eps'
set title "tau=0"
splot 'placaexp.txt' u 1:2:3 index 0 title ''
!epstopdf 'plots/a3-t0.eps'
!rm 'plots/a3-t0.eps'

# t=400*dt
set output 'plots/a3-t400.eps'
set title "tau=0.264"
splot 'placaexp.txt' u 1:2:3 index 400 title ''
!epstopdf 'plots/a3-t400.eps'
!rm 'plots/a3-t400.eps'

# t=800*dt
set output 'plots/a3-t800.eps'
set title "tau=0.528"
splot 'placaexp.txt' u 1:2:3 index 800 title ''
!epstopdf 'plots/a3-t800.eps'
!rm 'plots/a3-t800.eps'

# t=1499*dt
set output 'plots/a3-t1499.eps'
set title "tau=0.989"
splot 'placaexp.txt' u 1:2:3 index 1499 title ''
!epstopdf 'plots/a3-t1499.eps'
!rm 'plots/a3-t1499.eps'
