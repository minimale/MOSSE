function [H1, H2] = FILT_func(t, G)
 
T = fft2(t);

H1 = G.*conj(T);
H2 = T.*conj(T);

end

