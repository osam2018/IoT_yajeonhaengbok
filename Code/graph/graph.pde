import processing.serial.*;

Serial port;
int x_position = 1;
float value = 0;
float old_value = 0;

void setup(){
    size(400, 300);
    port = new Serial(this, Serial.list()[2], 9600); //Board Port
    port.bufferUntil('\n');
    background(0);
}

void draw(){
    stroke(255, 255, 0);
    line(x_position, height - old_value, x_position, height - value); //Processing coordinate system 
    
    if(x_position >= width){ 
        x_position = 0;
        background(0);
    } //monitor reset
    else{
        x_position++;
    }
    old_value = value;
}


void serialEvent (Serial port) {
    String input = port.readStringUntil('\n');

    if (input != null) {
        input = trim(input);
        value = float(input);
        println(value);
        value = map(value, 0, 200, 0, height);
    }
}
