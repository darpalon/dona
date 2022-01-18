#include <iostream>

#include <tao/pegtl.hpp>

namespace pt = tao::pegtl;

namespace dona {
using namespace pt;

struct BREAK : TAO_PEGTL_KEYWORD("break") {};
struct CLASS : TAO_PEGTL_KEYWORD("class") {};
struct CONST : TAO_PEGTL_KEYWORD("const") {};
struct CONTINUE : TAO_PEGTL_KEYWORD("continue") {};
struct DEFER : TAO_PEGTL_KEYWORD("defer") {};
struct ELSE : TAO_PEGTL_KEYWORD("else") {};
struct ENUM : TAO_PEGTL_KEYWORD("enum") {};
struct FALSE : TAO_PEGTL_KEYWORD("false") {};
struct FOR : TAO_PEGTL_KEYWORD("for") {};
struct FUN : TAO_PEGTL_KEYWORD("fun") {};
struct GOTO : TAO_PEGTL_KEYWORD("goto") {};
struct IF : TAO_PEGTL_KEYWORD("if") {};
struct IN : TAO_PEGTL_KEYWORD("in") {};
struct INTERFACE : TAO_PEGTL_KEYWORD("interface") {};
struct MATCH : TAO_PEGTL_KEYWORD("match") {};
struct NUL : TAO_PEGTL_KEYWORD("null") {};
struct RETURN : TAO_PEGTL_KEYWORD("return") {};
struct STATIC : TAO_PEGTL_KEYWORD("static") {};
struct STRUCT : TAO_PEGTL_KEYWORD("struct") {};
struct THIS : TAO_PEGTL_KEYWORD("this") {};
struct TRUE : TAO_PEGTL_KEYWORD("true") {};
struct VAR : TAO_PEGTL_KEYWORD("var") {};
struct WHILE : TAO_PEGTL_KEYWORD("while") {};
struct USE : TAO_PEGTL_KEYWORD("use") {};

struct CHAR_LIT : seq<one<'\''>, any, one<'\''>> {};
struct FLOAT_LIT : seq<plus<digit>, one<'.'>, star<digit>> {};
struct INT_LIT : plus<digit> {};
struct STR_LIT : seq<one<'"'>, star<any>, one<'"'>> {};

struct LineComment : seq<two<'/'>, star<not_at<eolf>, any>> {};
struct MultiLineComment : if_must<string<'/', '*'>, until<string<'*', '/'>>> {};
struct Comment : sor<LineComment, MultiLineComment> {};

struct SkipWithoutNewLine : star<sor<seq<not_at<eol>, space>, Comment>> {};
struct SkipWithNewLine : star<sor<space, Comment>> {};

using _ = SkipWithoutNewLine;
using __ = SkipWithNewLine;

struct Grammar : must<__, eof> {};
} // namespace dona

int main() {
  pt::file_input in{"../code.do"};
  auto ok = pt::parse<dona::Grammar>(in);
  if (ok) {
    std::cout << "OK\n";
  } else {
    std::cout << "FAIL\n";
  }
}
