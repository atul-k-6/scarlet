#include "lexer.hh"
namespace scarlet {
namespace lexer {

#define ERROR_LOCATION                                                         \
  file_path.substr(0, file_path.length() - 1) + ":" +                          \
      std::to_string(line_number) + ":" + std::to_string(col_number)

void lexer::tokenize() {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    error_recovery.emplace_back(std::make_pair(
        "Unable to open the file> " + file_path, "Please check file path"));
    success = false;
    return;
  }

  char ch;
  while (file.get(ch)) {
    if (ch == '(') {
      tokens.emplace_back(token::TOKEN::OPEN_PARANTHESES, line_number);
      col_number++;
    } else if (ch == ')') {
      tokens.emplace_back(token::TOKEN::CLOSE_PARANTHESES, line_number);
      col_number++;
    } else if (ch == '{') {
      tokens.emplace_back(token::TOKEN::OPEN_BRACE, line_number);
      col_number++;
    } else if (ch == '}') {
      tokens.emplace_back(token::TOKEN::CLOSE_BRACE, line_number);
      col_number++;
    } else if (ch == ';') {
      tokens.emplace_back(token::TOKEN::SEMICOLON, line_number);
      col_number++;
    } else if (ch == '[') {
      tokens.emplace_back(token::TOKEN::OPEN_BRACKET, line_number);
    } else if (ch == ']') {
      tokens.emplace_back(token::TOKEN::CLOSE_BRACKET, line_number);
    } else if (ch == ':') {
      tokens.emplace_back(token::TOKEN::COLON, line_number);
      col_number++;
    } else if (ch == '?') {
      tokens.emplace_back(token::TOKEN::QUESTION_MARK, line_number);
      col_number++;
    } else if (ch == ',') {
      tokens.emplace_back(token::TOKEN::COMMA, line_number);
      col_number++;
    } else if (ch == '~') {
      tokens.emplace_back(token::TOKEN::TILDE, line_number);
      col_number++;
    } else if (ch == '+') {
      file.get(ch);
      if (ch == '+') {
        tokens.emplace_back(token::TOKEN::INCREMENT_OPERATOR, line_number);
        col_number++;
      } else if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_SUM, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::PLUS, line_number);
      }
      col_number++;
    } else if (ch == '*') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_PRODUCT, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::ASTERISK, line_number);
      }
      col_number++;
    } else if (ch == '/') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_DIVISION, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::FORWARD_SLASH, line_number);
      }
      col_number++;
    } else if (ch == '%') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_REMAINDER, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::PERCENT_SIGN, line_number);
      }
      col_number++;
    } else if (ch == '&') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_AND, line_number);
        col_number += 2;
      } else if (ch == '&') {
        tokens.emplace_back(token::TOKEN::LAND, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::AAND, line_number);
        col_number++;
      }
    } else if (ch == '|') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_OR, line_number);
        col_number += 2;
      } else if (ch == '|') {
        tokens.emplace_back(token::TOKEN::LOR, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::AOR, line_number);
        col_number++;
      }
    } else if (ch == '^') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_XOR, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::XOR, line_number);
      }
      col_number++;
    } else if (ch == '!') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::NOTEQUAL, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::NOT, line_number);
        col_number++;
      }
    } else if (ch == '=') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::EQUAL, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::ASSIGNMENT, line_number);
        col_number++;
      }
    } else if (ch == '>') {
      file.get(ch);
      if (ch == '>') {
        file.get(ch);
        if (ch == '=') {
          tokens.emplace_back(token::TOKEN::COMPOUND_RIGHTSHIFT, line_number);
          col_number++;
        } else {
          file.seekg(-1, std::ios::cur);
          tokens.emplace_back(token::TOKEN::RIGHT_SHIFT, line_number);
        }
        col_number += 2;
      } else if (ch == '=') {
        tokens.emplace_back(token::TOKEN::GREATERTHANEQUAL, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::GREATERTHAN, line_number);
        col_number++;
      }
    } else if (ch == '<') {
      file.get(ch);
      if (ch == '<') {
        file.get(ch);
        if (ch == '=') {
          tokens.emplace_back(token::TOKEN::COMPOUND_LEFTSHIFT, line_number);
          col_number++;
        } else {
          file.seekg(-1, std::ios::cur);
          tokens.emplace_back(token::TOKEN::LEFT_SHIFT, line_number);
        }
        col_number += 2;
      } else if (ch == '=') {
        tokens.emplace_back(token::TOKEN::LESSTHANEQUAL, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::LESSTHAN, line_number);
        col_number++;
      }
    } else if (ch == '-') {
      file.get(ch);
      if (ch == '=') {
        tokens.emplace_back(token::TOKEN::COMPOUND_DIFFERENCE, line_number);
        col_number += 2;
      } else if (ch == '-') {
        tokens.emplace_back(token::TOKEN::DECREMENT_OPERATOR, line_number);
        col_number += 2;
      } else if (ch == '>') {
        tokens.emplace_back(token::TOKEN::ARROW_OPERATOR, line_number);
        col_number += 2;
      } else {
        file.seekg(-1, std::ios::cur);
        tokens.emplace_back(token::TOKEN::HYPHEN, line_number);
        col_number++;
      }
    } else if (ch == '\'') {
      file.get(ch);
      std::string tmp;
      col_number += 2;
      if (ch == '\\') {
        // parse the next character as escape character
        file.get(ch);
        col_number++;
        if (regex.matchEscape(ch)) {
          tmp += token::char_to_esc(ch);
        } else {
          success = false;
          tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
          error_recovery.emplace_back(
              std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET +
                                 " " + "unkown escape character " + tmp,
                             "please use escape characters from c standard"));
        }
      } else if (regex.matchASCIIPrintable(ch) and ch != '\'') {
        tmp += ch;
      } else {
        success = false;
        tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
        error_recovery.emplace_back(
            std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET + " " +
                               "unkwown character " + tmp,
                           "please use characters from c standard"));
      }
      file.get(ch);
      col_number++;
      if (ch != '\'' and success != false) {
        success = false;
        tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
        error_recovery.emplace_back(
            std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET + " " +
                               "no end quote for character " + tmp,
                           "please add end quotes"));
      } else {
        tokens.emplace_back(token::Token(token::TOKEN::CHAR, tmp, line_number));
      }
      col_number++;
    } else if (ch == '\"') {
      std::string literal;
      file.get(ch);
      col_number += 2;
      while (ch != '"' and regex.matchASCIIPrintable(ch)) {
        if (ch == '\\') {
          // parse the next character as escape character
          file.get(ch);
          col_number++;
          if (regex.matchEscape(ch)) {
            literal += token::char_to_esc(ch);
          } else {
            success = false;
            tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
            error_recovery.emplace_back(std::make_pair(
                ERROR_LOCATION + " " + RED + "error:" + RESET + " " +
                    "bad escape character in " + literal + ": " + ch,
                "please use escape characters from c standard"));
          }
        } else if (regex.matchASCIIPrintable(ch) and ch != '\\') {
          literal += ch;
        } else { // will this ever be called?
          success = false;
          tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
          error_recovery.emplace_back(std::make_pair(
              ERROR_LOCATION + " " + RED + "error:" + RESET + " " +
                  "unkwown character in " + literal + " : " + ch,
              "please use characters from c standard"));
        }
        file.get(ch);
        col_number++;
      }
      if (ch == '\"') {
        tokens.emplace_back(
            token::Token(token::TOKEN::CHAR_ARR, literal, line_number));
      } else {
        success = false;
        tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
        error_recovery.emplace_back(
            std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET + " " +
                               "string missing end quotes " + " \"" + literal,
                           "please add end quotes"));
        file.seekg(-1, std::ios::cur);
      }
    } else if (regex.matchWord(ch)) {
      std::string identifier;
      while (regex.matchWord(ch) || regex.matchDigit(ch)) {
        identifier += ch;
        file.get(ch);
      }
      while (ch == ' ' or ch == '\n') {
        if (ch == '\n') {
          line_number++;
          col_number = 1;
        } else {
          col_number++;
        }
        if (!file.get(ch))
          break;
      }
      // cases when we have a struct and need to
      // access its members
      if (identifier == "int") {
        tokens.emplace_back(token::TOKEN::INT, line_number);
      } else if (identifier == "float") {
        tokens.emplace_back(token::TOKEN::FLOAT, line_number);
      } else if (identifier == "double") {
        tokens.emplace_back(token::TOKEN::DOUBLE, line_number);
      } else if (identifier == "void") {
        tokens.emplace_back(token::TOKEN::VOID, line_number);
      } else if (identifier == "return") {
        tokens.emplace_back(token::TOKEN::RETURN, line_number);
      } else if (identifier == "if") {
        tokens.emplace_back(token::TOKEN::IF, line_number);
      } else if (identifier == "else") {
        tokens.emplace_back(token::TOKEN::ELSE, line_number);
      } else if (identifier == "do") {
        tokens.emplace_back(token::TOKEN::DO, line_number);
      } else if (identifier == "while") {
        tokens.emplace_back(token::TOKEN::WHILE, line_number);
      } else if (identifier == "for") {
        tokens.emplace_back(token::TOKEN::FOR, line_number);
      } else if (identifier == "break") {
        tokens.emplace_back(token::TOKEN::BREAK, line_number);
      } else if (identifier == "continue") {
        tokens.emplace_back(token::TOKEN::CONTINUE, line_number);
      } else if (identifier == "static") {
        tokens.emplace_back(token::TOKEN::STATIC, line_number);
      } else if (identifier == "extern") {
        tokens.emplace_back(token::TOKEN::EXTERN, line_number);
      } else if (identifier == "long") {
        tokens.emplace_back(token::TOKEN::LONG, line_number);
      } else if (identifier == "signed") {
        tokens.emplace_back(token::TOKEN::SIGNED, line_number);
      } else if (identifier == "unsigned") {
        tokens.emplace_back(token::TOKEN::UNSIGNED, line_number);
      } else if (identifier == "char") {
        tokens.emplace_back(token::TOKEN::CHAR, line_number);
      } else if (identifier == "sizeof") {
        tokens.emplace_back(token::TOKEN::SIZEOF, line_number);
      } else if (identifier == "struct") {
        tokens.emplace_back(token::TOKEN::STRUCT, line_number);
      } else if (identifier == "goto") {
        tokens.emplace_back(token::TOKEN::GOTO, line_number);
      } else if (identifier == "const") {
        tokens.emplace_back(token::TOKEN::CONST, line_number);
      } else if (identifier == "volatile") {
        tokens.emplace_back(token::TOKEN::VOLATILE, line_number);
      } else if (identifier == "typedef") {
        tokens.emplace_back(token::TOKEN::TYPEDEF, line_number);
      } else {
        tokens.emplace_back(
            token::Token(token::TOKEN::IDENTIFIER, identifier, line_number));
      }
      if (ch == '.') {
        tokens.emplace_back(token::TOKEN::DOT, line_number);
        col_number++;
      } else {
        file.seekg(-1, std::ios::cur);
      }
      col_number += (identifier.length());
    } else if (regex.matchDigit(ch) or ch == '.') {
      std::string constant;
      while (regex.matchDigit(ch)) {
        constant += ch;
        file.get(ch);
      }
      std::string literal_suffix = "";
      // supported suffixes: l, L, u, U, lu, lU, Lu, LU, ul, uL, Ul, UL
      if (ch == 'l' || ch == 'L' || ch == 'u' || ch == 'U') {
        literal_suffix += ch;
        char prev_ch = ch;
        file.get(ch);
        if (ch == 'l' || ch == 'L' || ch == 'u' || ch == 'U') {
          if (std::toupper(prev_ch) != std::toupper(ch)) {
            literal_suffix += ch;
            file.get(ch);
          }
        }
      }
      constant += literal_suffix;
      // This if for a float ie. when there is no proceeding l,L,u,U suffix
      if (ch == '.' and literal_suffix.size() == 0) {
        constant += '.';
        file.get(ch);
        while (regex.matchDigit(ch)) {
          constant += ch;
          file.get(ch);
        }
      }
      if ((ch == 'e' or ch == 'E') and literal_suffix.size() == 0) {
        file.get(ch);
        if (ch == '+' or ch == '-') {
          constant += ch;
          file.get(ch);
        }
        if (regex.matchDigit(ch)) {
          while (regex.matchDigit(ch)) {
            constant += ch;
            file.get(ch);
          }
        } else {
          col_number += (constant.length());
          error_recovery.emplace_back(std::make_pair(
              ERROR_LOCATION + " " + RED + "error:" + RESET + " " + ch +
                  " follows e/E in a number> " + std::string(1, ch),
              "some digit/+/- must follow a number that has e/E"));
          success = false;
          tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
          file.seekg(-1, std::ios::cur);
          continue;
        }
      }

      // If a character follows a number or if we have two dots in a row
      if (regex.matchWord(ch) or ch == '.') {
        col_number += (constant.length());
        if (ch == '.') {
          error_recovery.emplace_back(
              std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET +
                                 " . follows another . in a float number",
                             "a float must have only one ."));
        } else {
          error_recovery.emplace_back(
              std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET +
                                 " " + ch + " follows a digit",
                             "characters cannot follow a number"));
        }
        success = false;
        tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
        file.seekg(-1, std::ios::cur);
        continue;
      } else {
        tokens.emplace_back(
            token::Token(token::TOKEN::CONSTANT, constant, line_number));
      }
      file.seekg(-1, std::ios::cur);
      col_number += (constant.length());
    } else if (ch == '\n' or ch == ' ') {
      if (ch == '\n') {
        line_number++;
        col_number = 1;
      } else {
        col_number++;
      }
    } else {
      error_recovery.emplace_back(
          std::make_pair(ERROR_LOCATION + " " + RED + "error:" + RESET +
                             " invalid token> " + std::string(1, ch),
                         "Please check the code"));
      success = false;
      tokens.emplace_back(token::TOKEN::UNKNOWN, line_number);
    }
  }
}

void lexer::print_symbol_table() {
  const int w = 64;
  std::cout << BOLD << CYAN << std::left << std::string(2 * w, '-')
            << std::endl;
  std::cout << std::left << std::setw(w) << "Lexeme" << std::setw(w) << "Tokens"
            << std::endl;
  std::cout << std::left << std::string(2 * w, '-') << RESET << std::endl;
  for (auto &token_ : lexer::tokens) {
    if (token_.get_value().has_value()) {
      std::cout << RED << std::left << std::setw(w)
                << token_.get_value().value() << GREEN << std::setw(w)
                << token::get_token_type(token_.get_token()) << RESET
                << std::endl;
    } else {
      std::cout << RED << std::left << std::setw(w)
                << token::to_string(token_.get_token()) << GREEN << std::setw(w)
                << token::get_token_type(token_.get_token()) << RESET
                << std::endl;
    }
  }
  std::cout << BOLD << CYAN << std::left << std::string(2 * w, '-') << RESET
            << std::endl;
}

void lexer::print_error_recovery() {
  for (auto &error : error_recovery) {
    std::cout << error.first << std::endl;
    std::cout << GREEN << "info:" << RESET << " " << error.second << std::endl;
  }
}

void lexer::print_tokens() {
  for (auto token : tokens)
    print_token(token.get_token());
  std::cout << std::endl;
}

std::vector<token::Token> lexer::get_tokens() { return tokens; }
} // namespace lexer
} // namespace scarlet
