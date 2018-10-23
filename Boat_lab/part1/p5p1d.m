%% Part 1 d
K = 0.1557;
T = 70.5465
comparison = load('compass_comparison.mat');
plot(comparison.ans(1,:),comparison.ans(2,:),comparison.ans(1,:),comparison.ans(3,:))
xlabel('time[s]','Interpreter','latex')
ylabel('Direction[deg]','Interpreter','latex')
legend('Transfer function', 'Cargo Ship','Interpreter','latex')