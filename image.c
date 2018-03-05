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


void findframe(void)//边框检测，检测边界四个点。
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

/*********检测球心*******/

void ball_pos() //以3*3矩阵检测球
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

