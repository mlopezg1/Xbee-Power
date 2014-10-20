char pregunta = 'pregunta';
char frame[64];
char gframe[64] = {0x7E,0x00,0x10,0x17,0x01,0x04,0x00,0x42,0x05,0x45,0x41,0x01,0x06,0xFF,0xFE,0x02,'D','B',0x00,pregunta};
char resframe[64];
bool state = true;


void setup(){
	Serial.begin(115200);
	Serial1.begin(9600);
	delay(1000);
	Serial.println("--- Send Frame ---");
}

uint8_t adress[8] = {0x04,0x00,0x41,0x08,0x43,0x03,0x43,0x03};

// --- AT Remote Frame ---
/* Frame = 	[header]
			[MSB]
			[LSB] 
			[Frame Type] 
			[ID]  
			[AT Command]
			[Command Status]
			[Command Data]
			[Check Sum]
*/

void loop(){

if (Serial1.available()){
  if (Serial1.read() == 0x7E){
  	for(int i=0; i<20; i++){
  		Serial.print(Serial1.read());
  	    frame[i] = Serial1.read();
  		}
   }
 }

if(frame == gframe){
state = !state;

		resframe[0] = 0x7E; 				// Header

		resframe[1] = (byte)0x00;			// MSB
		resframe[2] = 0x05;				// LSB

		resframe[3] = 0x88; 				// Frame Type

		resframe[4] = 0x01;				// ID

		resframe[5] = 'D';
		resframe[6] = 'B';

		resframe[7] = 0x00;	           //Command Status

		resframe[8] = checkSum(7);		// CheckSum

		for(int i=0; i<9; i++){		// 
			Serial1.write(resframe[i]);
		}
	}

		delay(100);

		/*while(Serial1.available()){
			Serial.print(Serial1.read(),HEX);
			Serial.print('\t');
		}*/
		Serial.println("");
		Serial.println("Finish!");
	}

uint8_t checkSum(uint8_t len){
	int sum = 0;
	for(int i = 3; i < len+1; i++){
		sum += uint8_t(frame[i]);
	}
	return (uint8_t)(0xFF - sum);
}