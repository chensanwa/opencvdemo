%均值滤波
H=imread('jll.bmp'); 
a=isgray(H)
b=isrgb(H)                     %彩色图像转灰度图像
r=H(:,:,1);
g=H(:,:,2);
b=H(:,:,3); 
 [M,N]=size(r)
 for o=1:M;
    for p=1:N;
         J(o,p)=0.2989*r(o,p)+0.5870*g(o,p)+0.1140*b(o,p); 
    end
 end
c=isgray(J)
figure;
imshow(uint8(J));
title('灰度图像')
J=double(J);
[M,N]=size(J); 
for i=2:M-1;
    for j=2:N-1; 
        K(i,j)=1/8*(J(i-1,j-1)+J(i-1,j)+J(i-1,j+1)+J(i,j-1)+J(i,j)+J(i,j+1)+J(i+1,j-1)+J(i+1,j)+J(i+1,j+1));
    end
end
figure(2);
imshow(uint8(K));
title('均值滤波结果')