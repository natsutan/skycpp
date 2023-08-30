#include "tokenizer.h"

namespace tokenizer {
    Tokenizer::Tokenizer(const std::string &filename) {
        this->filename = filename;
        this->line_num = 1;
        this->pos = 0;
        this->file = fopen(filename.c_str(), "r");
    }

    Tokenizer::~Tokenizer() {
        fclose(this->file);
    }

    Token Tokenizer::next_token() {
        Token token;
        token.line_num = this->line_num;
        token.pos = this->pos;
        token.type = TokenType::INT;
        token.value = 0;
        return token;
    }
};