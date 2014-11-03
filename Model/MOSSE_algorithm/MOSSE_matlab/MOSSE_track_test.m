% Adaptive Correlation Filters with Minimum Output Sum of Squared Error (MOSSE)
% test video

clear all
close all

vidObj= VideoReader('klt_algorithm_robustness_640x360.avi');
videoPlayer  = vision.VideoPlayer('Name', 'Visual','Position',[100 100 vidObj.Height+360 vidObj.Width - 120]);

% writerObj = VideoWriter('MOSSE_ist1.avi');
nFrames = vidObj.NumberOfFrames;

H_V = vidObj.Height;
W_V = vidObj.Width;

hsize = [5 5];
sigma = 2;
th = 3;

%  
% frame = histeq(rgb2gray(read(vidObj,350)),255);
% [~, rect] = imcrop(frame);
% [w, h] = Opt_size(round(rect(3)), round(rect(4)));
% % w = 64;
% % h = 64;
% x = uint32(rect(1));
% y = uint32(rect(2));
% template = imcrop(frame, [x y w - 1 h - 1]);
% 
% window = hanning(h, w);
% temp = preproces(template, window);
% close
% G = Gauss_filt(h, w, hsize, sigma);
% [H1, H2] = FILT_func(temp, G);
% H = FILT_div(H1, H2);
% x_s = x;
% y_s = y;
% x_r = x;
% y_r = y;
ready = 0;
% open(writerObj);
 
for n = 1:nFrames
    [keyIsDown, secs, ch, deltaSecs] = KbCheck(-1);
    frame_rgb = read(vidObj, n);
    frame_gray = rgb2gray(frame_rgb);
    
    if(ch(27))
        break
    end
    
    if (ch(32))
        figure
        [~, rect] = imcrop(frame_gray);
%          [w, h] = Opt_size(round(rect(3)), round(rect(4)));
        w = 64;
        h = 64;
        h1 = 128;
        w1 = 128;
        x = uint32(rect(1)) - w/2;
        y = uint32(rect(2)) - h/2;
%         w = 64;
%         h = 64;
        th = 3;
        
        template = imcrop(frame_gray, [x y w - 1 h - 1]);
        window = hanning(h, w);
        temp = preproces(template, window);
        G = Gauss_filt(h, w, hsize, sigma);
        [H1, H2] = FILT_func(temp, G);
        H = FILT_div(H1, H2);
        bbox = [x, y, x+w, y, x+w, y+h, x, y+h];
        x_r = x;
        y_r = y;
        close
        ready = 1;
    end
    
    if (ready == 1)
        f = imcrop(frame_gray, [x  y  w1-1 h1-1]);
        [S_res, PSR, dx, dy] = corr2D_freq(preproces(f, window), H);
      
        
        if PSR > th
            color = 'green';
            x_r = x + dx;
            y_r = y + dy;
            
            if( x_r >= 1 && y_r >= 1 && x_r + w <= W_V && y_r + h <= H_V)
                x = x_r;
                y = y_r;
                bbox = [x, y, x+w, y, x+w, y+h, x, y+h];
                t = imcrop(frame_gray, [x  y  w-1 h-1]);
                [H1_n, H2_n] = FILT_func(preproces(t, window), G);
                [H1, H2] = FILT_upd(H1, H2, H1_n, H2_n);
                H = FILT_div(H1, H2);
            end 
            frame_rgb = insertShape(frame_rgb, 'Polygon', bbox, 'Color', color);
            frame_rgb = insertText(frame_rgb, [1, H_V - 45],  ['X:' num2str(x + w/2)], 'BoxColor', color);
            frame_rgb = insertText(frame_rgb, [1, H_V - 20],  ['Y:' num2str(y + h/2)], 'BoxColor', color);
            frame_rgb = insertText(frame_rgb, [x , y + h],  ['PSR:' num2str(PSR, '%0.2f')], 'BoxColor', color);
            frame_rgb = insertMarker(frame_rgb, [x + w/2, y + h/2], 'Color', color);
            frame_rgb = insertText(frame_rgb, [1 , 1],'Tracking', 'FontSize', 18, 'BoxColor', color);
            th = 7;

        else 
            color = 'red';
            frame_rgb = insertShape(frame_rgb, 'Polygon', bbox, 'Color', color);
            frame_rgb = insertText(frame_rgb, [x , y + h],  ['PSR:' num2str(PSR, '%0.2f')], 'BoxColor', color);
            frame_rgb = insertText(frame_rgb, [1 , 1],'No tracking', 'FontSize', 18, 'BoxColor', color);
        end
        
            subplot(1,3,1)
            imshow(t, []);
            title('Object')

            subplot(1,3,2)
            imshow(ifftshift(real(ifft2(H))), []);
            title('Filter')

            subplot(1,3,3)
            imshow(S_res, []);
            title('Result')
      
    end
step(videoPlayer, frame_rgb);
step(videoPlayer, frame_rgb);
% writeVideo(writerObj, frame_rgb);

end 
% close(writerObj);
delete(videoPlayer);
delete(vidObj);
close all
clear all
clc