#ifndef CLOSE_H
#define CLOSE_H
#include <Command.h>

class Close : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // CLOSE_H
