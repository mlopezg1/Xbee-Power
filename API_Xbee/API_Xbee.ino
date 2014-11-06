char frame[64];
bool state = true;

void setup(){
	Serial.begin(9600);
	Serial1.begin(14400);
	delay(1000);
	Serial.println("--- Send Frame ---");
}

uint8_t adress[8] = {0x04,0x00,0x42,0x05,0x45,0x41,0x01,0x06};

// --- AT Comand Frame ---
/* Frame = 	[header]
			[MSB]
			[LSB] 
			[Frame Type] 
			[ID] 
			[AT Command]
			[AT Parameter]
			[Check Sum]
*/

String readString()
{
	String output = "";
	while(Serial.available())                        
	{                    
	   output.concat(char(Serial.read()));                   // statement
	   delay(10);
	}
	return output;
}

String orden = "";

void loop(){

while(orden == ""){
  orden = readString();  // statement
}

if(orden != "potencia"){
    Serial.print("entrada invalida");
}

	else if(orden == "potencia"){

		state = !state;

		frame[0] = 0x7E; 				// Header

		frame[1] = (byte)0x00;			// MSB
		frame[2] = 0x04;				// LSB

		frame[3] = 0x08; 				// Frame Type

		frame[4] = 0x52;				// ID


        frame[5] = 'D';   	//hex (0x44)
		frame[6] = 'B';		//hex(0x42)

		frame[7] = checkSum(6);		// CheckSum

		for(int i=0; i<8; i++){		// 
			Serial1.write(frame[i]);
		}

		delay(100);

		if(Serial1.available()){
			Serial.print(Serial1.read(),HEX);
			Serial.print('\t');
		}
		Serial.println("");
		Serial.println("Finish!");

		/*while(Serial.available()){
		    Serial.read();
		}*/
	}
}

int checkSum(uint8_t len){
	int sum = 0;
	for(int i = 3; i < len+1; i++){
		sum += uint8_t(frame[i]);
	}
	return (uint8_t)(0xFF - sum);
}
