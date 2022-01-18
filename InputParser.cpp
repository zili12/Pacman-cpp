#include "InputParser.h"

void InputParser::checkMode()
{
    if (cmdOptionExists("-save"))
    {
        if (cmdOptionExists("-load") || cmdOptionExists("load"))
            throw InvalidGameModeException();
        mode = Mode::SAVE;
    }

    else if (cmdOptionExists("-load"))
    {
        if (cmdOptionExists("[-silent]"))
            mode = Mode::SILENT;
        else
            mode = Mode::LOAD;
    }
    else
        throw InvalidGameModeException();
}