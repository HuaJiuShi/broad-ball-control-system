#ifndef __BALL_CONTROL_H
#define __BALL_CONTROL_H
#include "sys.h"
#include "main.h"


typedef struct 
{
	u8 area1_x;
	u8 area1_y;
	u8 area2_x;
	u8 area2_y;
	u8 area3_x;
	u8 area3_y;
	u8 area4_x;
	u8 area4_y;
	u8 area5_x;
	u8 area5_y;
	u8 area6_x;
	u8 area6_y;
	u8 area7_x;
	u8 area7_y;
	u8 area8_x;
	u8 area8_y;
	u8 area9_x;
	u8 area9_y;
	u8 change_x;
	u8 change_y;
	
	u8 change151_x;
	u8 change151_y;
	u8 change152_x;
	u8 change152_y;
	
	u8 change141_x;
	u8 change141_y;
	u8 change142_x;
	u8 change142_y;
	u8 change451_x;
	u8 change451_y;
	u8 change452_x;
	u8 change452_y;
	
	u8 change121_x;
	u8 change121_y;
	u8 change122_x;
	u8 change122_y;
	u8 change261_x;
	u8 change261_y;
	u8 change262_x;
	u8 change262_y;
	u8 change691_x;
	u8 change691_y;
	
	u8 change191_x;
	u8 change191_y;
	u8 change192_x;
	u8 change192_y;
	u8 change193_x;
	u8 change193_y;
	u8 change194_x;
	u8 change194_y;
	u8 change195_x;
	u8 change195_y;
	u8 change196_x;
	u8 change196_y;
	u8 change197_x;
	u8 change197_y;
	u8 change198_x;
	u8 change198_y;
	u8 change199_x;
	u8 change199_y;
	u8 change1910_x;
	u8 change1910_y;
	u8 change1911_x;
	u8 change1911_y;
	u8 change1912_x;
	u8 change1912_y;
	 
	u8 changeo1_x;
	u8 changeo1_y;
	u8 changeo2_x;
	u8 changeo2_y;
	u8 changeo3_x;
	u8 changeo3_y;
	u8 changeo4_x;
	u8 changeo4_y;
	
	u8 changes9_x;
	u8 changes9_y;
}ball_locate_Typedef;

typedef struct 
{
	float x_max;
	float x_min;
	float x_middle;
	float y_max;
	float y_min;
	float y_middle;	
}steering_duty_Typedef;

typedef struct 
{
	u8 aim_x;
	u8 aim_y;
	u8 last_x;
	u8 last_y;
	u8 pre_x;
	u8 pre_y;
	int dis_x;
	int dis_y;
	int speed_x;
	int speed_y;
}ball_band_sys_Typedef;

typedef struct    //定义中继点坐标以及距离
{
	u8 relay1_x;
	u8 relay1_y;
	u8 relay2_x;
	u8 relay2_y;
	int dis_relay1_x;  
	int dis_relay1_y;
	int dis_relay2_x;
	int dis_relay2_y;
}ball_relay_sys_Typedef;

typedef struct 
{
	int Desired_Value;	// 设定目标 Desired_Value
	int NextValue;		// 当前值
	float PID_P;			// 比例常数 Proportional Const
	float PID_I;			// 积分常数 Integral Const 
	float PID_D;			// 微分常数 Derivative Const
	int LastError;		// Error[-1]
	int PrevError;		//Error[-2]
	int SumError;			// Sums of Errors
	float Duty;				//舵机占空比
}steer_x_pid_Typedef;

typedef struct 
{
	int Desired_Value;	// 设定目标 Desired_Value
	int NextValue;		// 当前值
	float PID_P;			// 比例常数 Proportional Const
	float PID_I;			// 积分常数 Integral Const 
	float PID_D;			// 微分常数 Derivative Const
	int LastError;		// Error[-1]
	int PrevError;		//Error[-2]
	int SumError;			// Sums of Errors
	float Duty;				//舵机占空比
}steer_y_pid_Typedef;


typedef struct 
{
	u8 t_flag;
	u8 tt_flag;
	u8 flag_0;
	u8 flag_3;
	u8 flag_o1;
	u8 flag_o2;
	u8 flag_o3;
	u8 flag_o4;
	u8 flag_o1_ok;
	u8 flag_o2_ok;
	u8 flag_o3_ok;
	u8 flag_o4_ok;
	u8 flag_a9_ok;
	u8 flag_times;	//次数
	u8 flag_a9;
}steer_flag_Typedef;



extern int iError_x,lastError_x,PrevError_x,x_set;
extern float dux,ux1,ux;
extern float Kp_x,Ki_x,Kd_x;
extern float Kp_y,Ki_y,Kd_y;
extern int iError_y,lastError_y,PrevError_y,y_set;
extern float duy,uy1,uy;
extern float uy_min,uy_max,ux_min,ux_max;


void update_data(void);
void calculate_parameter(void);
void ball_pid_init(void);
void ball_locate_init(void);
void ball_control_init(void);
void ball_pid_set(unsigned int seg);
float ball_pid_x(void);
float ball_pid_y(void);
float PID_x(float x);
float PID_y(float y);
void pid_control(void);

void num1_control_init(void);
void num2_control_init(void);
void num3_control_init(void);
void num4_control_init(void);
void num5_control_init(void);
void num6_control_init(void);
void num7_control_init(void);

void num1_control(void);
void num2_control(void);
void num3_control(void);
void num4_control(void);
void num5_control(void);
void num6_control(void);
void num7_control(void);

#endif









