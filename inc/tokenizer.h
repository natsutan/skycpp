#include <string>
#include <vector>

namespace tokenizer {
    enum class TokenType {
        INT,
    };

    class Token {
    public:
        TokenType type;
        int value;
        int line_num;
        int pos;
    };

    class Tokenizer {
    public:
        Tokenizer(const std::string &filename);
        ~Tokenizer();
        Token next_token();
    private:
        std::string filename;
        std::vector<Token> tokens;
        int line_num;
        int pos;
        FILE* file;
    };

};


