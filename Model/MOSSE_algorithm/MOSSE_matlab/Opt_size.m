function [w, h] = Opt_size( w_p, h_p)

if(rem(w_p/2,1))
    w = w_p + 1;
else
    w = w_p;
end

if(rem(h_p/2,1))
    h = h_p + 1;
else
    h = h_p;
end
    
end

