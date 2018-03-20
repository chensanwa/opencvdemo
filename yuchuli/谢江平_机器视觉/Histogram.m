%直方图均衡化 
clear;
H=imread('jll.bmp'); 
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
s=double(J);
sum=M*N; 
k=zeros(1,256); 
e=zeros(1,256); 
t=zeros(size(s)); 
for i=1:M 
    for j=1:N 
          k(s(i,j)+1)=k(s(i,j)+1)+1; %原图像概率密度 
    end 
end 
k=k./sum; 
for i=1:256 
    for j=1:i 
        e(i)=e(i)+k(j); %累积分布 
    end 
end 
for i=1:256 
       e(i)=floor(e(i)*255+0.5); %映射关系 
end 
for i=1:M 
    for j=1:N 
        t(i,j)=e(s(i,j)+1); 
    end 
end 
s=uint8(s); 
t=uint8(t); 
subplot(2,2,1); 
imshow(s); 
title('原图')
 
subplot(2,2,2); 
imhist(s);
title('原图直方图')
 
subplot(2,2,3); 
imshow(t); 
title('直方图均衡化后的图像')
  
subplot(2,2,4); 
imhist(t); 
title('直方图均衡化后图像的直方图')
