%��
I=imread('001.jpg');
figure(1);
imshow(I);
title('��ɫͼ��')              %��ʾԭͼ��
a=isgray(I)                    %��ɫͼ��תΪ�Ҷ�ͼ��
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
figure(2);                   %��ʾ�Ҷ�ͼ��
imshow(h);
 title('�Ҷ�ͼ��');
h=double(h);                 %��
h=255-h;
h=uint8(h);
figure(3);
imshow(uint8(h));           %��ʾ�󷴺��ͼ��
title('�󷴺��ͼ��')