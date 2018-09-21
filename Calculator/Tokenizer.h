#pragma once
#include <exception>
#include "Token.h"
#define MAX_INPUT_LENGTH 200

class Tokenizer {
    char m_input[MAX_INPUT_LENGTH];
    int m_inputLength = -1;
    int m_inputIdx = -1;
    Token m_current;

    // Converts a c-string token of the input into
    // a Token instance.
    void tokenize (const char * tokStr);

public:

    // Initializes this Tokenizer to tokenize the given input. 
    // When init is called multiple times, the Token stream is
    // reset and previous state of the Tokenizer is erased.
    void init (const char * input);
    
    // Returns the current Token.
    // @throws UninitializedTokenizerException if init hasn't
    //     been called
    Token getCurrent ();

    // Updates current Token and consumes more of the input.
    // Once all of the input has been consumed, all calls to
    // next will return false.
    //
    // @return an indicator of whether the stream was advanced.
    // @throws UninitializedTokenizerException if init hasn't
    //     been called
    bool next ();
};

// Exception class for Tokenizer method calls that happen
// before init.
class UninitializedTokenizerException : public std::exception {
public:
    virtual const char * what() const throw();
};
