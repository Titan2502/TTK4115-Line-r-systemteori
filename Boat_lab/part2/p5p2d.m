s = load('wave.mat');
wave = s.psi_w(2,:)*pi/180;
window = 4096;
fs = 10;
[pxx,f] = pwelch(wave,window, [], [],fs);
pxx_corrected = pxx/(2*pi);
omega = f*(2*pi);
plot(omega,pxx_corrected)
xlabel('$\omega$ $[rad/s]$','Interpreter','latex')
ylabel('Power spectral density [s/rad]','Interpreter','latex')

%%
% Finding omega_0 can be done my finding omega wich corresponds to the
% maximum power spectal density function value

[sig2 ind] = max(pxx_corrected);
sig = sqrt(sig2);
omega_0 = omega(ind)


%% Curve fitting
% Initialization
lam = 1;            % Lambda
lam_prev = lam;     % Placeholder for previous lambda
lam_prev_prev = lam;% Placeholder for lambda(i-2)
res = 1e6;          % Tolerance
frac = 1;           % Value used to decrease change in lambda
while res > 1e-9
    % Update wave constant and PSD
    Kw = 2*lam*omega_0*sig;
    Ppsi_w = omega.^2*Kw^2./((omega_0^2-omega.^2).^2 + (omega*lam*omega_0*2).^2);
    
    % Store current and previous lambda
    lam_prev_prev = lam_prev;
    lam_prev = lam;
    
    % Calculate new residual using lsq or area under curves
%     res_next = sum((Spsi_w - Ppsi_w).^2); % lsq
    res_next = abs(trapz(omega,pxx_corrected) - trapz(omega,Ppsi_w)); % area
    
    % If residual has increased, then change how lambda is changed
    if res_next > res
        frac = -frac;
    end
    
    % If lambda won't change from previous, then use smaller changes
    if abs(lam + frac - lam_prev_prev) < 1e-9
        frac = frac*.1;
    end
    
    % Update lambda
    lam = lam + frac;
    
    % Break loop if residual is below tolerance
    if abs(lam - lam_prev) < 1e-9
        break;
    end
    
    res = res_next; % Update residual
end
disp(lam)
plot(omega,pxx_corrected,omega,Ppsi_w)