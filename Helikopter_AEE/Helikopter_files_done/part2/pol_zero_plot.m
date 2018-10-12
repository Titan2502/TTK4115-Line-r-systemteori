% K_pd = 10;
% K_pp = 10;
% H = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
% pzmap(H)
% hold on

K_pd = 7.307922432746453;
K_pp = 15.564895730560675;
H1 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
pzmap(H1)
hold on
Krp = -2;
H2 = tf([Krp*K3],[1 Krp*K3]);
pzmap(H2)

% K_pd = 0;
% K_pp = 5;
% H2 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
% pzmap(H2)
% 
% K_pd = 5;
% K_pp = 0;
% H3 = tf([K1*K_pp],[1 K1*K_pd K1*K_pp]);
% pzmap(H3)

grid on
% legend('K_{pd}, K_{pp} = 10, 10', 'K_{pd}, K_{pp} = 7.3079, 15.564' ...
%        ,'K_{pd}, K_{pp} = 0, 5', 'K_{pd}, K_{pp} = 5, 0')
legend('K_{pd}, K_{pp} = 7.3079, 15.564', 'K_{rp} = -2')