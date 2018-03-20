%分段线性变换（灰度切割）
 
I=imread('jll.bmp');
a=isgray(I)
b=isrgb(I)
r=I(:,:,1);
g=I(:,:,2);
b=I(:,:,3); 
 [M,N]=size(r)
 for i=1:M;
    for j=1:N;
         J(i,j)=0.2989*r(i,j)+0.5870*g(i,j)+0.1140*b(i,j); 
    end
 end
 
figure;
imshow(uint8(J));
J=double(J);
[M,N]=size(J);
for i=1:M
    for j=1:N
    if J(i,j)<100                   %灰度小于100的像素，灰度不变
        J(i,j)=0;
    elseif J(i,j)>100&&J(i,j)<200   %灰度介于50和200之间的，令灰度等于150
        J(i,j)=150;
    else J(i,j)=J(i,j);            %灰度大于200的像素，灰度值不变
    end
  end
end
figure(2);
imshow(uint8(J));
title('灰度切割')
 