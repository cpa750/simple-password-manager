#include "Encrypt.h"

std::string CBC(std::string in, std::string key, std::string initializationVector)
{
    std::string plainText = padString(in);
    std::vector<State> states = cvtStrToStates(in);
    std::string out {""};
    State toXor;

    std::array<u_char, 176> keyIn;
    for (int i {0}; i < 176; ++i)
    {
        keyIn[i] = static_cast<u_char>(key[i]);
    }

    AES128 aes;

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
                    states[i][k][j] ^= static_cast<u_char>(initializationVector[index++]);
                    // Need to xor each element in the state with the initialization vector
                }
            }
            toXor = aes.cipher(states[i], keyIn);
            out += cvtStateToStr(toXor);
        }
        else
        {
            for (int j {0}; j < 4; ++j)
            {
                for (int k {0}; k < 4; ++k)
                    states[i][k][j] ^= toXor[k][j];
            }
            toXor = aes.cipher(states[i], keyIn);
            out += cvtStateToStr(toXor);
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
        for (int j {0}; j < 4; ++j)
        {
            for (int k {0}; k < 4; ++k)
            {
                s[k][j] = static_cast<u_char>(sub[stringIndex++]);
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
        for (int i {0}; i < (16 - inSize); ++i) in += static_cast<char>(0x00);
    }
    else
    {
        for (int i {0}; i < inSize % 16; ++i) in += static_cast<char>(0x00);
    }
    return in;
}

std::string cvtStateToStr(State in)
{
    std::string out;
    for (int i {0}; i < 4; ++i)
    {
        for (int j {0}; j < 4; ++j)
            out.push_back(static_cast<char>(in[j][i]));
    }
    return out;
}

std::string CBC(State stateIn, std::array<u_char, 176> keyIn, std::array<u_char, 16> initializationVector)
{
    /*
     * This CBC function is to test that the algorithm works properly with
     * the test vectors
     */
    State toXor;
    std::string out;
    std::vector<State> states {stateIn};

    AES128 aes;
    for (int i {0}; i < states.size(); ++i)
    {
        if (i == 1)
        {
            int index {0};
            for (int j {0}; j < 4; ++j)
            {
                for (int k {0}; k < 4; ++k)
                {
                    states[i][k][j] ^= static_cast<u_char>(initializationVector[index++]);
                    // Need to xor each element in the state with the initialization vector
                }
            }
            toXor = aes.cipher(states[i], keyIn);
            out += cvtStateToStr(toXor);
        }
        else
        {
            for (int j {0}; j < 4; ++j)
            {
                for (int k {0}; k < 4; ++k)
                    states[i][k][j] ^= toXor[k][j];
            }
            toXor = aes.cipher(states[i], keyIn);
            out += cvtStateToStr(toXor);
        }
    }
    for (int i{0}; i < 4; ++i)
    {
        for (int j{0}; j < 4; ++j)
        {
            std::cout << states[1][i][j];
            if (j == 3) std::cout << '\n';
        }
    }
    return out;
}
