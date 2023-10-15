#include <string>
#include <vector>

namespace tokenizer {
    enum class TokenType {
        INT,
        CHAR,
        OPERATOR,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        IDENTIFIER,
        STRING,
        IF,
        ELSE,
        FOR,
        WHILE,
        SIZEOF,
        COMMA,
        SEMICOLON,
        TK_EOF
    };

    class Token {
    public:
        TokenType type;
        int value;
        char c;
        std::string str;
        int line_num;
        int pos;
    };

    class Tokenizer {
    public:
        Tokenizer(const std::string &filename);
        ~Tokenizer();
        void tokenize(void);
        Token next_token();
    private:
        std::string filename;
        std::vector<Token> tokens;
        int line_num{0};
        int pos{0};
        FILE* file;
        bool tokenized{false};
    };

};


