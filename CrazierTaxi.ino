#include <LiquidCrystal.h>
#include <LCDBitmap.h>

#include "Canvas.h"
#include "Car.h"
#include "Player.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

LCDBitmap bmp(&lcd, 0, 0);

Player player(Pos.CENTER);
Canvas canvas(3, 8);
Car cars[10];

void setup() {
    canvas.begin();
    // lcd.begin(16,2);
    // bmp.begin();
    // bmp.pixel(0, 0, ON, UPDATE);
    // bmp.pixel(40, 1, ON, UPDATE);
    // bmp.pixel(1, 0, ON, UPDATE);

}
 
void loop() {
    canvas.clear();
    for (Car car : cars) car.draw();
    player.draw();
    canvas.render();
}
