#include <iostream>
using namespace std;

class Character
{
public:
    string name;
    double health;
    int level; // max 4. when taking cin use try catch for this.
    int hits_taken;
    virtual double *getAttack()
    {
        cout << "This is to get access to the attack array" << endl;
        return 0;
    };

public:
    Character()
    {
        name = "Annonymus";
        health = 0;
        level = 0;
        hits_taken = 0;
    }
    Character(string name1, double health1, int level1, int hits_taken1)
    {
        name = name1;
        health = health1;
        level = level1;
        hits_taken = hits_taken1;
    }
    virtual ~Character() {} // Virtual destructor
    virtual void display()
    {
        cout << "Name : " << name << endl;
        cout << "Health : " << health << endl;
        cout << "Level : " << level << endl;
        cout << endl;
    }

    bool operator==(const Character &other) const
    {
        return this->name == other.name;
    }
    friend istream &operator>>(istream &input, Character &obj)
    {
        string inputName;
        input >> inputName;

        if (inputName == "Fire")
        {
            obj = Character("Fire", 100.0, 0, 0); // Construct Fire object
        }
        else if (inputName == "Water")
        {
            obj = Character("Water", 150.0, 0, 0); // Construct Water object
        }
        else if (inputName == "Earth")
        {
            obj = Character("Earth", 200.0, 0, 0); // Construct Earth object
        }
        else if (inputName == "Air")
        {
            obj = Character("Air", 120.0, 0, 0); // Construct Air object
        }
        else
        {
            // Handle unknown input
            cerr << "Unknown character type: " << inputName << endl;
        }
        return input;
    }
    virtual void LevelUp()
    {
        cout << "this is main level up function" << endl;
    }
    virtual void inputAttack(int round)
    {
        cout << "this is main inputAttack function" << round << endl;
    }
};

/// Magic type classes below
class Water;

class Fire : public Character
{
protected:
    double attack[4];
    // Character weakness = "Water";
    Water *weakness; // specific to each magic. 1.5 times damage if weakness

public:
    Fire(string f, double h, int l, int h_t) : Character(f, h, l, h_t)
    {
        attack[0] = 10;
        attack[1] = 20;
        attack[2] = 30;
        attack[3] = 40;
    }
    virtual ~Fire() {}
    void Aggression()
    {
        for (int i = 0; i < 4; i++)
        {
            attack[i] = attack[i] * 1.05;
        }
    }

    void AttackFunction(Character *oponent, int attact_number)
    {
        oponent->hits_taken += 1;
        oponent->health = oponent->health - attack[attact_number];
    }
    // void ReceivingAttack()
    // {
    //     // we dont need this function as Attack function is handeling this already. repeating code is uncecessary. Since we cannot defend from attack, attak is always received so no need for a separate recieve attack function
    // }
    void LevelUp()
    {
        if (hits_taken > 0 && hits_taken % 3 == 0 && health >= 0.0 && level < 4)
        {
            int number = hits_taken / 3;
            health = 100;
            cout << "Character Level Up!" << endl;
            level++;

            for (int i = 0; i < 4; i++)
            {
                attack[i] += 1; // adding 1 to each attack// attack number increases by 1.
            }

            for (int i = 0; i < number; i++)
            {
                health = health * 1.10; // adding 10% to health depending upon the level. if we got 9 hits. we add 10% of total health 3 times.
            }
        }
    }
    void display() override
    {
        // displays the name, health, level, type, attacks, and weaknesses
        cout << "Name : " << name << endl;
        cout << "Health : " << health << endl;
        cout << "Level : " << level << endl;
        cout << "Type : Fire" << endl
             << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << "Attack " << i + 1 << " : " << attack[i] << endl;
        }
        cout << endl;
        cout << "Weakness : Water" << endl
             << endl
             << endl;
    }
    void inputAttack(int round)
    {
        // Aggression will be called for a fire type character if it has survived 2 rounds, it will be called at the start of the third round.
        if (round > 0 && round % 2 == 0)
        {
            cout << "Attacking power increases by 5%!!!" << endl;
            Aggression();
        }
    }
    double *getAttack() override
    {
        return attack;
    }
};

class Earth : public Character
{
protected:
    double attack[4];
    Fire *weakness;
    string type = "Earth";

public:
    Earth(string f, double h, int l, int h_t) : Character(f, h, l, h_t)
    {
        attack[0] = 10;
        attack[1] = 20;
        attack[2] = 30;
        attack[3] = 40;
    }
    virtual ~Earth() {}
    void AttackFunction(Character *oponent, int attact_number)
    {
        oponent->hits_taken += 1;
        oponent->health = oponent->health - attack[attact_number];
    }
    // void ReceivingAttack(Character * oponent)
    // {
    //     hits_taken += 1;
    //     health  -= 10;
    // }
    void LevelUp()
    {
        if (hits_taken > 0 && hits_taken % 3 == 0 && health >= 0.0 && level < 4)
        {
            int number = hits_taken / 3;
            health = 100;
            cout << "Character Level Up!" << endl;
            level++;

            for (int i = 0; i < 4; i++)
            {
                attack[i] += 1; // adding 1 to each attack// attack number increases by 1.
            }

            for (int i = 0; i < number; i++)
            {
                health = health * 1.10; // adding 10% to health depending upon the level. if we got 9 hits. we add 10% of total health 3 times.
            }
        }
    }
    void display() override
    {
        // displays the name, health, level, type, attacks, and weaknesses
        cout << "Name : " << name << endl;
        cout << "Health : " << health << endl;
        cout << "Level : " << level << endl;
        cout << "Type : Earth" << endl
             << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << "Attack " << i + 1 << " : " << attack[i] << endl;
        }
        cout << endl;
        cout << "Weakness : Fire" << endl
             << endl
             << endl;
    }

    double *getAttack() override
    {
        return attack;
    }

};

class Water : public Character
{
protected:
    double attack[4];
    Earth *weakness;
    string type = "Water";

public:
    Water(string f, double h, int l, int h_t) : Character(f, h, l, h_t)
    {
        attack[0] = 10;
        attack[1] = 20;
        attack[2] = 30;
        attack[3] = 40;
    }
    virtual ~Water() {}
    void regeneration()
    {
        health = health * 1.05;
    }
    void AttackFunction(Character *oponent, int attact_number)
    {
        oponent->hits_taken += 1;
        oponent->health = oponent->health - attack[attact_number];
    }
    // void ReceivingAttack()
    // {
    //     hits_taken += 1;
    // }
    void LevelUp()
    {
        if (hits_taken > 0 && hits_taken % 3 == 0 && health >= 0.0 && level < 4)
        {
            int number = hits_taken / 3;
            health = 100;
            cout << "Character Level Up!" << endl;
            level++;

            for (int i = 0; i < 4; i++)
            {
                attack[i] += 1; // adding 1 to each attack// attack number increases by 1.
            }

            for (int i = 0; i < number; i++)
            {
                health = health * 1.10; // adding 10% to health depending upon the level. if we got 9 hits. we add 10% of total health 3 times.
            }
        }
    }
    void display() override
    {
        // displays the name, health, level, type, attacks, and weaknesses
        cout << "Name : " << name << endl;
        cout << "Health : " << health << endl;
        cout << "Level : " << level << endl;
        cout << "Type : Water" << endl
             << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << "Attack " << i + 1 << " : " << attack[i] << endl;
        }
        cout << endl;
        cout << "Weakness : Earth" << endl
             << endl
             << endl;
    }
    void inputAttack(int round)
    {
        // Regeneration will be called for a water type character if it has survived 2 rounds, it will be called at the start of the third round.
        if (round > 0 && round % 2 == 0)
        {
            cout << "Health increases by 5%" << endl;
            regeneration();
        }
    }
    double *getAttack() override
    {
        return attack;
    }
};

class Air : public Character
{
protected:
    double attack[4];
    Earth *weakness;
    string type = "Air";

public:
    Air(string f, double h, int l, int h_t) : Character(f, h, l, h_t)
    {
        attack[0] = 10;
        attack[1] = 20;
        attack[2] = 30;
        attack[3] = 40;
    }
    virtual ~Air() {}
    void Meditation()
    {
        health = health * 1.10;
    }
    void AttackFunction(Character *oponent, int attact_number)
    {
        oponent->hits_taken += 1;
        oponent->health = oponent->health - attack[attact_number];
    }
    // void ReceivingAttack()
    // {
    //     hits_taken += 1;
    // }
    void LevelUp()
    {
        if (hits_taken > 0 && hits_taken % 3 == 0 && health >= 0.0 && level < 4)
        {
            int number = hits_taken / 3;
            health = 100;
            cout << "Character Level Up!" << endl;
            level++;

            for (int i = 0; i < 4; i++)
            {
                attack[i] += 1; // adding 1 to each attack// attack number increases by 1.
            }

            for (int i = 0; i < number; i++)
            {
                health = health * 1.10; // adding 10% to health depending upon the level. if we got 9 hits. we add 10% of total health 3 times.
            }
        }
    }
    void display() override
    {
        // displays the name, health, level, type, attacks, and weaknesses
        cout << "Name : " << name << endl;
        cout << "Health : " << health << endl;
        cout << "Level : " << level << endl;
        cout << "Type : Air" << endl
             << endl;

        for (int i = 0; i < 4; i++)
        {
            cout << "Attack " << i + 1 << " : " << attack[i] << endl;
        }
        cout << endl;
        cout << "Weakness : Earth" << endl
             << endl
             << endl;
    }
    void inputAttack(int round)
    {
        // Meditation will be called for a water type character if it has survived 4 rounds, it will be called at the start of the fifth round.
        // making correction. Meditation will be called for Air class not water.
        if (round > 0 && round % 4 == 0)
        {
            cout << "Health increases by 10%" << endl;
            Meditation();
        }
    }
    double *getAttack() override
    {
        return attack;
    }
};

class Player
{
public:
    string name;
    int count;
    Character **band;

public:
    Player(string name1)
    {
        name = name1;
        count = 0;
        band = NULL;
    }

    void addCharacter(string s, int pos)
    {
        if (s == "Fire" || s == "Water" || s == "Air" || s == "Earth")
        {
            Character **temp = new Character *[count + 1];
            // Create an instance of the appropriate derived class based on the input string
            Character *new_ch;

            if (s == "Fire")
            {
                new_ch = new Fire("Fire", 100.0, 0, 0);
                new_ch->name = "Fire";
            }
            else if (s == "Water")
            {
                new_ch = new Water("Water", 100, 0, 0);
            }
            else if (s == "Air")
            {
                new_ch = new Air("Air", 100, 0, 0);
            }
            else if (s == "Earth")
            {
                new_ch = new Earth("Earth", 100, 0, 0);
            }

            // checking position issues
            if (pos < 0)
            {
                cout << "Enter position greater than 0";
            }
            else if (pos == 0)
            {
                temp[pos] = new_ch;
            }
            else
            {
                for (int i = 0; i < pos; i++)
                {
                    temp[i] = band[i];
                }
                // adding new element
                temp[pos] = new_ch;
                // adding later elements
                for (int i = pos; i < count; i++)
                {
                    temp[i + 1] = band[i];
                }
            }
            // deleting old stuff
            delete[] band;
            count++;
            band = temp;
        }
        else
        {
            cout << "Please enter Fire or Water or Air or Earth on a empty list" << endl;
        }
    }

    void removeCharacter(string s, int position, string s2)
    {
        if (position < 1 || position > count)
        {
            // Position out of bounds, do nothing
            return;
        }

        if (band[position - 1]->name != s)
        {
            // Character at the given position doesn't match s, do nothing
            return;
        }

        // Delete the Character object at the specified position
        delete band[position - 1];

        // Shift elements in the array to the left
        for (int i = position - 1; i < count - 1; i++)
        {
            band[i] = band[i + 1];
        }

        // Decrement count
        count--;

        // If you want to add a new character after removing, you can call addCharacter here
        // For example:
        addCharacter(s2, position); // Replace "NewCharacterType" with the appropriate character type

        // If necessary, resize the array
        if (count > 0)
        {
            Character **temp = new Character *[count];
            for (int i = 0; i < count; i++)
            {
                temp[i] = band[i];
            }
            delete[] band;
            band = temp;
        }
        else
        {
            // If count is zero, delete the band array
            delete[] band;
            band = nullptr; // Set to nullptr to indicate an empty array
        }
    }

    void display()
    {
        cout << "Player Name: " << name << endl;
        cout << "Characters chosen: " << count << endl
             << endl;
        cout << "Characters list: " << endl;
        for (int i = 0; i < count; i++)
        {
            band[i]->display();
        }
    }
    void setCount(int number)
    {
        count = number;
    }
    bool lost()
    {
        int temp = 0;
        for (int i = 0; i < count; i++)
        {
            if (band[i]->health <= 0)
            {
                temp++;
            }
        }
        if (temp == count)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

/// game class
class Game
{
public:
    Character *selected_char_p1;
    Character *selected_char_p2;

    void formTeam(Player &p1, Player &p2, int number_of_characters)
    {
        cout << "Who will choose their characters first?" << endl;
        cout << "Press 1 for player 1. Press 2 for player 2: " << endl;
        int one_two;
        cin >> one_two;

        int players_done = 0;
        while (players_done != 2)
        {
            cout << "Choose your option player " << one_two << endl;
            cout << "a: "
                 << "Add Characters" << endl;
            cout << "b: "
                 << "Display Characters" << endl;
            cout << "c: "
                 << "Remove Characters" << endl;
            cout << "d: "
                 << "Done" << endl;

            char chosen;
            cin >> chosen;

            if (one_two == 1)
            {
                if (chosen == 'a')
                {
                    for (int i = 0; i < number_of_characters; i++)
                    {
                        try
                        {
                            string s1;
                            cout << "Chose chacter # " << i + 1 << endl;
                            cin >> s1;

                            // Validate the input
                            if (s1 != "Fire" && s1 != "Water" && s1 != "Air" && s1 != "Earth")
                            {
                                throw "Invalid input. Please choose from 'Fire', 'Water', 'Air', or 'Earth'.";
                            }
                            p1.addCharacter(s1, i);
                        }
                        catch (const char *errorMessage)
                        {
                            cout << "Error: " << errorMessage << endl;
                            cout << "Please re-enter the character." << endl;
                            i--; // Decrement i to allow re-entering the character
                        }
                    }
                    cout << "Team full for p1" << endl
                         << endl;
                }
                else if (chosen == 'b')
                {
                    cout << "These are the characters you can choose from : " << endl;
                    cout << "1) Fire    2) Water    3) Earth    4) Air" << endl
                         << endl;

                    cout << "Your currents characters are: " << endl;
                    p1.display();
                }
                else if (chosen == 'c')
                {
                    try
                    {
                        cout << "Name the character to remove from your list" << endl;
                        string to_remove;
                        cin >> to_remove;
                        if (to_remove != "Fire" && to_remove != "Air" && to_remove != "Water" && to_remove != "Earth")
                        {
                            throw "Error: invalid input. Enter either Fire, Air, Water, or Earth";
                        }
                        cout << "select position to remove it from" << endl;
                        int p;
                        cin >> p;
                        if (p < 1 || p1.band[p - 1]->name != to_remove)
                        {
                            throw "Error: The input character does not exist at given position";
                        }
                        cout << "Now add some other character here: " << endl;
                        string new_char;
                        cin >> new_char;
                        if (new_char != "Fire" && new_char != "Water" && new_char != "Air" && new_char != "Earth")
                        {
                            throw "Invalid input. Please choose from 'Fire', 'Water', 'Air', or 'Earth'.";
                        }
                        p1.removeCharacter(to_remove, p, new_char);
                    }
                    catch (const char *errorMessage)
                    {
                        cout << "Error: " << errorMessage << endl;
                        cout << "Please re-enter the character and position" << endl;
                    }
                }
                else if (chosen == 'd')
                {
                    one_two = 2;
                    players_done++;
                    cout << endl
                         << endl;
                }
            }
            else if (one_two == 2)
            {
                if (chosen == 'a')
                {
                    for (int i = 0; i < number_of_characters; i++)
                    {
                        try
                        {
                            string s2;
                            cout << "Chose chacter # " << i + 1 << endl;
                            cin >> s2;

                            // Validate the input
                            if (s2 != "Fire" && s2 != "Water" && s2 != "Air" && s2 != "Earth")
                            {
                                throw "Invalid input. Please choose from 'Fire', 'Water', 'Air', or 'Earth'.";
                            }

                            p2.addCharacter(s2, i);
                        }
                        catch (const char *errorMessage)
                        {
                            cout << "Error: " << errorMessage << endl;
                            cout << "Please re-enter the character." << endl;
                            i--; // Decrement i to allow re-entering the character
                        }
                    }
                    cout << "Team full for p2" << endl
                         << endl;
                }
                else if (chosen == 'b')
                {
                    cout << "These are the characters you can choose from : " << endl;
                    cout << "1) Fire    2) Water    3) Earth    4) Air" << endl
                         << endl;
                    cout << "Your currents characters are: " << endl;
                    p2.display();
                }
                else if (chosen == 'c')
                {
                    try
                    {
                        cout << "Name the character to remove from your list" << endl;
                        string to_remove;
                        cin >> to_remove;
                        if (to_remove != "Fire" && to_remove != "Air" && to_remove != "Water" && to_remove != "Earth")
                        {
                            throw "Error: invalid input. Enter either Fire, Air, Water, or Earth";
                        }
                        cout << "select position to remove it from" << endl;
                        int p;
                        cin >> p;
                        if (p < 1 || p2.band[p - 1]->name != to_remove)
                        {
                            throw "Error: The input character does not exist at given position";
                        }
                        cout << "Now add some other character here: " << endl;
                        string new_char;
                        cin >> new_char;
                        if (new_char != "Fire" && new_char != "Water" && new_char != "Air" && new_char != "Earth")
                        {
                            throw "Invalid input. Please choose from 'Fire', 'Water', 'Air', or 'Earth'.";
                        }
                        p2.removeCharacter(to_remove, p, new_char);
                    }
                    catch (const char *errorMessage)
                    {
                        cout << "Error: " << errorMessage << endl;
                        cout << "Please re-enter the character and position" << endl;
                    }
                }
                else if (chosen == 'd')
                {
                    one_two = 1;
                    players_done++;
                    cout << endl
                         << endl;
                }
            }
            else
            {
                cout << "Please press 1 or 2";
            }
        }
    }

    Character *selectCharacter(Player p)
    {
        int c_no;

        cout << "Choose your character: " << p.name << endl;
        for (int i = 1; i < p.count + 1; i++)
        {
            cout << i << " :  " << p.band[i - 1]->name << endl;
        }
        cin >> c_no;
        while (true)
        {
            try
            {
                if (c_no >= 1 && c_no <= p.count)
                {
                    return p.band[c_no - 1];
                }
                else
                {
                    throw out_of_range("Enter a number within your character range");
                }
            }
            catch (const out_of_range &e)
            {
                cerr << "Error: " << e.what() << endl;
                // Prompt the user to enter the value again
                cout << "Please enter a valid number: ";
                cin >> c_no;
            }
        }
        cout << endl;
    }

    void move1(Player p1)
    {
        if (selected_char_p1->health <= 0)
        {
            cout << "Character died!" << endl
                 << "Choose another character" << endl;

            for (int i = 0; i < p1.count; i++)
            {
                if (p1.band[i]->health > 0)
                {
                    cout << i + 1 << ") Character: " << p1.band[i]->name << "    Health: " << p1.band[i]->health;
                }
            }
            while (true)
            {
                int numb;
                cin >> numb;
                if (p1.band[numb - 1]->health > 0)
                {
                    selected_char_p1 = selectCharacter(p1);
                    break;
                }
                else
                {
                    cout << "Character already dead";
                }
            }
        }

        cout << "Select your move: " << p1.name << endl;
        cout << "1) Attack.   2) Switch.   3) Forfeit." << endl;
        cout << "Your health: " << selected_char_p1->health << "    "
             << "Hits Taken: " << selected_char_p1->hits_taken << endl;
        cout << "Enemy Health: " << selected_char_p2->health << endl;
        int mo;
        cin >> mo;
        if (mo == 1)
        {
            cout << "Choose your attack: " << endl;

            for (int i = 0; i < selected_char_p1->level + 1; i++)
            {
                cout << "Attack " << i + 1 << " = " << (selected_char_p1->getAttack())[i] << endl;
            }
            int att;
            cin >> att;
            selected_char_p2->health -= (selected_char_p1->getAttack())[att - 1];
            selected_char_p2->hits_taken++;
            cout << "Damage delt to Enemy"
                 << "!!!" << endl;
        }
        else if (mo == 2)
        {
            cout << "Which character would you select?" << endl;
            for (int i = 0; i < p1.count; i++)
            {
                cout << i + 1 << ") Character: " << p1.band[i]->name << "    Health: " << p1.band[i]->health;
            }
            while (true)
            {
                int numb;
                cin >> numb;
                if (p1.band[numb - 1]->health > 0)
                {
                    selected_char_p1 = selectCharacter(p1);
                    break;
                }
                else
                {
                    cout << "Character already dead";
                }
            }
        }
        else if (mo == 3)
        {
            cout << p1.name << " Lost! The opponent has won." << endl;
            for (int i = 0; i < p1.count; i++)
            {
                p1.band[i]->health = 0;
            }
            p1.lost();
        }
        else
        {
            cout << "Select 1,2, or 3" << endl;
        }
    }

    void move2(Player p2)
    {
        if (selected_char_p2->health <= 0)
        {
            cout << "Character died!" << endl
                 << "Choose another character" << endl;

            for (int i = 0; i < p2.count; i++)
            {
                if (p2.band[i]->health > 0)
                {
                    cout << i + 1 << ") Character: " << p2.band[i]->name << "    Health: " << p2.band[i]->health;
                }
            }
            while (true)
            {
                int numb;
                cin >> numb;
                if (p2.band[numb - 1]->health > 0)
                {
                    selected_char_p2 = selectCharacter(p2);
                    break;
                }
                else
                {
                    cout << "Character already dead";
                }
            }
        }

        cout << "Select your move:" << p2.name << endl;
        cout << "1) Attack.   2) Switch.   3) Forfeit." << endl;
        cout << "Your health: " << selected_char_p2->health << "    "
             << "Hits Taken: " << selected_char_p2->hits_taken << endl;
        cout << "Enemy Health: " << selected_char_p1->health << endl
             << endl;
        int mo;
        cin >> mo;
        if (mo == 1)
        {
            cout << "Choose your attack: " << endl;

            for (int i = 0; i < selected_char_p2->level + 1; i++)
            {
                cout << "Attack " << i + 1 << " = " << (selected_char_p2->getAttack())[i] << endl;
            }
            int att;
            cin >> att;
            selected_char_p1->health -= (selected_char_p2->getAttack())[att - 1];
            selected_char_p1->hits_taken++;
            cout << "Damage delt to Enemy"
                 << "!!!" << endl;
        }
        else if (mo == 2)
        {
            cout << "Which character would you select?" << endl;
            for (int i = 0; i < p2.count; i++)
            {
                cout << i + 1 << ") Character: " << p2.band[i]->name << "    Health: " << p2.band[i]->health << endl;
            }
            while (true)
            {
                int numb;
                cin >> numb;
                cout << "Are you sure?" << endl;
                if (p2.band[numb - 1]->health > 0)
                {
                    selected_char_p2 = selectCharacter(p2);
                    break;
                }
                else
                {
                    cout << "Character already dead";
                }
            }
        }
        else if (mo == 3)
        {
            cout << p2.name << " Lost! The opponent has won." << endl;
            for (int i = 0; i < p2.count; i++)
            {
                p2.band[i]->health = 0;
            }
            p2.lost();
        }
        else
        {
            cout << "Select 1,2, or 3" << endl;
        }
    }

    void startBattle(Player p1, Player p2)
    {
        int round = 0;
        while (true)
        {
            if (round < 4)
            {
                cout << "////////// Round " << round + 1 << " //////////" << endl;
            }

            // p1 move
            for (int i = 0; i < p1.count; i++)
            {
                p1.band[i]->LevelUp();
                p1.band[i]->inputAttack(round);
            }
            move1(p1);
            if (p1.lost() == true || p2.lost() == true)
            {
                break;
            }

            cout << "Move change" << endl
                 << endl;

            // p2 move
            for (int i = 0; i < p2.count; i++)
            {
                p2.band[i]->LevelUp();
                p1.band[i]->inputAttack(round);
            }
            move2(p2);
            if (p1.lost() == true || p2.lost() == true)
            {
                break;
            }
            cout << "Move change" << endl
                 << endl;
            round++;
        }
    }
};

int main()
{
    cout << "Hello" << endl;

    int number_of_characters;
    Player p1("Player 1"), p2("Player 2");

    cout << "Select the number of characters per team: " << endl;
    cin >> number_of_characters;

    Game g1;
    g1.formTeam(p1, p2, number_of_characters);
    cout << "//////////////Pre Battle///////////////" << endl;
    g1.selected_char_p1 = g1.selectCharacter(p1);
    g1.selected_char_p2 = g1.selectCharacter(p2);

    cout << endl;
    g1.startBattle(p1, p2);

    cout << "Game Over! Bye Bye" << endl;
    return 0;
}