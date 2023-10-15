#include <iostream>
#include "tokenizer.h"

namespace tokenizer {
    Tokenizer::Tokenizer(const std::string &filename) {
        this->filename = filename;
        this->line_num = 1;
        this->pos = 0;
        this->file = fopen(filename.c_str(), "r");
        if (this->file == NULL) {
            std::cout << "Error opening file " << filename << std::endl;
            exit(1);
        }
    }

    Tokenizer::~Tokenizer() {
        fclose(this->file);
    }

    void Tokenizer::tokenize(void) {
        this->tokens.clear();
        char c;
        while ((c = fgetc(this->file)) != EOF) {
            if (c == '\n') {
                this->line_num++;
                this->pos = 0;
            } else {
                this->pos++;
            }
            if(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                continue;
            }
            if (c == '#') {
                while ((c = fgetc(this->file)) != EOF) {
                    if (c == '\n') {
                        this->line_num++;
                        this->pos = 0;
                        break;
                    } else {
                        this->pos++;
                    }
                }
                continue;
            }
            if (c == '/') {
                c = fgetc(this->file);
                if (c == '/') {
                    while ((c = fgetc(this->file)) != EOF) {
                        if (c == '\n') {
                            this->line_num++;
                            this->pos = 0;
                            break;
                        } else {
                            this->pos++;
                        }
                    }
                    continue;
                } else if (c == '*') {
                    while ((c = fgetc(this->file)) != EOF) {
                        if (c == '\n') {
                            this->line_num++;
                            this->pos = 0;
                        } else {
                            this->pos++;
                        }
                        if (c == '*') {
                            c = fgetc(this->file);
                            if (c == '/') {
                                break;
                            }
                        }
                    }
                    continue;
                } else {
                    ungetc(c, this->file);
                    c = '/';
                }
            }
            if (c == '"') {
                std::string str;
                while ((c = fgetc(this->file)) != EOF) {
                    if (c == '\n') {
                        this->line_num++;
                        this->pos = 0;
                        break;
                    } else {
                        this->pos++;
                    }
                    if (c == '"') {
                        break;
                    }
                    str += c;
                }
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::STRING;
                token.str = str;
                this->tokens.push_back(token);
                continue;
            }
            if (c == '\'') {
                c = fgetc(this->file);
                if (c == '\\') {
                    c = fgetc(this->file);
                    if (c == 'n') {
                        c = '\n';
                    } else if (c == 't') {
                        c = '\t';
                    } else if (c == 'r') {
                        c = '\r';
                    } else if (c == '0') {
                        c = '\0';
                    } else if (c == '\'') {
                        c = '\'';
                    } else if (c == '\\') {
                        c = '\\';
                    } else {
                        std::cout << "Invalid escape sequence" << std::endl;
                        exit(1);
                    }
                }
                char c2 = fgetc(this->file);
                if (c2 != '\'') {
                    std::cout << "Invalid character constant" << std::endl;
                    exit(1);
                }
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::CHAR;
                token.c = c;
                this->tokens.push_back(token);
                continue;
            }
            if (c == '(') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::LPAREN;
                this->tokens.push_back(token);
                continue;
            }
            if (c == ')') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::RPAREN;
                this->tokens.push_back(token);
                continue;
            }
            if (c == '{') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::LBRACE;
                this->tokens.push_back(token);
                continue;
            }
            if (c == '}') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::RBRACE;
                this->tokens.push_back(token);
                continue;
            }
            if (c == ',') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::COMMA;
                this->tokens.push_back(token);
                continue;
            }
            if (c == ';') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::SEMICOLON;
                this->tokens.push_back(token);
                continue;
            }

            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '<' || c == '>') {
                Token token;
                token.line_num = this->line_num;
                token.pos = this->pos;
                token.type = TokenType::OPERATOR;
                token.str = c;
                this->tokens.push_back(token);
                continue;
            }
            if (c == '&') {
                c = fgetc(this->file);
                if (c == '&') {
                    Token token;
                    token.line_num = this->line_num;
                    token.pos = this->pos;
                    token.type = TokenType::OPERATOR;
                    token.str = "&&";
                    this->tokens.push_back(token);
                    continue;
                } else {
                    Token token;
                    token.line_num = this->line_num;
                    token.pos = this->pos;
                    token.type = TokenType::OPERATOR;
                    token.str = "&";
                    this->tokens.push_back(token);
                    ungetc(c, this->file);
                    continue;
                }
            }
            if (c == '|') {
                c = fgetc(this->file);
                if (c == '|') {
                    Token token;
                    token.line_num = this->line_num;
                    token.pos = this->pos;
                    token.type = TokenType::OPERATOR;
                    token.str = "||";
                    this->tokens.push_back(token);
                    continue;
                } else {
                    Token token;
                    token.line_num = this->line_num;
                    token.pos = this->pos;
                    token.type = TokenType::OPERATOR;
                    token.str = "|";
                    this->tokens.push_back(token);
                    ungetc(c, this->file);
                    continue;
                }
            }


        }
        this->tokenized = true;
    }

    Token Tokenizer::next_token() {
        if (!this->tokenized) {
            this->tokenize();
        }

        Token token;
        token.line_num = this->line_num;
        token.pos = this->pos;
        token.type = TokenType::INT;
        token.value = 0;
        return token;
    }
};