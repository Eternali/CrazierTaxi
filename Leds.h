class Leds : public Canvas {

public:
    Leds(unsigned int width, unsigned int height, std::vector<std::vector<int>> pins);

    void begin();
    void render();

private:
    std::vector<std::vector<int>> pins {  };

};