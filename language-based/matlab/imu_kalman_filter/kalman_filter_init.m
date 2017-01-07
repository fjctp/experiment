close all; clear; clc;

%%
dt = 1/50;

x_seed = round(abs(rand()*1000));
xdot_seed = round(abs(rand()*1000));

%%
A = [1 dt; 0 1];
B = zeros(2, 1);
H = eye(2, 2);

Q = 0.01*eye(2,2);
R = 0.95*eye(2,2);

P0 = Q;
x0 = [0 0]';

%%
sim('kalman_filter');
vars = create_simout_struct(logsout);

%%
figure(1)
hold on
plot(vars.x(1, :), vars.x(2, :))
plot(vars.x_estimate(1, :), vars.x_estimate(2, :))
plot(vars.x_measured(1, :), vars.x_measured(2, :), 'x')
hold off
legend('Real', 'Estimate', 'Measure')
xlabel('Time (s)')

% 
% figure(2)
% subplot(2, 1, 1)
% plot(vars.K(1, :), vars.K(2, :))
% legend('Kx')
% subplot(2, 1, 2)
% plot(vars.K(1, :), vars.K(3, :))
% legend('Kxdot')
% xlabel('Time (s)')
% 
% figure(1)

%% 
std_dev = sqrt(sum((vars.x_estimate(2,:) - vars.x(2,:)).^2)/501);
fprintf('Std Dev: %.4f\n', std_dev/pi*180);