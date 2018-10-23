% plot
run('p5p3a')
s = load('p5p3c_30_deg.mat');
figure(1)
plot(s.ans(1,:),s.ans(2,:),s.ans(1,:),s.ans(3,:))
xlabel('time[s]','Interpreter','latex')
ylabel('Compass[deg]','Interpreter','latex')
legend('Reference', 'Compass course','Interpreter','latex')

figure(2)
ss = load('p5p3c_30_deg_utenKontroller.mat');
plot(ss.ans(1,:),ss.ans(2,:),ss.ans(1,:),ss.ans(3,:))
xlabel('time[s]','Interpreter','latex')
ylabel('Compass[deg]','Interpreter','latex')
legend('Reference', 'Compass course','Interpreter','latex')