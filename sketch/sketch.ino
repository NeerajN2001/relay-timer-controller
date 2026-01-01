#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define up 2
#define down 3
#define set 4
#define menu 5
#define relay 8

struct values {
  unsigned long hour;
  unsigned long minute;
  unsigned long second;
};
values timer = {0, 0, 0};
unsigned long total_time = 0;
unsigned long clock_time;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
}



void loop() {
  lcd_print("Set Timer", 0, 0);
  lcd_print("M to enter menu", 0, 1);

  while(true) {
    if(digitalRead(menu) == LOW) {
      delay(200);
      menu_f();
      total_time = ((timer.hour*60*60)+(timer.minute*60)+(timer.second))*1000;
      relay_control(total_time);
      timer = {0,0,0};
      break;
    }
  }
}


//----------Functions
void relay_control(unsigned long total_time) {
  unsigned long display_refresh = millis();
  digitalWrite(relay, HIGH);
  lcd_print("Relay ON", 0, 1);

  while(true) {
    while (timer.second > 0) {
      if(millis()-display_refresh > 1000) {
        display_refresh = millis();
        timer.second -= 1;
        String display_time = String(timer.hour)+":"+String(timer.minute)+":"+String(timer.second);
        lcd_print(display_time, 0, 0);
      }
      if (digitalRead(menu) == LOW) {
        delay(200);
        menu_f();
      }
      if (digitalRead(set) == LOW) {
        delay(200);
        timer = {0,0,0};
        break;
      }
    }
    if(timer.minute > 0) {
      timer.minute -= 1;
      timer.second = 60;
    }
    else if(timer.hour > 0) {
      timer.hour -= 1;
      timer.minute = 60;
    }
    if (timer.hour == 0 && timer.minute==0 && timer.second==0) {
      break;
    }
  }

  digitalWrite(relay, LOW);
  Serial.println("Relay OFF");
}

void lcd_print(String message, int posx, int posy) {
  lcd.setCursor(posx, posy);
  lcd.print("                ");
  lcd.setCursor(posx, posy);
  lcd.print("     ");
  lcd.print(message);
}

void menu_f() {
  lcd_print("Menu", 0, 0);
  lcd_print("M to set time", 0, 1);
  while (true) {
    if(digitalRead(menu) == LOW) {
      delay(200);
      set_hour();
      lcd.clear();
      break;
    }
  }
}

void set_hour() {
  lcd_print("Hour", 0, 0);
  lcd_print(String(timer.hour), 0, 1);
  while(true) {
    if (digitalRead(up) == LOW) {
      delay(200);
      timer.hour += 1;
      lcd_print(String(timer.hour), 0, 1);
    }
    else if (digitalRead(down) == LOW) {
      delay(200);
      if (timer.hour>0) {
        timer.hour -= 1;
      }
      lcd_print(String(timer.hour), 0, 1);
    }
    else if (digitalRead(menu) == LOW) {
      delay(200);
      set_minutes();
      break;
    }
    else if (digitalRead(set) == LOW) {
      delay(400);
      break;
    }
  }
}

void set_minutes() {
  lcd_print("Minutes", 0, 0);
  lcd_print(String(timer.minute), 0, 1);
  while(true) {
    if (digitalRead(up) == LOW) {
      delay(200);
      if (timer.minute<60) {
        timer.minute += 1;
      }
      lcd_print(String(timer.minute), 0, 1);
    }
    else if (digitalRead(down) == LOW) {
      delay(200);
      if (timer.minute>0) {
        timer.minute -= 1;
      }
      lcd_print(String(timer.minute), 0, 1);
    }
    else if (digitalRead(menu) == LOW) {
      delay(200);
      set_second();
      break;
    }
    else if (digitalRead(set) == LOW) {
      delay(400);
      break;
    }
  }
}

void set_second() {
  lcd_print("Seconds", 0, 0);
  lcd_print(String(timer.second), 0, 1);
  while(true) {
    if (digitalRead(up) == LOW) {
      delay(200);
      if (timer.second<60) {
        timer.second += 1;
      }
      lcd_print(String(timer.second), 0, 1);
    }
    else if (digitalRead(down) == LOW) {
      delay(200);
      if (timer.second>0) {
        timer.second -= 1;
      }
      lcd_print(String(timer.second), 0, 1);
    }
    else if (digitalRead(menu) == LOW) {
      delay(200);
      set_hour();
    }
    else if (digitalRead(set) == LOW) {
      delay(400);
      break;
    }
  }
}
