#include <iostream>
#include <string>
#include <vector>

// Define the possible states for our Finite State Machine
enum states
{
    START,      // Initial state
    CMD_START,  // Transitioned when a command begins 
    WHITESPACE, // Handling spaces between arguments
    CMD_END,    // Successful termination state
    CMD_ERR,    // Error state if syntax is invalid
};

class LEXCTX{
    private:
    public:
    std::string buffer; // Command line buffer
    int bufferSize; // Command line buffer Size
    int currentLn;  // Tracks current line (for multi-line scripts)
    int charIdx;     // Tracks current character index
    char currChar;  // Stores the character currently being evaluated
    void setBuffer(std::string str);
    int stepLn();
    int stepIdx();
    void setChar(char newChar);
};

void LEXCTX::setBuffer(std::string str){
    this->bufferSize = str.length();
    this->buffer = str;
    this->currentLn = 0;
    this->charIdx = 0;
    this->currChar = str[charIdx];
}

int LEXCTX::stepLn(){
    this->currentLn++;
    return this->currentLn;
}

int LEXCTX::stepIdx(){
    this->charIdx++;
    return this->charIdx;
}

void LEXCTX::setChar(char newChar){
    this->currChar = newChar;
}



// Finite State Machine class to manage state transitions
class FSM
{
private:
    states currState = START; // Default starting state

public:
    void exec(LEXCTX &ctx);
    states getState() { return currState; }
};

// Logic for state transitions based on current state and input
void FSM::exec(LEXCTX &ctx)
{
    {
        switch (currState)
        {
        case START:
            // TODO: Logic to move from START to CMD_START or CMD_ERR
            break;

        case CMD_START:
            // TODO: Logic to parse the command name
            break;

        case WHITESPACE:
            // TODO: Logic to skip spaces or move to next argument
            break;

        case CMD_END:
            // Terminal state: process is complete
            break;

        case CMD_ERR:
            // Terminal state: process encountered an error
            break;
        default:
            break;
        }
    }
}



// Command Lexer class to tokenize the input string
class CMDLEX
{
private:
    FSM fsm;        // Instance of the state machine
    LEXCTX ctx;
public:
    CMDLEX();
    void scan(std::string cmd);
};

// Initialize the Lexer with default values
CMDLEX::CMDLEX()
{

}
// A : Iterates through the input string and drives the FSM
// B : Continue running the FSM until it reaches a termination state (End or Error)
// C : Update currentState to avoid an infinite loop if FSM doesn't change it
void CMDLEX::scan(std::string cmd)
{
    states currentState = this->fsm.getState();
    LEXCTX lexCtx = this->ctx;
    lexCtx.setBuffer(cmd);
    // B
    while (currentState != CMD_END && currentState != CMD_ERR) {
        this->fsm.exec(lexCtx);
        
        
    // C    
        currentState = this->fsm.getState(); 
    }
}

int main()
{
    // Example command input
    std::string cmd = "/tp 0 10 0";
    
    // Initialize and run the lexer
    CMDLEX cmdLexer;
    cmdLexer.scan(cmd);
    
    return 0;
}