#ifndef OPEN_H
#define OPEN_H
#include <Command.h>

class Open : public Command{
    public:
        virtual std::string execute (std::vector<std::string> words, Interface& location);
};

#endif // OPEN_H
