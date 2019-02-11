testimg = imread('Baby-Musk-Ox.ppm');

figure(1);
image(testimg);
title('testimg.ppm');

drawnow;

testimg_ca=imadd(testimg, 25.0);
figure(2);
image(testimg_ca);
title('testimg_c_a contrast adjusted version');

drawnow;

testimg_br=immultiply(testimg, 1.25);
figure(3);
image(testimg_br);
title('testimg_b_r scaled version');

drawnow;

testimg2=imadd(immultiply(testimg, 1.25), 25.0);
figure(4);
image(testimg2);
title('testimg scaled + offset version');

drawnow;