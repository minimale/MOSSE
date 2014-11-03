function w = window_hann

w = hamming(64)*hamming(64)';
w = fix(256 * w);

end

