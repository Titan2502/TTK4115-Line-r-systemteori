w1 = 0.005;
w2 = 0.05;
w1_compass = load('compass_w1.mat');
plot(w1_compass.ans(1,:),w1_compass.ans(2,:),w1_compass.ans(1,:),w1_compass.ans(3,:))
figure(1)
w2_compass = load('compass_w2.mat');
figure(2)
plot(w2_compass.ans(1,:),w2_compass.ans(2,:),w2_compass.ans(1,:),w2_compass.ans(3,:))

max_out_w1 = max(w1_compass.ans(2,1000:end));
min_out_w1 = min(w1_compass.ans(2,1000:end));
Amp_w1 = (max_out_w1-min_out_w1)/2

max_out_w2 = max(w2_compass.ans(2,1000:end));
min_out_w2 = min(w2_compass.ans(2,1000:end));
Amp_w2 = (max_out_w2-min_out_w2)/2

syms K T
eqns = [K/(w1*sqrt(T^2*w1^2+1)) == Amp_w1, K/(w2*sqrt(T^2*w2^2+1)) == Amp_w2];
vars =[K T];
[solK, solT] = solve(eqns, vars);
K = max(double(solK))
T = max(double(solT))
