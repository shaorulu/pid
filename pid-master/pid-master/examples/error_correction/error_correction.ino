/*
 * 用于Arduino的C语言PID控制器实现 - 使用示例
 * 
 * 此示例展示如何使用该库根据PID算法计算误差修正。
 */

#include "pid.h"


// 初始化空的PID_Calibration结构体和空的PID_State结构体
PID_Calibration calibration;
PID_State state;


void setup() {
    // 配置校准和状态结构体
    // 虚拟的增益值
    calibration.kp = 1.0;
    calibration.ki = 1.0;
    calibration.kd = 1.0;
    // 初始空白的起始状态
    state.actual = 0.0;
    state.target = 0.0;
    state.time_delta = 1.0; // 假设任意时间间隔为1.0
    state.previous_error = 0.0;
    state.integral = 0.0;
    // 以9600波特率启动串行通信
    Serial.begin(9600);
}


void loop() {
    // 从串行通信中读取两个字节，假定第一个是目标值，第二个是实际值。在串行上输出计算结果
    if (Serial.available() >= 2) {
        // 读取一个字节作为目标值，转换为double并存储在状态结构体中
        state.target = (double) Serial.read();
        // 对实际值执行与上面相同的操作
        state.actual = (double) Serial.read();
        // 现在执行PID计算并将输出重新赋值给状态
        state = pid_iterate(calibration, state);
        // 在串行上打印结果
        Serial.print("目标值:\t");
        Serial.println(state.target);
        Serial.print("实际值:\t");
        Serial.println(state.actual);
        Serial.print("输出值:\t");
        Serial.println(state.output);
    }
}
