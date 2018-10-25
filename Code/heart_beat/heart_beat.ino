double alpha = 0.80; //heart beat buffer
int minval = 0; //sensor calibration
int old_value = 0; // 
unsigned long time_now = 0;
unsigned long time_check = 0;

bool flag = false;
int redpin = 11;
int greenpin = 10;

void setup ()
{
    Serial.begin (9600);
    pinMode(7, OUTPUT);
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);  
}

void loop ()
{
    int raw_value = analogRead(A0)-900;
    if(raw_value < minval){
        raw_value = 0;
    }
    double value = alpha * old_value + (1 - alpha) * raw_value;

    Serial.println (value);
    old_value = value;

    if(raw_value == 0){
        analogWrite (redpin, 60);
        analogWrite (greenpin, 30);
        time_check = millis();
        digitalWrite(7, LOW);
    }
    else if(flag == true){
        if(value < 85 || value > 120){
            analogWrite (redpin, 100);
            analogWrite (greenpin, 0);
            time_now = millis();
            if(time_now - time_check > 10000){
                digitalWrite(7, HIGH);
            }
        }
        else{
            analogWrite (redpin, 0);
            analogWrite (greenpin, 100);
            flag = false;
            time_check = millis();
            digitalWrite(7, LOW);
        } 
    }
    else if(flag == false && value < 85 || value > 120){
        analogWrite (redpin, 100);
        analogWrite (greenpin, 0);
        time_check = millis();
        flag = true;
    }
    else{
        analogWrite (redpin, 0);
        analogWrite (greenpin, 100);
        time_check = millis();
        digitalWrite(7, LOW);
    }
    delay (200);
}
