#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

std::vector<std::vector<int>> pins {
    { 3, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12 },
};
Leds canvas(2, 8, pins);
Player player(&canvas, 1);
// Car cars[10];

void setup() {
    Serial.begin(9600);
    canvas.begin();
//    attachInterrupt();
}
 
void loop() {
    canvas.clear();
    // for (Car car : cars) car.draw();
    player.draw();
    canvas.render();
}
