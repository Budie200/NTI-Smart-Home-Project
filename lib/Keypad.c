#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "Keypad.h"
#include "Delay.h"

static const u8 KPD_Map[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}
};

void KPD_Init(){
	// make the columns inputs and turn the pull up res
	for(u8 cols = 0; cols < 4; cols++){
		DIO_SetPinDirection(KPD_Port, cols, INPUT);
		DIO_SetPinValue(KPD_Port, cols, HIGH);
	}

	// make the rows outputs and init to HIGH
	for(u8 rows = 4; rows < 8; rows++){
		DIO_SetPinDirection(KPD_Port, rows, OUTPUT);
		DIO_SetPinValue(KPD_Port, rows, HIGH);
	}

}

u8 KPD_GetPressedKey(){

	u8 pressed_key = KPD_Unpressed;

	for(u8 row = 4; row < 8; row++){

		// Drive the current row LOW
		DIO_SetPinValue(KPD_Port, row, LOW);

		for(u8 col = 0; col < 4; col++){

			// If the col reads LOW, a button is pressed
			if(DIO_GetPinValue(KPD_Port, col) == LOW){

				pressed_key = KPD_Map[row - 4][col];

				while(DIO_GetPinValue(KPD_Port, col) == LOW) {
					Delay_ms(10);
				}

				DIO_SetPinValue(KPD_Port, row, HIGH);
				break;
			}
		}

		// Restore the row to HIGH before checking the next one
		DIO_SetPinValue(KPD_Port, row, HIGH);
	}

	return pressed_key;
}
