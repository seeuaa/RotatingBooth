/*
 Today, I am extremely excited to open source our carefully crafted rotating booth! Firstly, I would like to sincerely thank all the partners who have supported and helped me during the development process, especially Chen Jiayi, Song Yuchen, and Liu Muze. Whether discussing solutions together or providing valuable ideas when encountering code difficulties, your efforts have turned the rotating booth from concept to reality.
 I hope this code will be useful to those in need, and I look forward to exchanging ideas with more developers. If you have any thoughts, suggestions during use, or want to collaborate, feel free to reach out to me at 378943818@qq.com .
 Meanwhile, if the rotating booth is helpful for your project and you are willing to provide funding support for my subsequent development work, so that we can continue to optimize and produce more high-quality content, I would be extremely grateful.
Donation link:
Alipay: lblhhh@126.com .

May the spirit of open - source thrive, and let's create more possibilities together in the world of code!
 */
#include <IRremote.h>

// 引脚定义
#define ENA_PIN 6       // PWM控制转速
#define IN1_PIN 7       // 正转控制
#define IN2_PIN 8       // 反转控制


#define IR_RECEIVE_PIN 2 // 红外接收引脚

// 红外解码对象
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

// 状态变量
bool isRunning = false;   // 运行状态（开机/关机）
int speedLevel = 4;       // 速度档位（0-4，对应PWM值0-255）
int direction = 0;        // 方向：0=停止，1=正转，2=反转

// 红外按键编码（需根据实际遥控器调试）
#define KEY_POWER 0xFF38C7   // 电源键
#define KEY_FORWARD 0xFF5AA5 // 正转键
#define KEY_BACKWARD 0xFF10EF // 反转键
#define KEY_SPEED_UP 0xFF18E7 // 加速键
#define KEY_SPEED_DOWN 0xFF4AB5 // 减速键

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  
  irrecv.enableIRIn(); // 启动红外接收
  Serial.begin(9600);  // 串口调试
}

void loop() {
  if (irrecv.decode(&results)) { // 读取红外信号
    handleIRCommand(results.value);
    Serial.println(results.value,HEX);
    irrecv.resume(); // 准备接收下一个信号
  }

  // 根据状态控制电机
  if (isRunning) {
    controlMotor();
  } else {
    stopMotor(); // 关机时停止电机
  }
}

// 处理红外指令
void handleIRCommand(unsigned long command) {
  switch (command) {
    case KEY_POWER:
      isRunning = !isRunning; // 切换开关机状态
      Serial.println("电源状态：" + String(isRunning));
      if (isRunning) {
         direction = 1; // 正转
      }
      break;
    
    case KEY_FORWARD:
      if (isRunning) {
        direction = 1; // 正转
        Serial.println("正转");
      }
      break;
    
    case KEY_BACKWARD:
      if (isRunning) {
        direction = 2; // 反转
        Serial.println("反转");
      }
      break;
    
    case KEY_SPEED_UP:
      if (isRunning && speedLevel < 4) {
        speedLevel++; // 速度档位提升（0-4）
        Serial.println("速度：" + String(speedLevel));
      }
      break;
    
    case KEY_SPEED_DOWN:
      if (isRunning && speedLevel > 0) {
        speedLevel--; // 速度档位降低
        Serial.println("速度：" + String(speedLevel));
      }
      break;
    
    default:
      break;
  }
  updateSpeed();
}

// 更新电机转速（PWM控制）
void updateSpeed() {
  int pwmValue = map(speedLevel, 0, 4, 0, 255); // 档位映射到PWM值
  analogWrite(ENA_PIN, pwmValue);
  Serial.println("PWM:");
  Serial.println(pwmValue);
}

// 控制电机正反转
void controlMotor() {
  switch (direction) {
    case 1: // 正转
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
      break;
    
    case 2: // 反转
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
      break;
    
    default: // 停止（方向未设置时）
      stopMotor();
      break;
  }
}

// 停止电机
void stopMotor() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 0); // 关闭PWM
  direction = 0;
}
