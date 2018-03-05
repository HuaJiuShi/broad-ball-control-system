#include "image.h"
#include "ov7725.h"

#define START_LINE 0

s16 left[IMG_H]={0};
s16 right[IMG_H]={0};
s16 middle[IMG_H];
float middle_x=0,middle_y=0;
s16 L_M_X=CAMERA_W,L_M_Y=0,R_M_X=0,R_M_Y=0;

s16 start_pix_h;
s16 sum_pix;
s16 increase_pix;
s16 spe_w,spe_h,spe_l,spe_n;
u8 b_flag_l ,b_flag_r ,b_flag_u,b_flag_d;
u8 b_flag_c1 ,b_flag_c2 ,b_flag_c3,b_flag_c4;
u8 b_flag_b;

s16 image_c1_h;
s16 image_c1_w;
s16 image_c2_h;
s16 image_c2_w;
s16 image_c3_h;
s16 image_c3_w;
s16 image_c4_h;
s16 image_c4_w;
s16 image_b_h;
s16 image_b_w;

int ball_x,ball_y;


/*void findborder0(void)   //Ѱ�ұ���
{
    s16 i,j,m,n;
    s16 sum_pix_1,sum_pix_2;
    s16 row=CAMERA_H,cow;            //120��
    u8  Y_flag0=CAMERA_W,Y_flag1=0;          //Y�����Ч������Χ
    s16 n1,n2;
    s16 x1=0,x2=0,y1=0,y2=0;
    s16 flag_w,flag_b;
    s16 b_left[60]={0};
    s16 b_right[60]={0};
    s16 b_start=0,b_end=0,b_time=0,b_l=0,b_r=0;
    u8  grad_d = 0,grad_u = 0;
    float grad_ave_l,grad_ave_r;
    
    
    for(i=0;i<IMG_H;i++)   //ÿ������Ҫ����
    {
      left[i]=0;
      right[i]=0;
      L_M_X=CAMERA_W;
      L_M_Y=0;
      R_M_X=0;
      R_M_Y=0;
    }
    start_pix_h = IMG_H/2-1;
    sum_pix = 0;
    increase_pix = 0;
    spe_w = 0;
    spe_h = 0;
    spe_l = 0;
    spe_n = 0;
    x1 = IMG_W/2;
    x2 = IMG_W/2;
    y1 = IMG_W/2;
    y2 = IMG_W/2;

    //�������ҡ��������󡢴������¡���������
    for(row=0;row<IMG_H;row++)    //��������
    {
        for(i=2;i<IMG_W-2;i++)
        {
           if(img_ready[row][i]==0&&img_ready[row][i+1])       
              break;
        }
        left[row]=i;
        if(left[row] == IMG_W-2)
          left[row] = 0;
        
        for(i=IMG_W-2;i>2;i--)    //X�ᣨ160�У����еĵ㶼����
        {
           if(img_ready[row][i-1]&&img_ready[row][i]==0)    
              break;
        }
        right[row]=i;
        if(right[row] == 2)
          right[row] = 0;
    }
  
    grad_ave_l = (left[IMG_H/2+4] - left[IMG_H/2-4])/9.0;
    grad_ave_r = (right[IMG_H/2+4] - right[IMG_H/2-4])/9.0;
    
    for(row=0;row<IMG_H/2;row++)
    {
      if(left[row]-(left[IMG_H/2]+grad_ave_l*(IMG_H/2-row))<=3 && left[row]-(left[IMG_H/2]+grad_ave_l*(IMG_H/2-row))>=-3)  //�ж�Ϊ���½ǵ�
      {
        image_c3_h = row;
        image_c3_w = left[row];
        break;
      }
    }
    for(row=IMG_H;row>IMG_H/2;row--)
    {
      if(left[row]-(left[IMG_H/2]+grad_ave_l*(IMG_H/2-row))<=3 && left[row]-(left[IMG_H/2]+grad_ave_l*(IMG_H/2-row))>=-3)  //�ж�Ϊ���Ͻǵ�
      {
        image_c1_h = row;
        image_c1_w = left[row];
        break;
      }
    }
    for(row=0;row<IMG_H/2;row++)
    {
      if(right[row]-(right[IMG_H/2]+grad_ave_l*(IMG_H/2-row))<=3 && right[row]-(right[IMG_H/2]+grad_ave_l*(IMG_H/2-row))>=-3)  //�ж�Ϊ���½ǵ�
      {
        image_c4_h = row;
        image_c4_w = right[row];
        break;
      }
    }
    for(row=IMG_H;row>IMG_H/2;row--)
    {
      if(right[row]-(right[IMG_H/2]+grad_ave_l*(IMG_H/2-row))<=3 && right[row]-(right[IMG_H/2]+grad_ave_l*(IMG_H/2-row))>=-3)  //�ж�Ϊ���Ͻǵ�
      {
        image_c2_h = row;
        image_c2_w = right[row];
        break;
      }
    }
}
    */


void findframe(void)//�߿��⣬���߽��ĸ��㡣
{
  int i,j,sum1,sum2,sum3,sum4;
  for(sum1=0;sum1<60;sum1++)
    for(i=0;i<=sum1;i++)
    {
      if(!(img_ready[i][sum1-i]))
      {
        image_c3_h =sum1-i;
        image_c3_w =i;
        sum1=60;
        i=60;
      }
    }
  for(sum2=59;sum2>=0;sum2--)
    for(i=59;i>=sum2;i--)
    {
      if(!(img_ready[i][i-sum2]))
      {
        image_c1_h =i-sum2;
        image_c1_w =i;
        sum2=-1;
        i=-1;
      }
    }
  for(sum3=79;sum3>19;sum3--)
    for(j=79;j>=sum3;j--)
    {
      if(!(img_ready[j-sum3][j]))
      {
        image_c4_h =j;
        image_c4_w =j-sum3;
        sum3=19;
        j=19;
      }
    }
  for(sum4=138;sum4>78;sum4--)
    for(i=59;i>=sum4-79;i--)
    {
      if(!(img_ready[i][sum4-i]))
      {
        image_c2_h =sum4-i;
        image_c2_w =i;
        sum4=78;
        i=-1;
      }
    }
}

/*********�������*******/

void ball_pos() //��3*3��������
{
  int x=60;
  int y=80;
  int flag=0;
  int i,j;
  
  for(i=1;(x<120)&&(y<160);i=i+2)
  {
    for(j=0;j<i;j++)
    {
      y++;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x+1][y]+!img_ready[x][y+1]+!img_ready[x][y-1]+!img_ready[x-1][y-1]+!img_ready[x-1][y+1]+!img_ready[x+1][y+1]+!img_ready[x+1][y-1])>5)
        {
          ball_x=x;
          ball_y=y;
          flag=1;
        }
        
          
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i;j++)
    {
      x++;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x+1][y]+!img_ready[x][y+1]+!img_ready[x][y-1]+!img_ready[x-1][y-1]+!img_ready[x-1][y+1]+!img_ready[x+1][y+1]+!img_ready[x+1][y-1])>5)
          {
            ball_x=x;
            ball_y=y;
            flag=1;
          }
        
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i+1;j++)
    {
      y--;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x+1][y]+!img_ready[x][y+1]+!img_ready[x][y-1]+!img_ready[x-1][y-1]+!img_ready[x-1][y+1]+!img_ready[x+1][y+1]+!img_ready[x+1][y-1])>5)
        {
          ball_x=x;
          ball_y=y;
          flag=1;
        }
        
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i+1;j++)
    {
      x--;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x+1][y]+!img_ready[x][y+1]+!img_ready[x][y-1]+!img_ready[x-1][y-1]+!img_ready[x-1][y+1]+!img_ready[x+1][y+1]+!img_ready[x+1][y-1])>5)
        {
          ball_x=x;
          ball_y=y;
          flag=1;
        }
        
      }
      if(flag)
        break;
    }
    if(flag)
        break;
  }
}


/*void ball_pos() //��2*2��������
{
  int x=60;
  int y=80;
  int flag=0;
  int i,j;
  
  for(i=1;(x<120)&&(y<160);i=i+2)
  {
    for(j=0;j<i;j++)
    {
      y++;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x][y+1]+!img_ready[x-1][y])==4)
          ball_x=x;
          ball_y=y;
          flag=1;
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i;j++)
    {
      x++;
      if(!img_ready[x][y])
      {
        if((!img_ready[x+1][y]+!img_ready[x][y+1]+!img_ready[x+1][y+1])==4)
          ball_x=x;
          ball_y=y;
          flag=1;
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i+1;j++)
    {
      y--;
      if(!img_ready[x][y])
      {
        if((!img_ready[x+1][y]+!img_ready[x][y-1]!img_ready[x+1][y+1])==4)
          ball_x=x;
          ball_y=y;
          flag=1;
      }
      if(flag)
        break;
    }
    if(flag)
        break;
    
    for(j=0;j<i+1;j++)
    {
      x--;
      if(!img_ready[x][y])
      {
        if((!img_ready[x-1][y]+!img_ready[x][y+1]+!img_ready[x-1][y-1])==4)
          ball_x=x;
          ball_y=y;
          flag=1;
      }
      if(flag)
        break;
    }
    if(flag)
        break;
  }
}*/

    /*
    //�߽���ȡ��ϣ���ʼ����
    if(x1>image_c1_w) x1=image_c1_w;    //��ʼ�����꣬��С������
    if(x1>image_c3_w) x1=image_c3_w;
    if(x2<image_c2_w) x1=image_c2_w;    //��ֹ�����꣬��������
    if(x2<image_c4_w) x1=image_c4_w;
    
    if(y1>image_c3_h) y1=image_c3_h;    //��ʼ�����꣬��С������
    if(y1>image_c4_h) y1=image_c4_h;
    if(y1<image_c1_h) y1=image_c1_h;
    if(y1<image_c2_h) y1=image_c2_h;
    
    for(row=y1;row<y2;row++)
    {
      for(cow=x1;cow<x2;cow++)
      {
        if(flag_w)
        {
          //flag_w = 2;
          if(img_ready[row][cow-1]&&img_ready[row][cow]==0)     //w-b
          {
            flag_b = 1;
            b_l = cow;
          }
          if(img_ready[row][cow-1]==0&&img_ready[row][cow])     //b-w
          {
            if(flag_b)  //����
            {
              b_r = cow;
              b_start = row;
            }
            else
              break;
          }
        }
        else
        {
          if(img_ready[row][cow-1]==0&&img_ready[row][cow])     //b-w
            flag_w = 1;
        }
      }
      flag_b = 0;
      flag_w = 0;
    }
    
    */



/*
    //����λ���ж�,���е�ɼ�
    middle[IMG_H/2] = IMG_W/2;
    for(row=IMG_H/2;row<IMG_H-1;row++)    //��ʼ����Ѱ�� ���������ұ߽�     
    {
      for(i=middle[row];i<IMG_W-1;i++)    //X������
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //����2����Ϊ�׵��ж�Ϊ�ڱ�
            break;
      }
      left[row]=i;
      for(i=middle[row];i>1;i--)    //X�ᣨ160�У����еĵ㶼����
      {
         if(img_ready[row][i-1]&&img_ready[row][i]==0)       //����������Ϊ�׵��ж�Ϊ����
            break;
      }
      right[row]=i;
      
      middle[row] = (left[row] + right[row])<<1;
    } 
    for(row=IMG_H/2;row>1;row++)    //��ʼ����Ѱ�� ���������ұ߽�     
    {
      for(i=middle[row];i<IMG_W-1;i++)    //X������
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //����2����Ϊ�׵��ж�Ϊ�ڱ�
            break;
      }
      left[row]=i;
      for(i=middle[row];i>1;i--)    //X�ᣨ160�У����еĵ㶼����
      {
         if(img_ready[row][i-1]&&img_ready[row][i]==0)       //����������Ϊ�׵��ж�Ϊ����
            break;
      }
      right[row]=i;
      
      middle[row] = (left[row] + right[row])<<1;
    }
    
    for(i=0;i<59;i++)   //��΢��
    {
      middle_d[i]=middle_d[i+1]-middle_d[i];
    }
    
    //���߲ɼ���ϣ����������Ч��,�������9���е�������ԣ��г弤��Ϊ����ת�۵�Ϊ�α䡢�ǵ�
    for(row=IMG_H/2;row<IMG_H;row++)    //��ʼ���ϼ��    
    {
      if(middle[row]-middle[row-8]-(middle[row-1]-middle[row-9])>2 || middle[row]-middle[row-8]-(middle[row-1]-middle[row-9])<-2)       //�Ǳ�㣬����Ƿ��ǳ弤��ת��
      {
        grad_ave = (middle[row+4]-middle[row-3])/8.0;
      }
    }
    
    
    /*
    //�ݶ���߽� shiyan
    for(i=0;i<20;i++)   //w
    {
      for(n=0;n<15;n++) //h
      {
        for(j=i*4;j<i*4+4;j++)    //w
          for(m=n*4;m<n*4+4;m++)
            sum_pix = sum_pix + img_ready[m][n];
        if(sum_pix >= 5)
        {
          for(j=i*4;j<i*4+4;j++)    //w
            for(m=n*4;m<n*4+4;m++)
              img_ready[m][n] = 1;
        }
        else
        {
          for(j=i*4;j<i*4+4;j++)    //w
            for(m=n*4;m<n*4+4;m++)
              img_ready[m][n] = 0;
        }
      }
      */
    /*
    //�ݶ���߽�
    for(i=0;i<20;i++)   //w
    {
      for(n=0;n<15;n++) //h
      {
        for(j=i*4;j<i*4+4;j++)    //w
          for(m=n*4;m<n*4+4;m++)
            sum_pix = sum_pix + img_ready[m][n];
        grad_pix[i][n] = sum_pix;       //�õ�һ15*20�ĻҶ�ͼ
      }
    }
    for(i=10;i<20;i++)   //w,����1/4����
    {
      for(n=7;n<15;n++) //h
      {
        if(grad_pix[i][n]-grad_pix[i-1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]<-3)
          grad_d++;
        if(grad_d >= 5) //�ݶ�5�����ڼ��٣��ж�Ϊ��Ѱ��������ĵ����
        {
          image_b_h = 4*n+2;
          image_b_w = 4*i+2;
          b_flag_b = 1;
        }
        
        if(grad_pix[i][n]-grad_pix[i-1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]>3)
          grad_u++;
        if(grad_u == 5)
        {
          b_flag_c2 = 1;
          image_c2_h = 4*n+2;
          image_c2_w = 4*i+2;
        }
      }
    }
    
    for(i=10;i<20;i++)   //w����1/4����
    {
      for(n=0;n<7;n++) //h
      {
        if(grad_pix[i][n]-grad_pix[i-1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]<-3)
          grad_d++;
        if(grad_d >= 5) //�ݶ�5�����ڼ��٣��ж�Ϊ��Ѱ��������ĵ����
        {
          image_b_h = 4*n+2;
          image_b_w = 4*i+2;
          b_flag_b = 1;
        }
        
        if(grad_pix[i][n]-grad_pix[i-1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]>3)
          grad_u++;
        if(grad_u == 5)
        {
          b_flag_c4 = 1;
          image_c4_h = 4*n+2;
          image_c4_w = 4*i+2;
        }
      }
    }
    
    for(i=0;i<10;i++)   //w������1/4����
    {
      for(n=7;n<15;n++) //h
      {
        if(grad_pix[i][n]-grad_pix[i-1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]<-3)
          grad_d++;
        if(grad_d >= 5) //�ݶ�5�����ڼ��٣��ж�Ϊ��Ѱ��������ĵ����
        {
          image_b_h = 4*n+2;
          image_b_w = 4*i+2;
          b_flag_b = 1;
        }
        
        if(grad_pix[i][n]-grad_pix[i-1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]>3)
          grad_u++;
        if(grad_u == 5)
        {
          b_flag_c1 = 1;
          image_c1_h = 4*n+2;
          image_c1_w = 4*i+2;
        }
      }
    }
    
    for(i=0;i<10;i++)   //w������1/4����
    {
      for(n=0;n<7;n++) //h
      {
        if(grad_pix[i][n]-grad_pix[i-1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]<-3)
          grad_d++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]<-3)
          grad_d++;
        if(grad_d >= 5) //�ݶ�5�����ڼ��٣��ж�Ϊ��Ѱ��������ĵ����
        {
          image_b_h = 4*n+2;
          image_b_w = 4*i+2;
          b_flag_b = 1;
        }
        
        if(grad_pix[i][n]-grad_pix[i-1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i-1][n-1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n+1]>3)
          grad_u++;
        if(grad_pix[i][n]-grad_pix[i+1][n-1]>3)
          grad_u++;
        if(grad_u == 5)
        {
          b_flag_c3 = 1;
          image_c3_h = 4*n+2;
          image_c3_w = 4*i+2;
        }
      }
    }
   */


    /*
    //��ʼѰ�Ҿ��α߿�
    for(row=IMG_H/2;row<IMG_H;row++)    //��ʼ����Ѱ�� ���������ұ߽�     
    {
      for(i=IMG_W/2;i<IMG_W;i++)    //X������
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //����5����Ϊ�׵��ж�Ϊ����
            break;
      }
      left[row]=i;
      for(i=IMG_W/2;i>0;i--)    //X�ᣨ160�У����еĵ㶼����
      {
         if(img_ready[row][i-1]&&img_ready[row][i]==0)       //����������Ϊ�׵��ж�Ϊ����
            break;
      }
      right[row]=i;
      
      if(IMG_H/2 - row>=3)
      {
        if(left[row]-left[row-2]>4 && left[row]-left[row-2]<-4) //������ų�����ȱʧ�����ת��,��֤�룬xyխ�����صĺ�
        {
          for(m=row-4;m<row+5;m++)
            for(n=left[row]-1;n<left[row]+2;n++)
              sum_pix_1 = sum_pix_1 + img_ready[m][n];  //y��
          for(m=row-1;m<row+2;m++)
            for(n=left[row]-4;n<left[row]+5;n++)
              sum_pix_2 = sum_pix_2 + img_ready[m][n];  //x��
          for(m=row-1;m<row+2;m++)
            for(n=left[row]-1;n<left[row]+2;n++)
              sum_pix = sum_pix + img_ready[m][n];  //x��
          if(sum_pix_1 - sum_pix < 5 && sum_pix_2 - sum_pix < 5)    //��������
          {
            
          }
          else if(sum_pix_1-sum_pix_2<6 && sum_pix_2-sum_pix_1<6)    //�ж�Ϊ�ǵ�
          {
          
          }
          else
          {
          }
        }
        if(right[row]-right[row-2]>4 && right[row]-right[row-2]<-4) //������ų�����ȱʧ�����ת��
        {
          
        }
      }
    }

    //������ֵ�ж�
    for(row=start_pix_h;row>0;row--)    //��ʼ������Ѱ��
    {
       for(i=row;i <= 79-row;i++)
           sum_pix = sum_pix + img_ready[i][row-10] + img_ready[i][69-row];
       for(i=row-9;i <= 68-row;i++)
           sum_pix = sum_pix + img_ready[row][i] + img_ready[79-row][i];
    }
    
    //��ֵ�˲�+��Ե���
    for(row=IMG_H/2;row<IMG_H-1;row++)    //��ʼ����Ѱ��
    {
      for(i=IMG_W/2;i<IMG_W;i++)    //X������
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //����5����Ϊ�׵��ж�Ϊ����
            break;
      }
      //�ȴӺ����˲�
      for(i=IMG_W/2;i<IMG_W;i++)
      {
        for(j=0;j<=3;j++)
          sum_pix = sum_pix + img_ready[28+j][i] + img_ready[28+j][i+1] + img_ready[28+j][i+2] + img_ready[28+j][i+3];
        if(sum_pix >= 5)  //������⵽���߻����
        {
          for(j=0;j<=3;j++)
            sum_pix = sum_pix + img_ready[28+j][i] + img_ready[28+j][i+1] + img_ready[28+j][i+2] + img_ready[28+j][i+3];
        }
        sum_pix = 0;
      }
      
    }
    */
        /*
    for(row=0;row<IMG_H;row++)
    {
      if(left[row] != 0)
      {
        if(left[row] < IMG_W<<1)
        {
          if(left[row+2]-left[row]>=3 && left[row+2]-left[row]<=-3)  //�ж�Ϊ���½ǵ�
          {
            image_c3_h = row;
            image_c3_w = left[row];
            break;
          }
        }
        else
        {
          if(left[row+2]-left[row]-(left[row+3]-left[row+1])>=3 && left[row+2]-left[row]-(left[row+3]-left[row+1])<=-3)
          {
            image_c3_h = row;
            image_c3_w = left[row];
            break;
          }
        }
      }
    }
    for(row=0;row<IMG_H;row++)
    {
      if(left[row] != 0)
      {
        if(left[row] < IMG_W<<1)
        {
          if(left[row+2]-left[row]>=3 && left[row+2]-left[row]<=-3)  //�ж�Ϊ���½ǵ�
          {
            image_c3_h = row;
            image_c3_w = left[row];
            break;
          }
        }
        else
        {
          if(left[row+2]-left[row]-(left[row+3]-left[row+1])>=3 && left[row+2]-left[row]-(left[row+3]-left[row+1])<=-3)
          {
            image_c3_h = row;
            image_c3_w = left[row];
            break;
          }
        }
      }
    }
    
    
    for(row=0;row<IMG_H;row++)
    {
      if(left[row] != 0)
      {
        if(left[row+2]-left[row]>=3 && left[row+2]-left[row]<=-3)  //�ж�Ϊ���Ͻǵ�
        {
          image_c3_h = row;
          image_c3_w = left[row];
          break;
        }
      }
    }
    for(row=0;row<IMG_H;row++)
    {
      if(left[row] != 0)
      {
        if(left[row+2]-left[row]>=3 && left[row+2]-left[row]<=-3)  //�ж�Ϊ���½ǵ�
        {
          image_c3_h = row;
          image_c3_w = left[row];
          break;
        }
      }
    }
    for(row=0;row<IMG_H;row++)
    {
      if(left[row] != 0)
      {
        if(left[row+2]-left[row]>=3 && left[row+2]-left[row]<=-3)  //�ж�Ϊ���Ͻǵ�
        {
          image_c3_h = row;
          image_c3_w = left[row];
          break;
        }
      }
    }
    */
    

