%�ṹ������������
clear;
I=imread('picture3.jpg');
 figure;
imshow(I);
 [M,N]=size(I);
for i=1:M
    for j=1:N
        if I(i,j)>105
            e(i,j)=255;  %e  ��ֵͼ��
        else e(i,j)=0;
        end
    end
end
figure;
imshow(e);   
a(1)=0;
a(2)=0; 
 n=0; 
 max=0;
 K=zeros(size(I));  %K  �������ƽ���
d=zeros(size(I));   %d  ��������ͼ��
[M,N]=size(I);
for i=1:M
    for j=1:N-1
        if (xor(e(i,j),e(i,j+1)))   %�����ұ߽�
            if n==0
             K(i,j)=255;
            else K(i,j+1)=255;
            end
             n=n+1;
             if n==1;
             a(n)=j;
             else a(n)=j+1;
             end
        end
       if  n==2
             %  t=floor((a(1)+a(2))/2);
             %  d(i,t)=255;
             % n=0;
              %  ��������������Ƶļ������ģ�һ��ʼ�õ������ַ�����
             %  �������Ǿ����󼸺����ıȽϺã���˰�����ע�͵��ˡ�
          for x=a(1):a(2)
              max=I(i,a(1));
             if I(i,x)>max    %������������ԭͼ�����ؼ���ֵ
                 temp=max;
                 max=I(i,x);
                 I(i,x)=temp;
                 b=x;
             end
          end
          d(i,x)=255;
          n=0;
        end
    end
end
%ȥ��ɢ��
for i=2:M-1
    for j=2:N-1
        if d(i,j)==255&&d(i-1,j-1)+d(i-1,j)+d(i-1,j+1)+d(i,j-1)+d(i,j+1)+d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0
            d(i,j)=0;
        end
    end
end
figure;
imshow(d);;
%�Ӷϵ�������Ѱ��������
for i=2:M-1
    for j=2:N-1
        if d(i,j)==255&&(d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0)
            if I(i+1,j-1)>I(i+1,j)&&I(i+1,j-1)>I(i+1,j+1)
                d(i+1,j-1)=255;
            elseif I(i+1,j)>I(i+1,j-1)&&I(i+1,j)>I(i+1,j+1)
                d(i+1,j)=255;
            else d(i+1,j+1)=255;
            end
        end
    end
end
figure;
imshow(d); %��ʾ�ṹ�����Ƶ�������
title('����������������')
%ͼ�����·�ת����������������
d=flipud(d);%��תͼ��
I=flipud(I);
for i=50:M-1        %��Ϊ��Ҫ��Ϊ�˰����Ͻ����ƶϵ㴦����������i��j����1��ʼ�����Լ��ټ�����
    for j=50:N-1
        if d(i,j)==255&&(d(i+1,j-1)+d(i+1,j)+d(i+1,j+1)==0)
            if I(i+1,j-1)>I(i+1,j)&&I(i+1,j-1)>I(i+1,j+1)
                d(i+1,j-1)=255;
            elseif I(i+1,j)>I(i+1,j-1)&&I(i+1,j)>I(i+1,j+1)
                d(i+1,j)=255;
            else d(i+1,j+1)=255;
            end
        end
    end
end
d=flipud(d);
for i=2:M-1          %�����ػ�
    for j=2:N-1
        if d(i,j)==255&&d(i,j+1)==255;
            if I(i,j)>I(i,j+1)
                d(i,j)=255;
                d(i,j+1)=0;
            else d(i,j+1)=255;
                d(i,j)=0;
            end
        end
    end
end
figure;
imshow(d);
title('����õ���������') 
 %figure;
%imshow(d); %��ʾ�ṹ�����Ƶ�������
%title('���º�����������������')