#ifndef MOVE_H
#define MOVE_H
#include <Command.h>

class Move: public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // MOVE_H
