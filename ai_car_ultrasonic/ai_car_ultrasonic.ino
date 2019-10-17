
#include<Servo.h>
Servo myservo;
const int TrigPin = 2;
const int EchoPin = 3;


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool isDetectDistance = false;
int detectInterval = 1000;
void setup()
{
	Serial.begin(115200);
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
	myservo.attach(9);
}

int i = 0;
void loop()
{
	if (isDetectDistance) {
		delay(detectInterval);
		float distance = readDistance();
		String str = String(myservo.read())+ "," + String(distance) +";";
		Serial.println("detect:"+str);
	}

}

float readDistance() {
	float cm=0.0;
	digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm
	cm = (int(cm * 100.0)) / 100.0; //保留两位小数
	return cm;
}



void serialEvent() {
	while (Serial.available()) {
		String data = Serial.readStringUntil(';');//读一条指令 “；”分割
		if (data.length() == 0) {
			return;
		}
		Serial.println(data);
		int index = data.indexOf(':');
		String k = "";
		String v = "";
		if (index != -1) {//如果有冒号，说明是指令带值
			k = data.substring(0, index);
			v = data.substring(index + 1, data.length());
		}
		else {//否则只有指令
			k = data;
		}
		float distance = readDistance();
		if (k.compareTo("turn")==0) {
			int dis = myservo.read() - v.toInt();
			int delaytime = abs(dis) * 150 / 45;
			myservo.write(v.toInt());
			delay(delaytime);
			distance = readDistance();
			String str = v +","+ distance+";";
			Serial.println("read:"+str);
		}else if (k.compareTo("read_distance") == 0) {
			String s =   String(myservo.read());
			String str = s + "," + distance + ";";
			Serial.println("read:"+str);
		}else if (k.compareTo("detect_distance") == 0) {
			if (v.toInt() <= 0) {
				isDetectDistance = false;
			}else {
				isDetectDistance = true;
				detectInterval = v.toInt();
			}	
		}
	}
}