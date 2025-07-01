/*
 Today, I am extremely excited to open source our carefully crafted rotating booth! Firstly, I would like to sincerely thank all the partners who have supported and helped me during the development process, especially Chen Jiayi, Song Yuchen, and Liu Muze. Whether discussing solutions together or providing valuable ideas when encountering code difficulties, your efforts have turned the rotating booth from concept to reality.
 I hope this code will be useful to those in need, and I look forward to exchanging ideas with more developers. If you have any thoughts, suggestions during use, or want to collaborate, feel free to reach out to me at 378943818@qq.com .
 Meanwhile, if the rotating booth is helpful for your project and you are willing to provide funding support for my subsequent development work, so that we can continue to optimize and produce more high-quality content, I would be extremely grateful.
Donation link:
Alipay: lblhhh@126.com .

May the spirit of open - source thrive, and let's create more possibilities together in the world of code!
 * 
 */
// 定义引脚  
const int IN1 = 8;  
const int IN2 = 7;  
const int ENA = 6;  

void setup() {  
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(ENA, OUTPUT);  
}

void loop() {  

  // 正转（全速）  
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);  
  analogWrite(ENA, 255); // PWM占空比0-255  
  delay(2000);  

  // 反转（半速）  
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);  
  analogWrite(ENA, 200);  
  delay(2000);  

  // 停止  
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, LOW);  
  delay(1000);  
}
