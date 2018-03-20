%分水岭算法边缘检测
 
 
I=imread('jll.bmp');

a=isgray(I)                    %彩色图像转为灰度图像
b=isrgb(I)
r=I(:,:,1);
g=I(:,:,2);
b=I(:,:,3); 
 [M,N]=size(r)
 for i=1:M;
    for j=1:N;
         h(i,j)=0.2989*r(i,j)+0.5870*g(i,j)+0.1140*b(i,j); 
    end
end
c=isgray(h)
d=isrgb(h)

subplot(231);                 %显示灰度图像
imshow(h);
 title('灰度图像');
 
 f=double(h);
hv=fspecial('prewitt');
hh=hv;
gv=abs(imfilter(f,hv,'replicate'));
gh=abs(imfilter(f,hh,'replicate'));
g=sqrt(gv.^2+gh.^2);
subplot(2,3,2);
df=bwdist(f)
imshow(df*8);
L=watershed(df);
em=L==0;
subplot(233);
imshow(em);
im=imextendedmax(f,30);
subplot(234);
imshow(im);
g2=imimposemin(g,im|em);
subplot(235);
imshow(g2);
L2=watershed(g2);
wr2=L2==0;
subplot(236);
f(wr2)=255;
imshow(uint8(f));
figure
imshow(uint8(f));
