% Constants from previous parts
K = 0.1557;
T = 70.5465;

Kpd = 0.838411873;
Td  = T;
Tf  = 8.390996312;

H = tf([Kpd*K],[Tf 1 0])
[Gm,Pm,Wgm,Wpm] = margin(H);
bode(H)
