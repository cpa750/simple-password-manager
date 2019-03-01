#include "Encrypt.h"

std::string CBC(std::string in, std::string key, std::string initializationVector)
{
    std::string plainText = padString(in);
    std::vector<State> states = cvtStrToStates(in);

    // TODO: Write the rest of the CBC algorithm
    for (int i {0}; i < states.size(); ++i)
    {
        if (i == 1)
        {
            int index {0};
            for (int j {0}; j < 4; ++j)
            {
                for (int k {0}; k < 4; ++k)
                {
                    states[i][k][j] = static_cast<u_char>(initializationVector[index++]);
                }
            }
        }
    }

}

std::vector<State> cvtStrToStates(std::string in)
{
    std::vector<State> out;
    for (int i {0}; i < in.size() / 16; ++i)
    {
        State s;
        std::string sub = in.substr(i, 16);
        int stringIndex {0};
        for (int i {0}; i < 4; ++i)
        {
            for (int j {0}; j < 4; ++j)
            {
                s[j][i] = static_cast<u_char>(sub[stringIndex++]);
            }
        }
        out.push_back(s);
    }
    return out;
}

std::string padString(std::string in)
{
    size_t inSize {in.size()};

    if (inSize < 16)
    {
        for (int i {0}; i < (16 - inSize); ++i) in += '0';
    }
    else
    {
        for (int i {0}; i < inSize % 16; ++i) in += '0';
    }
    return in;
}
