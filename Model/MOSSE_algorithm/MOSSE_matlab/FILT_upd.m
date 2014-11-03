function [H1, H2] = FILT_upd(H1_p, H2_p, H1_n, H2_n)

alfa = 0.125;

H1 = (1 - alfa)*H1_p + alfa*H1_n;
H2 = (1 - alfa)*H2_p + alfa*H2_n;

end

