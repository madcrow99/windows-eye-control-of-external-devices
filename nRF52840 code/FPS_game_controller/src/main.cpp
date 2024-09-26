

#if defined(USE_TINYUSB)
#include <Adafruit_TinyUSB.h> // for Serial
#endif
#include <Arduino.h>
#include <bluefruit.h>






BLEDis bledis;
BLEHidAdafruit blehid;


char receivedCmd = 'x';


int8_t fast = 120;
int8_t medium  = 60;
int8_t slow = 20;
int8_t scroll = 5;


String ctrl_mode = "phone";
bool latch_active = false;
bool key_latch_active = false;
bool key_assigned = false;
String key_assigned_string = "";


void startAdv(void);
void mouse_click_control(char cmd);
void ipad_click_control(char cmd);
void processKeyboardCommand() ;
String readSerialCommand() ;
void send_key(const String& command) ;
void processMouseCommand() ;
void processGameCommand() ;


void setup() {
 
  Serial.begin(9600);
  Bluefruit.begin();
  // HID Device can have a min connection interval of 9*1.25 = 11.25 ms
  Bluefruit.Periph.setConnInterval(9, 16); // min = 9*1.25=11.25 ms, max = 16*1.25=20ms
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  //Bluefruit.setName("ICAN HID Device");
  Bluefruit.setName("MikeHID");


  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();


  // BLE HID
  blehid.begin();


  // Set up and start advertising
  startAdv();


 
 
}


void loop() {
    if (Serial.available() > 0) {
        char header = Serial.read(); // Read the header


        if (header == 'K') {
            // Keyboard command
            processKeyboardCommand();
        } else if (header == 'M') {
            // Mouse command
            processMouseCommand(); // Implement this function based on how you want to handle mouse commands
        } else if (header == 'L') {//mouse latch
            // Latch command
            latch_active = !latch_active;
            if (!latch_active) {
                blehid.mouseButtonRelease();
            }
        }
         else if (header == 'N') {//keyboard latch latch
            // Latch command
            key_latch_active = !key_latch_active;
            if (!key_latch_active) {
                blehid.keyRelease();
                key_assigned = false;
                key_assigned_string = "";
            }
        } else if (header == 'G') {
            // Game command
            processGameCommand(); // Implement this function based on how you want to handle game commands
        }      
    }
}


void processKeyboardCommand() {
    if (Serial.available() > 0) {
       String command = readSerialCommand(); // Read the entire command as a string
       send_key(command);
         if(key_latch_active) {
              if(!key_assigned) {
                key_assigned = true;
                key_assigned_string = command;
              }
              delay(100);
              send_key(key_assigned_string);
        } else{
            delay(100);
            blehid.keyRelease();
        }
    }
}
   




String readSerialCommand() {
    String command = "";
    while (Serial.available() > 0) {
        char c = Serial.read();
        command += c;
        delay(5); // Small delay to allow buffer to fill
    }
    return command;
}


void send_key(const String& command) {
    if (command.length() == 1) {
      // Single character command
      blehid.keyPress(command[0]);  
      return;        
    }
    else if (command == "down") { uint8_t keycodes[6] = { HID_KEY_ARROW_DOWN, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  ); return;}
    else if (command == "up") { uint8_t keycodes[6] = { HID_KEY_ARROW_UP, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "left") { uint8_t keycodes[6] = { HID_KEY_ARROW_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "right") { uint8_t keycodes[6] = { HID_KEY_ARROW_RIGHT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "backspace") { uint8_t keycodes[6] = { HID_KEY_BACKSPACE, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "enter") { uint8_t keycodes[6] = { HID_KEY_ENTER, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "space") { uint8_t keycodes[6] = { HID_KEY_SPACE, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "tab") { uint8_t keycodes[6] = { HID_KEY_TAB, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "escape") { uint8_t keycodes[6] = { HID_KEY_ESCAPE, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "alt") { uint8_t keycodes[6] = { HID_KEY_ALT_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "control") { uint8_t keycodes[6] = { HID_KEY_CONTROL_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "shift") { uint8_t keycodes[6] = { HID_KEY_SHIFT_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "numlock") { uint8_t keycodes[6] = { HID_KEY_NUM_LOCK, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
    else if (command == "capslock") { uint8_t keycodes[6] = { HID_KEY_CAPS_LOCK, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
    blehid.keyboardReport( 0 ,  keycodes  );return;}
return;
}


void processMouseCommand() {
    // Implement mouse command processing
     if (Serial.available() > 0) {
        String command = readSerialCommand(); // Read the entire command as a string


        if(command == "LLLFFF") blehid.mouseMove(-fast, -fast);
        if(command == "LLFFF") blehid.mouseMove(-medium, -fast);
        if(command == "LFFF") blehid.mouseMove(-slow, -fast);
        if(command == "FFF") {blehid.mouseMove(0,-fast); delay(25); blehid.mouseMove(0,-fast);}
        if(command == "RRRFFF") blehid.mouseMove(fast, -fast);
        if(command == "RRFFF") blehid.mouseMove(medium, -fast);
        if(command == "RFFF") blehid.mouseMove(slow, -fast);


        if(command == "LLLFF") blehid.mouseMove(-fast, -medium);
        if(command == "LLFF") blehid.mouseMove(-medium, -medium);
        if(command == "LFF") blehid.mouseMove(-slow, -medium);
        if(command == "FF") blehid.mouseMove(0, -medium);
        if(command == "RRRFF") blehid.mouseMove(fast, -medium);
        if(command == "RRFF") blehid.mouseMove(medium, -medium);
        if(command == "RFF") blehid.mouseMove(slow, -medium);


        if(command == "LLLF") blehid.mouseMove(-fast, -slow);
        if(command == "LLF") blehid.mouseMove(-medium, -slow);
        if(command == "LF") blehid.mouseMove(-slow, -slow);
        if(command == "F") blehid.mouseMove(0, -slow);
        if(command == "RRRF") blehid.mouseMove(fast, -slow);
        if(command == "RRF") blehid.mouseMove(medium, -slow);
        if(command == "RF") blehid.mouseMove(slow, -slow);


        if(command == "LLL")  {blehid.mouseMove(-fast, 0); delay(25); blehid.mouseMove(-fast, 0);}
        if(command == "LL") blehid.mouseMove(-medium, 0);
        if(command == "L") blehid.mouseMove(-slow, 0);
        if(command == "R") blehid.mouseMove(slow, 0);
        if(command == "RR") blehid.mouseMove(medium, 0);
        if(command == "RRR") {blehid.mouseMove(fast, 0); delay(25); blehid.mouseMove(fast, 0);}


        if(command == "LLLBBB") blehid.mouseMove(-fast, fast);
        if(command == "LLBBB") blehid.mouseMove(-medium, fast);
        if(command == "LBBB") blehid.mouseMove(-slow, fast);
        if(command == "BBB") {blehid.mouseMove(0, fast); delay(25); blehid.mouseMove(0, fast);}
        if(command == "RRRBBB") blehid.mouseMove(fast, fast);
        if(command == "RRBBB") blehid.mouseMove(medium, fast);
        if(command == "RBBB") blehid.mouseMove(slow, fast);


        if(command == "LLLBB") blehid.mouseMove(-fast, medium);
        if(command == "LLBB") blehid.mouseMove(-medium, medium);
        if(command == "LBB") blehid.mouseMove(-slow, medium);
        if(command == "BB") blehid.mouseMove(0, medium);
        if(command == "RRRBB") blehid.mouseMove(fast, medium);
        if(command == "RRBB") blehid.mouseMove(medium, medium);
        if(command == "RBB") blehid.mouseMove(slow, medium);


        if(command == "LLLB") blehid.mouseMove(-fast, slow);
        if(command == "LLB") blehid.mouseMove(-medium, slow);
        if(command == "LB") blehid.mouseMove(-slow, slow);
        if(command == "B") blehid.mouseMove(0, slow);
        if(command == "RRRB") blehid.mouseMove(fast, slow);
        if(command == "RRB") blehid.mouseMove(medium, slow);
        if(command == "RB") blehid.mouseMove(slow, slow);


        if(command =="Left") {
            blehid.mouseButtonPress(1);
            if(!latch_active) {
                delay(75);
                blehid.mouseButtonRelease();}
        }
        if(command =="Right") {
            blehid.mouseButtonPress(2);
            if(!latch_active) {
                delay(75);
                blehid.mouseButtonRelease();}
        }
        if(command =="Center") {blehid.mouseButtonPress(3); delay(25); blehid.mouseButtonRelease();}
       
        if(command =="Scrollu") blehid.mouseScroll(scroll);
        if(command =="Scrolld") blehid.mouseScroll(-scroll);


     }
}
int move_delay = 250;
bool sneak_mode = false;
bool game_latch_active = false;
void processGameCommand() {
    // Implement game command processing
    if (Serial.available() > 0) {
        String command = readSerialCommand(); // Read the entire command as a string

        if (command == "Jump") { uint8_t keycodes[6] = { HID_KEY_SPACE, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
        blehid.keyboardReport( 0 ,  keycodes  );
        delay(10);
        blehid.keyRelease();
        blehid.keyboardReport( 0 ,  keycodes  );
        delay(move_delay); blehid.keyRelease();
        }
        if(command == "LF") {blehid.mouseMove(-fast, 0);blehid.keyPress('w'); delay(move_delay); blehid.keyRelease();}
        if(command == "LFF") {blehid.mouseMove(-slow, 0);blehid.keyPress('w'); delay(move_delay); blehid.keyRelease();}
        if(command == "FF") {blehid.keyPress('w'); delay(move_delay); blehid.keyRelease();}
        if(command == "RFF") {blehid.mouseMove(slow, 0);blehid.keyPress('w'); delay(move_delay); blehid.keyRelease();}
        if(command == "RF") {blehid.mouseMove(fast, 0);blehid.keyPress('w'); delay(move_delay); blehid.keyRelease();}
        if(command == "StrafeL") {blehid.keyPress('a'); delay(move_delay); blehid.keyRelease();}
        if(command == "BB") {blehid.keyPress('s'); delay(move_delay); blehid.keyRelease();}
        if(command == "StrafeR") {blehid.keyPress('d'); delay(move_delay); blehid.keyRelease();}
        //for sneak mode hold left control. This is implemented as a toggle
        if (command == "Sneak") {
            sneak_mode = !sneak_mode;
            if (sneak_mode) {
                { uint8_t keycodes[6] = { HID_KEY_SHIFT_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
                blehid.keyboardReport( 0 ,  keycodes  );}
                //delay(move_delay);
               
            } else {
                blehid.keyRelease();
               
            }


        }
        
        if (command == "Latch") {
            game_latch_active = !game_latch_active;
            
        }
        if (!game_latch_active) {
                blehid.keyRelease();
                if (sneak_mode) {
                { uint8_t keycodes[6] = { HID_KEY_SHIFT_LEFT, HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE , HID_KEY_NONE };
                blehid.keyboardReport( 0 ,  keycodes  );}
                //delay(move_delay);
               
            } 
            } else {
                blehid.keyPress('w');
                
            }
    }




}




      //enter key is int 13
      //backspace is int 8
      //escape is int 27
      //space is int 32
      //tab is int 9
      //delete is int 127
      //up is int 38
      //down is int 40
      //left is int 37
      //right is int 39
      //home is int 36
      //end is int 35
      //page up is int 33
      //page down is int 34
      //enter is int 13
      //shift is int 16
      //control is int 17
      //alt is int 18
      //caps lock is int 20
      //f1 is int 112
      //f2 is int 113
      //f3 is int 114
      //f4 is int 115
      //f5 is int 116
      //f6 is int 117
      //f7 is int 118
      //f8 is int 119
      //f9 is int 120
      //f10 is int 121
      //f11 is int 122
      //f12 is int 123
      //print screen is int 44
      //insert is int 45
      //num lock is int 144
      //scroll lock is int 145
      //pause is int 19
      //windows key is int 91
      //windows menu is int 93
     






void startAdv(void)
{  
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_MOUSE);
 
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);


  // There is enough room for 'Name' in the advertising packet
  Bluefruit.Advertising.addName();
 
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html  
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}



