w1 = 0.005;
w2 = 0.05;
w1_compass_noise = load('compass_w1_noise.mat');
plot(w1_compass_noise.ans(1,:),w1_compass_noise.ans(2,:),w1_compass_noise.ans(1,:),w1_compass_noise.ans(3,:))
figure(1)
w2_compass_noise = load('compass_w2_noise.mat');
figure(2)
plot(w2_compass_noise.ans(1,:),w2_compass_noise.ans(2,:),w2_compass_noise.ans(1,:),w2_compass_noise.ans(3,:))

max_out_w1_noise = max(w1_compass_noise.ans(2,1000:end));
min_out_w1_noise = min(w1_compass_noise.ans(2,1000:end));
Amp_w1_noise = (max_out_w1_noise-min_out_w1_noise)/2

max_out_w2_noise = max(w2_compass_noise.ans(2,1000:end));
min_out_w2_noise = min(w2_compass_noise.ans(2,1000:end));
Amp_w2_noise = (max_out_w2_noise-min_out_w2_noise)/2

syms K T
eqns = [K/(w1*sqrt(T^2*w1^2+1)) == Amp_w1_noise, K/(w2*sqrt(T^2*w2^2+1)) == Amp_w2_noise];
vars =[K T];
[solK, solT] = solve(eqns, vars);
K_noise = max(double(solK))
T_noise = max(double(solT))

% Plot
figure(3)
subplot(2,1,1)
plot(w1_compass_noise.ans(1,:),w1_compass_noise.ans(2,:),w1_compass_noise.ans(1,:),w1_compass_noise.ans(3,:))
legend('input, w = 0.005','output')
subplot(2,1,2)
plot(w2_compass_noise.ans(1,:),w2_compass_noise.ans(2,:),w2_compass_noise.ans(1,:),w2_compass_noise.ans(3,:))
legend('input, w = 0.05','output')