#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {2,3,4,5};
byte pinesColumnas[COLUMNAS] = {6,7,8,9};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

long num1 = 0;
long num2 = 0;
char op = 0;
bool segundo = false;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {

  char tecla = teclado.getKey();

  if (tecla) {

    if (tecla >= '0' && tecla <= '9') {

      if (!segundo) {
        num1 = num1 * 10 + (tecla - '0');

        lcd.clear();
        lcd.print(num1);
      }
      else {
        num2 = num2 * 10 + (tecla - '0');

        lcd.clear();
        lcd.print(num1);

        if (op == 'A') lcd.print("+");
        if (op == 'B') lcd.print("-");
        if (op == 'C') lcd.print("*");
        if (op == 'D') lcd.print("/");

        lcd.print(num2);
      }
    }

    if (tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D') {

      if (num1 != 0 || tecla == 'B') {

        op = tecla;
        segundo = true;

        lcd.clear();
        lcd.print(num1);

        if (op == 'A') lcd.print("+");
        if (op == 'B') lcd.print("-");
        if (op == 'C') lcd.print("*");
        if (op == 'D') lcd.print("/");
      }
    }

    if (tecla == '#') {

      float resultado = 0;

      if (op == 'A') resultado = num1 + num2;
      if (op == 'B') resultado = num1 - num2;
      if (op == 'C') resultado = num1 * num2;

      if (op == 'D') {
        if (num2 != 0) {
          resultado = (float)num1 / num2;
        } else {
          lcd.clear();
          lcd.print("Error");
          delay(2000);

          num1 = 0;
          num2 = 0;
          op = 0;
          segundo = false;
          lcd.clear();
          return;
        }
      }

      lcd.clear();
      lcd.print(resultado);

      delay(3000);

      num1 = 0;
      num2 = 0;
      op = 0;
      segundo = false;

      lcd.clear();
    }
  }
}