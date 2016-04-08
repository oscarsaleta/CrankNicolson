# Cal definir:
# k : valor inicial de l'índex a l'animació
# dk : increment de k
# kmax : valor final de l'índex a l'animació
# p (s) : temps de pausa entre frames

print "k=", k
splot 'placaexp.txt' index k w l
pause p
k=k+dk
if (k<=kmax) reread
