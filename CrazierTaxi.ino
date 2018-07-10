#include <LiquidCrystal.h>
#include <LCDBitmap.h>

#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

LCDBitmap bmp(&lcd, 0, 0);

std::vector<std::vector<int>> pins {
    { 0, 1, 2, 3, 4, 5, 6, 7 },
    { 8, 9 },
};
Leds canvas(2, 8, pins);
Player player(&canvas, 1);
// Car cars[10];

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
    // for (Car car : cars) car.draw();
    // player.draw();
    canvas.render();
}
