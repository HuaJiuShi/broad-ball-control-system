#include "Ball_control.h"

int iError_x=0,lastError_x=0,PrevError_x=0,x_set=0;
float dux=0,ux1=0,ux=0;
float Kp_x,Ki_x,Kd_x;
float Kp_y,Ki_y,Kd_y;
int iError_y=0,lastError_y=0,PrevError_y=0,y_set=0;
float duy=0,uy1=0,uy=0;
float uy_min,uy_max,ux_min,ux_max;

ball_locate_Typedef   ball_locate;
steering_duty_Typedef steering_duty;
ball_band_sys_Typedef ball_band;
steer_x_pid_Typedef   steer_x_pid;
steer_y_pid_Typedef   steer_y_pid;
steer_flag_Typedef    steer_flag;
ball_relay_sys_Typedef  ball_relay;

void update_data(void)
{
	ball_band.pre_x = ball_band.last_x;
	ball_band.pre_y = ball_band.last_y;
	ball_band.last_x = camsize_xu;
	ball_band.last_y = camsize_yu;
}

void calculate_parameter(void)
{
	ball_band.dis_x = ball_band.last_x - ball_band.aim_x;
	ball_band.dis_y = ball_band.last_y - ball_band.aim_y;
	ball_band.speed_x = ball_band.last_x - ball_band.pre_x;
	ball_band.speed_y = ball_band.last_y - ball_band.pre_y;
}

void ball_pid_init(void)
{
	Kp_x = 0.2;Ki_x = 0;Kd_x = 0.7;
	Kp_y = 0.2;Ki_y = 0;Kd_y = 0.5;
	x_set = ball_locate.area9_x;
	y_set = ball_locate.area9_y;
}

void ball_locate_init(void)
{
	ball_locate.area1_x = 45;
	ball_locate.area1_y = 95;
	ball_locate.area2_x = 80;
	ball_locate.area2_y = 95;
	ball_locate.area3_x = 115;
	ball_locate.area3_y = 95;
	ball_locate.area4_x = 45;
	ball_locate.area4_y = 60;
	ball_locate.area5_x = 80; //77
	ball_locate.area5_y = 60;
	ball_locate.area6_x = 115;
	ball_locate.area6_y = 60;
	ball_locate.area7_x = 45;
	ball_locate.area7_y = 25;
	ball_locate.area8_x = 80;
	ball_locate.area8_y = 25;
	ball_locate.area9_x = 115;
	ball_locate.area9_y = 25;
	ball_locate.change_x = 60;
	ball_locate.change_y = 45;
	
	ball_locate.change151_x = 55;
	ball_locate.change151_y = 85;
	ball_locate.change152_x = 65;
	ball_locate.change152_y = 75;
	
	ball_locate.change141_x = 45;
	ball_locate.change141_y = 85;
	ball_locate.change142_x = 45;
	ball_locate.change142_y = 75;
	ball_locate.change451_x = 55;
	ball_locate.change451_y = 60;
	ball_locate.change452_x = 65;
	ball_locate.change452_y = 60;
	
	ball_locate.change121_x = 55;
	ball_locate.change121_y = 105;
	ball_locate.change122_x = 65;
	ball_locate.change122_y = 100;
	ball_locate.change261_x = 92;
	ball_locate.change261_y = 85;
	ball_locate.change262_x = 102;
	ball_locate.change262_y = 75;
	ball_locate.change691_x = 98;
	ball_locate.change691_y = 42;
	
	ball_locate.change191_x = 54;
	ball_locate.change191_y = 86;
	ball_locate.change192_x = 63;
	ball_locate.change192_y = 80;
	ball_locate.change193_x = 63;
	ball_locate.change193_y = 65;
	ball_locate.change194_x = 63;
	ball_locate.change194_y = 54;
	ball_locate.change195_x = 63;
	ball_locate.change195_y = 42;
	ball_locate.change196_x = 75;
	ball_locate.change196_y = 42;
	ball_locate.change197_x = 86;
	ball_locate.change197_y = 42;
	ball_locate.change198_x = 98;
	ball_locate.change198_y = 34;
	ball_locate.change199_x = 101;
	ball_locate.change199_y = 34;
	ball_locate.change1910_x = 98;
	ball_locate.change1910_y = 77;
	ball_locate.change1911_x = 98;
	ball_locate.change1911_y = 65;
	ball_locate.change1912_x = 98;
	ball_locate.change1912_y = 54;
	
	ball_locate.changeo1_x = 66;
	ball_locate.changeo1_y = 52;
	ball_locate.changeo2_x = 90;
	ball_locate.changeo2_y = 51;
	ball_locate.changeo3_x = 92;
	ball_locate.changeo3_y = 75;
	ball_locate.changeo4_x = 66;
	ball_locate.changeo4_y = 75;
	
	ball_locate.changes9_x = 104;
	ball_locate.changes9_y = 34;
}


void num1_control_init(void)
{
	Kp_x = 0.08;Ki_x = 0;Kd_x = 0.3;
	Kp_y = 0.08;Ki_y = 0;Kd_y = 0.3;
	x_set = ball_locate.area2_x-3;
	y_set = ball_locate.area2_y+1;
}

void num2_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.11;Ki_y = 0;Kd_y = 0.7;
	x_set = ball_locate.change151_x;
	y_set = ball_locate.change151_y;
	//x_set = ball_locate.area5_x-3;
	//y_set = ball_locate.area5_y;
}

void num3_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.12;Ki_y = 0;Kd_y = 0.6;
	x_set = ball_locate.change141_x;
	y_set = ball_locate.change141_y;
	steer_flag.tt_flag = 0;
}

void num4_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.12;Ki_y = 0;Kd_y = 0.6;
	x_set = ball_locate.change191_x;
	y_set = ball_locate.change191_y;
}

void num5_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.12;Ki_y = 0;Kd_y = 0.6;
	x_set = ball_locate.change121_x;
	y_set = ball_locate.change121_y;
}

void num6_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.12;Ki_y = 0;Kd_y = 0.6;
	x_set = ball_locate.area2_x;
	y_set = ball_locate.area2_y;
}

void num7_control_init(void)
{
	Kp_x = 0.14;Ki_x = 0;Kd_x = 0.6;
	Kp_y = 0.12;Ki_y = 0;Kd_y = 0.6;
	steer_flag.flag_o1 = 1;
	steer_flag.flag_o2 = 0;
	steer_flag.flag_o3 = 0;
	steer_flag.flag_o4 = 0;
	steer_flag.flag_o1_ok = 0;
	steer_flag.flag_o2_ok = 0;
	steer_flag.flag_o3_ok = 0;
	steer_flag.flag_o4_ok = 0;
	steer_flag.flag_times = 0;
	steer_flag.flag_a9 = 0;
	x_set = ball_locate.changeo1_x;
	y_set = ball_locate.changeo1_y;
}


void ball_control_init(void)
{
	ball_locate_init();
	ball_pid_init();
	
	steering_duty.x_max = 0.050;
	steering_duty.x_min = 0.035;	//测定
	steering_duty.x_middle = 0.043;
	
	steering_duty.y_max = 0.08;	//测定
	steering_duty.y_min = 0.058;
	steering_duty.y_middle = 0.068;
}


void ball_pid_set(unsigned int seg)
{
	switch (seg)
	{
		case 11:Kd_x = 0.6;  //确定0.55
				Ki_x = 0;
				Kp_x = 0.2; 
				break;
		case 12:Kd_x = 0.6;
				Ki_x = 0;
				Kp_x = 0.2; 
				break;
		case 13:Kd_x = 0.4;
				Ki_x = 0;
				Kp_x = 0.15; 
				break;
		case 14:Kd_x = 0.3;
				Ki_x = 0;
				Kp_x = 0.12; 
				break;
		case 15: break;
		case 16: break;
		case 17: break;
		case 18: break;
		case 19: break;
		case 21:Kd_y = 0.5;
				Ki_y = 0;
				Kp_y = 0.2; 
				break;
		case 22:Kd_y = 0.5;
				Ki_y = 0;
				Kp_y = 0.2; 
				break;
		case 23:Kd_y = 0.5;
				Ki_y = 0;
				Kp_y = 0.2; 
				break;
		case 24:Kd_y = 0.5;
				Ki_y = 0;
				Kp_y = 0.2; 
				break;
		case 25: break;
		case 26: break;
		case 27: break;
		case 28: break;
		case 29: break;
		default : break;
	}
}

//增量式PID
float PID_x(float x)        //pid偏差计算
{
    iError_x=x_set-x;		 //误差=设定值-实际值
    dux=(Kp_x*(iError_x-lastError_x)+Ki_x*iError_x
			+Kd_x*(iError_x-2*lastError_x+PrevError_x));
    ux=ux1+dux;	
    ux1=ux;				  //变量值移位
    PrevError_x=lastError_x;
    lastError_x=iError_x;
    if(ux>20)
      ux=20;
    else if(ux<-40)
      ux=-40;
    return ux;
}
float PID_y(float y)        //pid偏差计算
{
    iError_y=y_set-y;		 //误差=设定值-实际值
    duy=(Kp_y*(iError_y-lastError_y)+Ki_y*iError_y
			+Kd_y*(iError_y-2*lastError_y+PrevError_y));     
    uy=uy1+duy;	
    uy1=uy;				  //变量值移位
    PrevError_y=lastError_y;
    lastError_y=iError_y;
    if(uy>50)
      uy=50;
    else if(uy<-50)
      uy=-50;
    return uy;
}

void pid_control(void)
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	x_steering(steer_x_pid.Duty);
	//x_steering(steering_duty.x_middle);
	y_steering(steer_y_pid.Duty);
	//y_steering(steering_duty.y_middle);
}

//控制算法采用插值的方法，减小速度，在边缘点处强行降速
void num1_control(void)
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}

void num2_control(void) //1-5
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	if((ball_band.last_x - ball_locate.change151_x <=5 && ball_band.last_x - ball_locate.change151_x >= -5) && 
		(ball_band.last_y - ball_locate.change151_y <= 5 && ball_band.last_y - ball_locate.change151_y >=-5))
	{
		x_set = ball_locate.change152_x;
		y_set = ball_locate.change152_y;
	}
	if((ball_band.last_x - ball_locate.change152_x <=5 && ball_band.last_x - ball_locate.change152_x >= -5) && 
		(ball_band.last_y - ball_locate.change152_y <= 5 && ball_band.last_y - ball_locate.change152_y >=-5))
	{
		x_set = ball_locate.area5_x-5;
		y_set = ball_locate.area5_y+5;
	}
	if((ball_band.last_x - ball_locate.area5_x <=5 && ball_band.last_x - ball_locate.area5_x >= -5) && 
		(ball_band.last_y - ball_locate.area5_x <= 5 && ball_band.last_y - ball_locate.area5_x >=-5))
	{
		x_set = ball_locate.area5_x-5;    //确定补偿
		y_set = ball_locate.area5_y+4;
	}
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}

void num3_control(void)	//1-4-5
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	if(!steer_flag.t_flag)
	{
		if((ball_band.last_x - ball_locate.change141_x <=5 && ball_band.last_x - ball_locate.change141_x >= -5) && 
			(ball_band.last_y - ball_locate.change141_y <= 5 && ball_band.last_y - ball_locate.change141_y >=-5))
		{
			x_set = ball_locate.change142_x;
			y_set = ball_locate.change142_y;
		}
		if((ball_band.last_x - ball_locate.change142_x <=5 && ball_band.last_x - ball_locate.change142_x >= -5) && 
			(ball_band.last_y - ball_locate.change142_y <= 5 && ball_band.last_y - ball_locate.change142_y >=-5))
		{
			x_set = ball_locate.area4_x - 8;
			y_set = ball_locate.area4_y + 5;
		}
		if((ball_band.last_x - ball_locate.area4_x <=5 && ball_band.last_x - ball_locate.area4_x >= -5) && 
			(ball_band.last_y - ball_locate.area4_x <= 5 && ball_band.last_y - ball_locate.area4_x >=-5))
		{
			x_set = ball_locate.area4_x - 8;
			y_set = ball_locate.area4_y + 5;
		}
	}

	//定时两秒部分

	if((ball_band.last_x - ball_locate.area4_x <=3 && ball_band.last_x - ball_locate.area4_x >= -3) && 
	(ball_band.last_y - ball_locate.area4_y <= 3 && ball_band.last_y - ball_locate.area4_y >=-3))
	{
		steer_flag.t_flag++;
	}
	else
	{
		steer_flag.t_flag = 0;
	}
	
	if(steer_flag.t_flag >= 100)
	{
		x_set = ball_locate.change451_x;
		y_set = ball_locate.change451_y;
		steer_flag.tt_flag = 1;
	}
	
	if(steer_flag.tt_flag)
	{
		if((ball_band.last_x - ball_locate.change451_x <=5 && ball_band.last_x - ball_locate.change451_x >= -5) && 
			(ball_band.last_y - ball_locate.change451_y <= 5 && ball_band.last_y - ball_locate.change451_y >=-5))
		{
			x_set = ball_locate.change452_x;
			y_set = ball_locate.change452_y;
		}
		if((ball_band.last_x - ball_locate.change452_x <=5 && ball_band.last_x - ball_locate.change452_x >= -5) && 
			(ball_band.last_y - ball_locate.change452_y <= 5 && ball_band.last_y - ball_locate.change452_y >=-5))
		{
			x_set = ball_locate.area5_x;
			y_set = ball_locate.area5_y;
		}
		if((ball_band.last_x - ball_locate.area5_x <=5 && ball_band.last_x - ball_locate.area5_x >= -5) && 
			(ball_band.last_y - ball_locate.area5_y <= 5 && ball_band.last_y - ball_locate.area5_y >=-5))
		{
			x_set = ball_locate.area5_x;
			y_set = ball_locate.area5_x;
		}
	}
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}

void num4_control(void)
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	if((ball_band.last_x - ball_locate.change191_x <=4 && ball_band.last_x - ball_locate.change191_x >= -4) && 
		(ball_band.last_y - ball_locate.change191_y <= 4 && ball_band.last_y - ball_locate.change191_y >=-4))
	{
		x_set = ball_locate.change192_x;
		y_set = ball_locate.change192_y;
	}
	if((ball_band.last_x - ball_locate.change192_x <=4 && ball_band.last_x - ball_locate.change192_x >= -4) && 
		(ball_band.last_y - ball_locate.change192_y <= 4 && ball_band.last_y - ball_locate.change192_y >=-4))
	{
		x_set = ball_locate.change193_x;
		y_set = ball_locate.change193_y;
	}
	if((ball_band.last_x - ball_locate.change193_x <=5 && ball_band.last_x - ball_locate.change193_x >= -5) && 
		(ball_band.last_y - ball_locate.change193_y <= 5 && ball_band.last_y - ball_locate.change193_y >=-5))
	{
		x_set = ball_locate.change194_x;
		y_set = ball_locate.change194_y;
	}
	if((ball_band.last_x - ball_locate.change194_x <=5 && ball_band.last_x - ball_locate.change194_x >= -5) && 
		(ball_band.last_y - ball_locate.change194_y <= 5 && ball_band.last_y - ball_locate.change194_y >=-5))
	{
		x_set = ball_locate.change195_x;
		y_set = ball_locate.change195_y;
	}
	if((ball_band.last_x - ball_locate.change195_x <=5 && ball_band.last_x - ball_locate.change195_x >= -5) && 
		(ball_band.last_y - ball_locate.change195_y <= 5 && ball_band.last_y - ball_locate.change195_y >=-5))
	{
		x_set = ball_locate.change196_x;
		y_set = ball_locate.change196_y;
	}
	if((ball_band.last_x - ball_locate.change196_x <=5 && ball_band.last_x - ball_locate.change196_x >= -5) && 
		(ball_band.last_y - ball_locate.change196_y <= 5 && ball_band.last_y - ball_locate.change196_y >=-5))
	{
		x_set = ball_locate.change197_x;
		y_set = ball_locate.change197_y;
	}
	if((ball_band.last_x - ball_locate.change197_x <=5 && ball_band.last_x - ball_locate.change197_x >= -5) && 
		(ball_band.last_y - ball_locate.change197_y <= 5 && ball_band.last_y - ball_locate.change197_y >=-5))
	{
		x_set = ball_locate.change198_x;
		y_set = ball_locate.change198_y;
	}
	if((ball_band.last_x - ball_locate.change198_x <=4 && ball_band.last_x - ball_locate.change198_x >= -4) && 
		(ball_band.last_y - ball_locate.change198_y <= 4 && ball_band.last_y - ball_locate.change198_y >=-4))
	{
		x_set = ball_locate.change199_x;
		y_set = ball_locate.change199_y;
	}
	if((ball_band.last_x - ball_locate.change199_x <=5 && ball_band.last_x - ball_locate.change199_x >= -5) && 
		(ball_band.last_y - ball_locate.change199_x <= 5 && ball_band.last_y - ball_locate.change199_x >=-5))
	{
		x_set = ball_locate.area9_x;
		y_set = ball_locate.area9_y+6;
	}
	if((ball_band.last_x - ball_locate.area9_x <=10 && ball_band.last_x - ball_locate.area9_x >= -10) && 
		(ball_band.last_y - ball_locate.area9_y <= 10 && ball_band.last_y - ball_locate.area9_y >=-10))
	{
		x_set = ball_locate.area9_x;
		y_set = ball_locate.area9_y+6;
	}
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}

void num5_control(void)
{
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	if((ball_band.last_x - ball_locate.change121_x <=4 && ball_band.last_x - ball_locate.change121_x >= -4) && 
		(ball_band.last_y - ball_locate.change121_y <= 4 && ball_band.last_y - ball_locate.change121_y >=-4))
	{
		x_set = ball_locate.change122_x;
		y_set = ball_locate.change122_y;
	}
	if((ball_band.last_x - ball_locate.change122_x <=4 && ball_band.last_x - ball_locate.change122_x >= -4) && 
		(ball_band.last_y - ball_locate.change122_y <= 4 && ball_band.last_y - ball_locate.change122_y >=-4))
	{
		x_set = ball_locate.area2_x;
		y_set = ball_locate.area2_y;
	}
	if((ball_band.last_x - ball_locate.area2_x <=3 && ball_band.last_x - ball_locate.area2_x >= -3) && 
		(ball_band.last_y - ball_locate.area2_y <= 3 && ball_band.last_y - ball_locate.area2_y >=-3))
	{
		x_set = ball_locate.area2_x;
		y_set = ball_locate.area2_y;
	}
	if((ball_band.last_x - ball_locate.change261_x <=4 && ball_band.last_x - ball_locate.change261_x >= -4) && 
		(ball_band.last_y - ball_locate.change261_y <= 4 && ball_band.last_y - ball_locate.change261_y >=-4))
	{
		x_set = ball_locate.change262_x;
		y_set = ball_locate.change262_y;
	}
	if((ball_band.last_x - ball_locate.change262_x <=4 && ball_band.last_x - ball_locate.change262_x >= -4) && 
		(ball_band.last_y - ball_locate.change262_y <= 4 && ball_band.last_y - ball_locate.change262_y >=-4))
	{
		x_set = ball_locate.area6_x;
		y_set = ball_locate.area6_y;
	}
	if((ball_band.last_x - ball_locate.area6_x <=3 && ball_band.last_x - ball_locate.area6_x >= -3) && 
		(ball_band.last_y - ball_locate.area6_x <= 3 && ball_band.last_y - ball_locate.area6_x >=-3))
	{
		x_set = ball_locate.change691_x;
		y_set = ball_locate.change691_y;
	}
	if((ball_band.last_x - ball_locate.area9_x <=10 && ball_band.last_x - ball_locate.area9_x >= -10) && 
		(ball_band.last_y - ball_locate.area9_y <= 10 && ball_band.last_y - ball_locate.area9_y >=-10))
	{
		x_set = ball_locate.area9_x;
		y_set = ball_locate.area9_y+6;
	}
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}

void num6_control(void)
{
	
}


void num7_control(void)	//画圈题
{
	if(steer_flag.flag_times <= 4)
	{
		if(steer_flag.flag_o1)
		{
			x_set = ball_locate.changeo1_x;
			y_set = ball_locate.changeo1_y;
			if((ball_band.last_x - ball_locate.changeo1_x <=5 && ball_band.last_x - ball_locate.changeo1_x >= -5) && 
			(ball_band.last_y - ball_locate.changeo1_y <= 5 && ball_band.last_y - ball_locate.changeo1_y >=-5))
			{
				steer_flag.flag_o1_ok++;
			}
			else
			{
				steer_flag.flag_o1_ok = 0;
			}
			if(steer_flag.flag_o1_ok >= 100)
			{
				steer_flag.flag_o1_ok = 0;
				x_set = ball_locate.changeo2_x;
				y_set = ball_locate.changeo2_y;
				steer_flag.flag_o2 = 1;
				steer_flag.flag_o1 = 0;
				steer_flag.flag_times++;
			}
		}
		if(steer_flag.flag_o2)
		{
			x_set = ball_locate.changeo2_x;
			y_set = ball_locate.changeo2_y;
			if((ball_band.last_x - ball_locate.changeo2_x <=5 && ball_band.last_x - ball_locate.changeo2_x >= -5) && 
			(ball_band.last_y - ball_locate.changeo2_y <= 5 && ball_band.last_y - ball_locate.changeo2_y >=-5))
			{
				steer_flag.flag_o2_ok++;
			}
			else
			{
				steer_flag.flag_o2_ok = 0;
			}
			if(steer_flag.flag_o2_ok >= 100)
			{
				steer_flag.flag_o2_ok = 0;
				x_set = ball_locate.changeo3_x;
				y_set = ball_locate.changeo3_y;
				steer_flag.flag_o3 = 1;
				steer_flag.flag_o2 = 0;
			}
		}
		if(steer_flag.flag_o3)
		{
			x_set = ball_locate.changeo3_x;
			y_set = ball_locate.changeo3_y;
			if((ball_band.last_x - ball_locate.changeo3_x <=5 && ball_band.last_x - ball_locate.changeo3_x >= -5) && 
			(ball_band.last_y - ball_locate.changeo3_y <= 5 && ball_band.last_y - ball_locate.changeo3_y >=-5))
			{
				steer_flag.flag_o3_ok++;
			}
			else
			{
				steer_flag.flag_o3_ok = 0;
			}
			if(steer_flag.flag_o3_ok >= 100)
			{
				steer_flag.flag_o3_ok = 0;
				x_set = ball_locate.changeo4_x;
				y_set = ball_locate.changeo4_y;
				steer_flag.flag_o4 = 1;
				steer_flag.flag_o3 = 0;
			}
		}
		if(steer_flag.flag_o4)
		{
			x_set = ball_locate.changeo4_x;
			y_set = ball_locate.changeo4_y;
			if((ball_band.last_x - ball_locate.changeo4_x <=5 && ball_band.last_x - ball_locate.changeo4_x >= -5) && 
			(ball_band.last_y - ball_locate.changeo4_y <= 5 && ball_band.last_y - ball_locate.changeo4_y >=-5))
			{
				steer_flag.flag_o4_ok++;
			}
			else
			{
				steer_flag.flag_o4_ok = 0;
			}
			if(steer_flag.flag_o4_ok >= 100)
			{
				steer_flag.flag_o4_ok = 0;
				x_set = ball_locate.changeo1_x;
				y_set = ball_locate.changeo1_y;
				steer_flag.flag_o1 = 1;
				steer_flag.flag_o4 = 0;
			}
		}
	}
	else
	{
		if(!steer_flag.flag_a9)
		{
			x_set = ball_locate.changes9_x;
			y_set = ball_locate.changes9_y;
			if((ball_band.last_x - ball_locate.changes9_x <=3 && ball_band.last_x - ball_locate.changes9_x >= -3) && 
				(ball_band.last_y - ball_locate.changes9_y <= 3 && ball_band.last_y - ball_locate.changes9_y >=-3))
			{
				steer_flag.flag_a9_ok++;
			}
			else
			{
				steer_flag.flag_a9_ok = 0;
			}
			if(steer_flag.flag_a9_ok >= 100)
			{
				steer_flag.flag_a9_ok = 0;
				x_set = ball_locate.area9_x;
				y_set = ball_locate.area9_y;
				steer_flag.flag_a9 = 1;
			}
		}
		if(steer_flag.flag_a9)
		{
			x_set = ball_locate.area9_x;
			y_set = ball_locate.area9_y+6;
		}
	}
	
	//用PID计算X轴方向上的舵机PWM占空比
	steer_x_pid.Duty = steering_duty.x_middle + PID_x(ball_band.last_x)*0.001;
	
	//用PID计算Y轴方向上的舵机PWM占空比
	steer_y_pid.Duty = steering_duty.y_middle - PID_y(ball_band.last_y)*0.001;
	
	x_steering(steer_x_pid.Duty);
	y_steering(steer_y_pid.Duty);
}









