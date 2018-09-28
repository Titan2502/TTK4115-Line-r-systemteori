K_pd = 10;
K_pp = 10;
H = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
pzmap(H)
hold on

K_pd = 5;
K_pp = 25;
H1 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
pzmap(H1)

K_pd = 0;
K_pp = 5;
H2 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
pzmap(H2)

K_pd = 5;
K_pp = 0;
H3 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
pzmap(H3)

grid on
legend('K_{pd}, K_{pp} = 10, 10', 'K_{pd}, K_{pp} = 5, 25' ...
       ,'K_{pd}, K_{pp} = 0, 5', 'K_{pd}, K_{pp} = 5, 0')