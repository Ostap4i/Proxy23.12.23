#include <iostream>
#include <unordered_map>

class Character {
private:
    char symbol;
    int size;
    std::string font;

public:
    Character(char symbol, int size, std::string font) : symbol(symbol), size(size), font(font) {}

    void draw() {
\
        std::cout << "Character: " << symbol << ", Size: " << size << ", Font: " << font << std::endl;
    }


};


class CharacterFactory {
public:

    std::unordered_map<char, Character*> characters;


    Character* getCharacter(char symbol, int size, std::string font) {
        if (characters.find(symbol) != characters.end()) {
       
            return characters[symbol];
        }
        else {
            Character* newCharacter = new Character(symbol, size, font);
            characters[symbol] = newCharacter;
            return newCharacter;
        }
    }
};

int main() {
  
    CharacterFactory characterFactory;

    Character* charA = characterFactory.getCharacter('A', 12, "Arial");
    charA->draw();

    Character* charB = characterFactory.getCharacter('B', 14, "Times New Roman");
    charB->draw();

    Character* charA2 = characterFactory.getCharacter('A', 12, "Arial");  
    charA2->draw();


    return 0;
}