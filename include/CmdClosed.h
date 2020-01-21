#ifndef CLOSED_H
#define CLOSED_H
#include <Command.h>

class Closed : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};


#endif // CLOSED_H
