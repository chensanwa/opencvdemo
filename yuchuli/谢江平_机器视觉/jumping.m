function varargout = jumping(varargin)
% JUMPING M-file for jumping.fig
%      JUMPING, by itself, creates a new JUMPING or raises the existing
%      singleton*.
%
%      H = JUMPING returns the handle to a new JUMPING or the handle to
%      the existing singleton*.
%
%      JUMPING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in JUMPING.M with the given input arguments.
%
%      JUMPING('Property','Value',...) creates a new JUMPING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before jumping_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to jumping_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help jumping

% Last Modified by GUIDE v2.5 17-Oct-2009 22:03:01

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @jumping_OpeningFcn, ...
                   'gui_OutputFcn',  @jumping_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before jumping is made visible.
function jumping_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to jumping (see VARARGIN)

% Choose default command line output for jumping
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes jumping wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = jumping_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%������
 %��
 clear;
I=imread('001.jpg'); 
%��ɫͼ��תΪ�Ҷ�ͼ��
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

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%
%�����任
I=imread('001.jpg');
a=isgray(I);
b=isrgb(I);
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
imshow(uint8(J));        %��ʾ�Ҷ�ͼ��
J=double(J);
[M,N]=size(J);
for i=1:M
  for j=1:N
     J(i,j)=38*log(1+J(i,j));%�ڹ�ʽs=c*log��1+r���У���Cֵ������ͼ�����
    end

end
figure();
imshow(uint8(J));           %��ʾ�����任���ͼ��
title('�����任');



% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%������
%�ֶ����Ա任���Ҷ��и
 
I=imread('001.jpg');
a=isgray(I);
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
    if J(i,j)<100                   %�Ҷ�С��100�����أ��ҶȲ���
        J(i,j)=0;
    elseif J(i,j)>100&&J(i,j)<200   %�ҶȽ���50��200֮��ģ���Ҷȵ���150
        J(i,j)=150;
    else J(i,j)=J(i,j);            %�Ҷȴ���200�����أ��Ҷ�ֵ����
    end
  end
end
figure(2);
imshow(uint8(J));
title('�Ҷ��и�')

% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 %��ֵ�˲�
H=imread('001.jpg'); 
a=isgray(H)
b=isrgb(H)                     %��ɫͼ��ת�Ҷ�ͼ��
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
title('�Ҷ�ͼ��')
J=double(J);
[M,N]=size(J);  %��ֵ�˲�
for i=2:M-1;
    for j=2:N-1; 
        K(i,j)=1/8*(J(i-1,j-1)+J(i-1,j)+J(i-1,j+1)+J(i,j-1)+J(i,j)+J(i,j+1)+J(i+1,j-1)+J(i+1,j)+J(i+1,j+1));
    end
end
figure(2);
imshow(uint8(K));
title('��ֵ�˲����')
% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%��ֵ�˲�
H=imread('salt&pepper.tif');  %��ȡ����˽���������ͼ��
a=isgray(H)
b=isrgb(H)                     %��ɫͼ��ת�Ҷ�ͼ��
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
title('����˽���������ͼ��')
I=double(J);             %��ֵ�˲�
[M,N]=size(I);
a=zeros(1,9);
for i=2:M-1;
    for j=2:N-1;
        a(1)=I(i-1,j-1); %����3*3ģ�� 
        a(2)=I(i-1,j);
        a(3)=I(i-1,j+1);
        a(4)=I(i,j-1);
        a(5)=I(i,j);
        a(6)=I(i,j+1);
        a(7)=I(i+1,j-1);
        a(8)=I(i+1,j);
        a(9)=I(i+1,j+1);
   %3*3ģ��Ԫ��ð������    
       for x=1:8
        for y=(x+1):9
           if a(y)<a(x);
               t=a(x);
               a(x)=a(y);
               a(y)=t;
             end
         end
   end
    %ȡ��ֵa(5��
    k(i,j)= a(5);
    end
end
figure();
imshow(uint8(k));
title('��ֵ�˲����')
 


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%������˹����
H=imread('001.jpg');
a=isgray(H)
b=isrgb(H)                     %��ɫͼ��ת�Ҷ�ͼ��
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
title('�Ҷ�ͼ��')         %��ʾԭͼ��
I=double(J);
[M,N]=size(I);
a=zeros(1,9);
for i=2:M-1;
    for j=2:N-1;
        a(1)=I(i-1,j-1); %����3*3ģ�顾0,-1,0;-1,4,-1,0,-1,0��
        a(2)=I(i-1,j);
        a(3)=I(i-1,j+1);
        a(4)=I(i,j-1);
        a(5)=I(i,j);
        a(6)=I(i,j+1);
        a(7)=I(i+1,j-1);
        a(8)=I(i+1,j);
        a(9)=I(i+1,j+1);
        J(i,j)=(0*a(1)+1*a(2)+0*a(3)+1*a(4)-4*a(5)+1*a(6)+0*a(7)+1*a(8)+0*a(9));
                 if J(i,j)<0
                    J(i,j)=0;
                 elseif J(i,j)>255
                    J(i,j)=255;
                 else  J(i,j)= J(i,j);
                 end
           K(i,j)=I(i,j)-J(i,j);%��˹��Ĥ����Ϊ��������ԭͼ��-��˹����
    end
   
end
figure();            %��ʾ��˹����
imshow(uint8(J));
title('��˹����')
figure();             %��ʾ������ͼ��
imshow(uint8(K));
title('��˹�任���')
% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%ֱ��ͼ���⻯ 
 H=imread('002.jpg'); 
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
          k(s(i,j)+1)=k(s(i,j)+1)+1; %ԭͼ������ܶ� 
    end 
end 
k=k./sum; 
for i=1:256 
    for j=1:i 
        e(i)=e(i)+k(j); %�ۻ��ֲ� 
    end 
end 
for i=1:256 
       e(i)=floor(e(i)*255+0.5); %ӳ���ϵ 
end 
for i=1:M 
    for j=1:N 
        t(i,j)=e(s(i,j)+1); 
    end 
end 
s=uint8(s); 
t=uint8(t); 
figure;
subplot(2,2,1); 
imshow(s); 
title('ԭͼ')
 
subplot(2,2,2); 
imhist(s);
title('ԭͼֱ��ͼ')
 
subplot(2,2,3); 
imshow(t); 
title('ֱ��ͼ���⻯���ͼ��')
  
subplot(2,2,4); 
imhist(t); 
title('ֱ��ͼ���⻯��ͼ���ֱ��ͼ')
 

% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%�ṹ������������
clear;
I=imread('picture3.jpg');
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
title('��ֵͼ��')
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
imshow(d);
title('������õ���������')
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


% --- Executes on button press in pushbutton9.
function pushbutton9_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%��ɫͼת�Ҷ�ͼ 
clear;
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