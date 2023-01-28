#include <iomanip>
#include <sstream>
#include <math.h>

/*
    Returns the finger id for a certain key pressed.
    Finger id: Left hand: 1 (thumb) - 5 (pinky), Right Hand: 6 (thumb) - 10 (pinky)
    Key: Input key on the keyboard, e.g. 'a' or '.'
*/
int get_finger_for_key(char key)
{
    return 1;
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
    return 1;
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