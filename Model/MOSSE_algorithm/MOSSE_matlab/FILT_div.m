function H = FILT_div(H1, H2)

H = H1./H2;
H = real(H) + imag(H)*1i;

end