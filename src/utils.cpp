#include <iomanip>
#include <sstream>
#include <math.h>
#include <set>
#include <map>

std::map<char, int> rows_for_keys;
std::map<char, int> finger_for_keys;

void init_utils()
{
    std::set<char> first_row= { '1', '2', '3', '4','5', '6', '7', '8','9', '0', '-', '=' };
    std::set<char> second_row= { 'Q', 'W', 'E', 'R', 'T','Y', 'U', 'I', 'O', 'P','[', ']', 'q', 'w', 'e','r', 't', 'y', 'u', 'i','o', 'p' };
    std::set<char> third_row= { 'A', 'S', 'D', 'F', 'G','H', 'J', 'K', 'L', ';', ':', 'a', 's', 'd', 'f','g', 'h', 'j', 'k', 'l' };
    std::set<char> fourth_row= { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.',  '/', 'z', 'x', 'c', 'v','b', 'n', 'm' };
    
    for(const auto& c : first_row)
    {
      rows_for_keys[c] = 1;
    }
    
    for(const auto& c : second_row)
    {
      rows_for_keys[c] = 2;
    }
    
    for(const auto& c : third_row)
    {
      rows_for_keys[c] = 3;
    }
    
    for(const auto& c : fourth_row)
    {
      rows_for_keys[c] = 4;
    }
    
    rows_for_keys[' '] = 5;


    //first row
    finger_for_keys['1'] = 1;
    finger_for_keys['2'] = 2;
    finger_for_keys['3'] = 3;
    finger_for_keys['4'] = 4;
    finger_for_keys['5'] = 4;
    finger_for_keys['6'] = 7;
    finger_for_keys['7'] = 7;
    finger_for_keys['8'] = 8;
    finger_for_keys['9'] = 9;
    finger_for_keys['0'] = 10;
    finger_for_keys['-'] = 10;
    finger_for_keys['='] = 10;
    //second row
    finger_for_keys['q'] = 1;
    finger_for_keys['Q'] = 1;
    finger_for_keys['w'] = 2;
    finger_for_keys['W'] = 2;
    finger_for_keys['e'] = 3;
    finger_for_keys['E'] = 3;
    finger_for_keys['R'] = 4;
    finger_for_keys['r'] = 4;
    finger_for_keys['T'] = 4;
    finger_for_keys['t'] = 4;
    finger_for_keys['Y'] = 7;
    finger_for_keys['y'] = 7;
    finger_for_keys['U'] = 7;
    finger_for_keys['u'] = 7;
    finger_for_keys['I'] = 8;
    finger_for_keys['i'] = 8;
    finger_for_keys['O'] = 9;
    finger_for_keys['o'] = 9;
    finger_for_keys['P'] = 10;
    finger_for_keys['p'] = 10;

    //Third row
    finger_for_keys['A'] = 1;
    finger_for_keys['a'] = 1;
    finger_for_keys['S'] = 2;
    finger_for_keys['s'] = 2;
    finger_for_keys['D'] = 3;
    finger_for_keys['d'] = 3;
    finger_for_keys['F'] = 4;
    finger_for_keys['f'] = 4;
    finger_for_keys['G'] = 4;
    finger_for_keys['g'] = 4;
    finger_for_keys['H'] = 7;
    finger_for_keys['h'] = 7;
    finger_for_keys['J'] = 7;
    finger_for_keys['j'] = 7;
    finger_for_keys['K'] = 8;
    finger_for_keys['k'] = 8;
    finger_for_keys['L'] = 9;
    finger_for_keys['l'] = 9;
    finger_for_keys[';'] = 10;
    finger_for_keys[':'] = 10;
    //Fourth row
    finger_for_keys['Z'] = 1;
    finger_for_keys['z'] = 1;
    finger_for_keys['X'] = 2;
    finger_for_keys['x'] = 2;
    finger_for_keys['C'] = 3;
    finger_for_keys['c'] = 3;
    finger_for_keys['V'] = 4;
    finger_for_keys['v'] = 4;
    finger_for_keys['B'] = 4;
    finger_for_keys['b'] = 4;
    finger_for_keys['N'] = 7;
    finger_for_keys['n'] = 7;
    finger_for_keys['M'] = 7;
    finger_for_keys['m'] = 7;
    finger_for_keys[','] = 8;
    finger_for_keys['.'] = 9;
    finger_for_keys['/'] = 10;    
}

/*
    Returns the finger id for a certain key pressed.
    Finger id: Left hand: 1 (thumb) - 5 (pinky), Right Hand: 6 (thumb) - 10 (pinky)
    Key: Input key on the keyboard, e.g. 'a' or '.'
*/
int get_finger_for_key(char key)
{
  return finger_for_keys[key];    
}

/*
    Returns the row on the keyboard of a certain key.
    Row 1: The row containing letters and special chars
    Row 2: qwerty...
    Row 3: asdf...
    Row 4: zxcv ,. ...
*/
int get_row_for_key(char key)
{
  return rows_for_keys[key];
}

std::string float_to_prec(float f, int decimals)
{
    if(((long) f) == f)
        return std::to_string((int) f);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(decimals) << f;
    std::string s = stream.str();

    return s;
}