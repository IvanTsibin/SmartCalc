#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

namespace s21 {

class calculator {

  typedef enum {
    NUMBER = 0,
    LEFT_BRASE = 1,
    PLUS = 2,
    MINUS = 3,
    MULTIP = 4,
    DIV = 5,
    EXP = 6,
    MOD = 7,
    COS = 8,
    SIN = 9,
    TAN = 10,
    ACOS = 11,
    ASIN = 12,
    ATAN = 13,
    SQRT = 14,
    LN = 15,
    LOG = 16,
    X_FACTOR = 17,
    RIGHT_BRASE = 18
  } token_type_t;

#define empty_ "empty"
#define left_brase_ "("
#define plus_ "+"
#define minus_ "-"
#define multip_ "*"
#define div_ "/"
#define exp_ "^"
#define mod_ "mod"
#define cos_ "cos("
#define sin_ "sin("
#define tan_ "tan("
#define acos_ "acos("
#define asin_ "asin("
#define atan_ "atan("
#define sqrt_ "sqrt("
#define ln_ "ln("
#define log_ "log("
#define x_factor_ "x"
#define right_brase_ ")"

#define letters_end_for_exp_number "1234567890+-eE."
#define letters_start_for_exp_number "1234567890eE."
#define letters_for_number "1234567890."

  typedef enum { ZERO = 0, ONE = 1, TWO = 2 } member_amount_t;

  typedef struct token_struct {
    token_type_t token_type;
    double token_value;
    int token_weight;
    member_amount_t member_amount;
  } token_t;

  typedef struct stack_struct {
    token_t token_stack[255];
    int tokens_amount;
  } stack_1t;

  typedef struct row_struct {
    token_t token_row[255];
    int tokens_amount;
    int token_pos;
  } row_t;

  typedef struct string_struct {
    char init_string[255];
    int string_pos;
    int string_lenth;
  } string_t;

  void add_token_features(token_t *token);
  void function_names(char func_names[18][6]);

  void add_multip_if_needed(row_t *row);

  int read_number(string_t *init_string, row_t *init_row);
  double convert_str_to_double(char number[], int counter);
  int read_expose_for_number(string_t *init_string, char number[],
                             int *counter);
  int read_operand(string_t *init_string, row_t *init_row);

  double calculate_out_row(row_t *out_row);
  token_t one_member_calculate(token_t first_token, token_t temp_token);
  token_t two_members_calculate(token_t first_token, token_t second_token,
                                token_t temp_token);

  int creat_out_row(row_t *out_row, row_t *in_row);

  void remove_unary_minus_and_plus(row_t *row);
  void remove_leading_unary_minus_and_plus(row_t *row, row_t *new_row,
                                           int *new_counter, int *counter);
  void remove_middle_unary_minus_and_plus(row_t *row, row_t *new_row,
                                          int *new_counter, int *counter);

  void init_stack(stack_1t *stack);
  token_t pop_stack(stack_1t *stack);
  void push_stack(stack_1t *stack, token_t *token);
  token_t read_token_in_stack(stack_1t *stack);

  int parce_init_string(string_t *init_string, row_t *init_row);
  void init_string(string_t *init_string, char start_string[]);

  void init_row(row_t *row);
  void write_row(row_t *row, token_t *token);
  token_t pop_row(row_t *row);
  void init_token(token_t *token);

public:
  double calculate_x_factor(char init_str[], double x_factor);
  double calculate_init_str(char init_str[]);
};
} // namespace s21

#endif // SRC_S21_SMARTCALC_H_
