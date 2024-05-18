#include "s21_smartcalc.h"
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21::calculator::add_token_features(token_t *token) {
  switch (token->token_type) {
  case 0:
    token->token_weight = 1;
    token->member_amount = (member_amount_t)0;
    break;
  case 1:
    token->token_weight = 0;
    token->member_amount = (member_amount_t)0;
    break;
  case 2:
    token->token_weight = 2;
    token->member_amount = (member_amount_t)2;
    break;
  case 3:
    token->token_weight = 2;
    token->member_amount = (member_amount_t)2;
    break;
  case 4:
    token->token_weight = 3;
    token->member_amount = (member_amount_t)2;
    break;
  case 5:
    token->token_weight = 3;
    token->member_amount = (member_amount_t)2;
    break;
  case 6:
    token->token_weight = 4;
    token->member_amount = (member_amount_t)2;
    break;
  case 7:
    token->token_weight = 3;
    token->member_amount = (member_amount_t)2;
    break;
  case 8:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 9:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 10:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 11:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 12:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 13:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 14:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 15:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 16:
    token->token_weight = 5;
    token->member_amount = (member_amount_t)1;
    break;
  case 17:
    token->token_weight = 1;
    token->member_amount = (member_amount_t)0;
    break;
  case 18:
    token->token_weight = -1;
    token->member_amount = (member_amount_t)0;
    break;
  }
}

void s21::calculator::function_names(char func_names[19][6]) {
  snprintf(func_names[0], sizeof(func_names[0]), "%s", empty_);
  snprintf(func_names[1], sizeof(func_names[1]), "%s", left_brase_);
  snprintf(func_names[2], sizeof(func_names[2]), "%s", plus_);
  snprintf(func_names[3], sizeof(func_names[3]), "%s", minus_);
  snprintf(func_names[4], sizeof(func_names[4]), "%s", multip_);
  snprintf(func_names[5], sizeof(func_names[5]), "%s", div_);
  snprintf(func_names[6], sizeof(func_names[6]), "%s", exp_);
  snprintf(func_names[7], sizeof(func_names[7]), "%s", mod_);
  snprintf(func_names[8], sizeof(func_names[8]), "%s", cos_);
  snprintf(func_names[9], sizeof(func_names[9]), "%s", sin_);
  snprintf(func_names[10], sizeof(func_names[10]), "%s", tan_);
  snprintf(func_names[11], sizeof(func_names[11]), "%s", acos_);
  snprintf(func_names[12], sizeof(func_names[12]), "%s", asin_);
  snprintf(func_names[13], sizeof(func_names[13]), "%s", atan_);
  snprintf(func_names[14], sizeof(func_names[14]), "%s", sqrt_);
  snprintf(func_names[15], sizeof(func_names[15]), "%s", ln_);
  snprintf(func_names[16], sizeof(func_names[16]), "%s", log_);
  snprintf(func_names[17], sizeof(func_names[17]), "%s", x_factor_);
  snprintf(func_names[18], sizeof(func_names[18]), "%s", right_brase_);
}

double s21::calculator::calculate_x_factor(char init_str[], double x_factor) {
  double rezult;
  if (strlen(init_str) > 255) {
    rezult = NAN;
  } else if (strlen(init_str) == 0) {
    rezult = 0;
  } else {
    string_t start_string;
    init_string(&start_string, init_str);
    row_t start_row;
    init_row(&start_row);
    if (parce_init_string(&start_string, &start_row)) {
      for (int i = 0; i < start_row.tokens_amount; i++) {
        if (start_row.token_row[i].token_type == 17) {
          start_row.token_row[i].token_type = (token_type_t)0;
          start_row.token_row[i].token_value = x_factor;
          start_row.token_row[i].token_weight = 1;
          start_row.token_row[i].member_amount = (member_amount_t)0;
        }
      }
      remove_unary_minus_and_plus(&start_row);
      add_multip_if_needed(&start_row);
      row_t out_row;
      init_row(&out_row);
      creat_out_row(&out_row, &start_row);
      rezult = calculate_out_row(&out_row);
    } else {
      rezult = NAN;
    }
  }
  return rezult;
}

double s21::calculator::calculate_init_str(char init_str[]) {
  double rezult;
  if (strlen(init_str) > 255) {
    rezult = NAN;
  } else if (strlen(init_str) == 0) {
    rezult = 0;
  } else {
    string_t start_string;
    init_string(&start_string, init_str);
    row_t start_row;
    init_row(&start_row);
    if (parce_init_string(&start_string, &start_row)) {
      remove_unary_minus_and_plus(&start_row);
      add_multip_if_needed(&start_row);
      row_t out_row;
      init_row(&out_row);
      if (creat_out_row(&out_row, &start_row)) {
        rezult = calculate_out_row(&out_row);
      } else {
        rezult = NAN;
      }
    } else {
      rezult = NAN;
    }
  }
  return rezult;
}

int s21::calculator::read_number(string_t *init_string, row_t *init_row) {
  int rezult = 1; //  rezult = 0 - failed to read init_string
  int counter = 0, start = init_string->string_pos,
      lenth = init_string->string_lenth;
  char letters_1[12] = letters_for_number, number[50];
  int dot_flag = 1, exp_possible = 1;
  while (counter < lenth - start) {
    int found_flag = 0;
    for (int i = 0; i < 12; i++) {
      if (init_string->init_string[counter + start] == letters_1[i]) {
        if (letters_1[i] == '.') {
          dot_flag--;
          if (counter > 1)
            exp_possible = 0;
        }
        if (dot_flag < 0) {
          rezult = 0;
          break;
        }
        number[counter] = init_string->init_string[counter + start];
        found_flag = 1;
        break;
      }
    }
    if (found_flag == 1) {
      counter++;
    } else {
      break;
    }
  }
  if (init_string->string_pos + counter + 1 < init_string->string_lenth &&
      exp_possible == 1) {
    rezult = read_expose_for_number(init_string, number, &counter);
  }
  number[counter] = '\0';
  if (rezult == 1) {
    init_string->string_pos += counter;
    token_t found_token;
    found_token.token_value = convert_str_to_double(number, counter);
    found_token.token_type = (token_type_t)0;
    add_token_features(&found_token);
    init_row->token_row[init_row->tokens_amount] = found_token;
    init_row->tokens_amount += 1;
  }
  return rezult;
}

double s21::calculator::convert_str_to_double(char number[], int counter) {
  int before_dot_flag = 1, devider = 10, exp_flag = 0, exp_sign = 1;
  double rezult = (double)(number[0] - 48), prev_exp = 0;
  for (int i = 1; i < counter; i++) {
    if (number[i] == 'E') {
      exp_flag = 1;
      continue;
    }
    if (exp_flag == 0) {
      if (number[i] == '.') {
        before_dot_flag = 0;
        continue;
      }
      if (before_dot_flag == 1) {
        rezult = rezult * 10 + (double)(number[i] - 48);
      } else {
        rezult = rezult + ((double)(number[i] - 48)) / devider;
        devider *= 10;
      }
    } else {
      if (number[i] == '+') {
        continue;
      } else if (number[i] == '-') {
        exp_sign = 0;
      } else {
        if (exp_sign == 1) {
          rezult = rezult * pow(10, prev_exp);
          prev_exp = (double)(number[i] - 48);
          rezult = rezult * pow(10, prev_exp);
        } else {
          rezult = rezult / pow(10, prev_exp);
          prev_exp = (double)(number[i] - 48);
          rezult = rezult / pow(10, prev_exp);
        }
      }
    }
  }
  return rezult;
}

int s21::calculator::read_expose_for_number(string_t *init_string,
                                            char number[], int *counter) {
  int rezult = 1;
  char letter = init_string->init_string[init_string->string_pos + *counter];
  if (letter == 'e' || letter == 'E') {
    number[*counter] = 'E';
    *counter += 1;
    if (init_string->string_pos + *counter < init_string->string_lenth) {
      letter = init_string->init_string[init_string->string_pos + *counter];
      if ((letter >= '0' && letter <= '9') || letter == '+' || letter == '-') {
        number[*counter] = letter;
        *counter += 1;
        for (int i = 0; i < 3; i++) {
          letter = init_string->init_string[init_string->string_pos + *counter];
          if (letter >= '0' && letter <= '9') {
            number[*counter] = letter;
            *counter += 1;
          } else {
            break;
          }
        }
        letter = init_string->init_string[init_string->string_pos + *counter];
        if (letter >= '0' && letter <= '9') {
          rezult = 0;
        }
      }
    }
  }
  return rezult;
}

int s21::calculator::read_operand(string_t *init_string, row_t *init_row) {
  int rezult = 1, token_type = 0, found_func_flag = 1;
  int func_lenth = 0; // rezult = 0 - failed to read init_string
  char func_names[19][6];
  function_names(func_names);
  for (int i = 0; i < 19; i++) {
    int lenth = strlen(func_names[i]);
    found_func_flag = 1;
    if (lenth <= init_string->string_lenth - init_string->string_pos) {
      for (int j = 0; j < lenth; j++) {
        if (init_string->init_string[init_string->string_pos + j] !=
            func_names[i][j]) {
          found_func_flag = 0;
          continue;
        } else {
          token_type = i;
          func_lenth = lenth;
        }
      }
    } else {
      found_func_flag = 0;
    }
    if (found_func_flag == 1)
      break;
  }
  if (found_func_flag == 1) {
    token_t found_token;
    found_token.token_value = 0;
    found_token.token_type = (token_type_t)token_type;
    add_token_features(&found_token);
    init_row->token_row[init_row->tokens_amount] = found_token;
    init_row->tokens_amount += 1;
    init_string->string_pos += func_lenth;
  } else {
    rezult = 0;
  }
  return rezult;
}

double s21::calculator::calculate_out_row(row_t *out_row) {
  double rezult = 0;
  int row_lenth = out_row->tokens_amount, no_rezult_flag = 1;
  token_t temp_token, first_token, second_token, rezult_token;
  row_t temp_row;
  init_row(&temp_row);
  if (row_lenth > 0) {
    for (int i = 0; i < row_lenth; i++) {
      temp_token = out_row->token_row[i];
      if (out_row->token_row[i].member_amount == 0) {
        write_row(&temp_row, &temp_token);
      } else if (out_row->token_row[i].member_amount == 1) {
        if (temp_row.tokens_amount < 1) {
          no_rezult_flag = 0;
          break;
        } else {
          first_token = pop_row(&temp_row);
          rezult_token = one_member_calculate(first_token, temp_token);
          write_row(&temp_row, &rezult_token);
        }
      } else {
        if (temp_row.tokens_amount < 2) {
          no_rezult_flag = 0;
          break;
        } else {
          second_token = pop_row(&temp_row);
          first_token = pop_row(&temp_row);
          rezult_token =
              two_members_calculate(first_token, second_token, temp_token);
          write_row(&temp_row, &rezult_token);
        }
      }
    }
    if (no_rezult_flag == 1) {
      rezult = rezult_token.token_value;
    } else {
      rezult = NAN;
    }
  } else {
    rezult = NAN;
  }
  return rezult;
}

s21::calculator::token_t
s21::calculator::one_member_calculate(token_t first_token, token_t temp_token) {
  token_t rezult;
  int token_type = temp_token.token_type;
  switch (token_type) {
  case COS:
    rezult.token_value = cos(first_token.token_value);
    break;
  case SIN:
    rezult.token_value = sin(first_token.token_value);
    break;
  case TAN:
    rezult.token_value = tan(first_token.token_value);
    break;
  case ACOS:
    rezult.token_value = acos(first_token.token_value);
    break;
  case ASIN:
    rezult.token_value = asin(first_token.token_value);
    break;
  case ATAN:
    rezult.token_value = atan(first_token.token_value);
    break;
  case SQRT:
    rezult.token_value = sqrt(first_token.token_value);
    break;
  case LN:
    rezult.token_value = log(first_token.token_value);
    break;
  case LOG:
    rezult.token_value = log10(first_token.token_value);
    break;
  }
  rezult.token_type = (token_type_t)0;
  rezult.token_weight = 1;
  rezult.member_amount = (member_amount_t)0;
  return rezult;
}

s21::calculator::token_t s21::calculator::two_members_calculate(
    token_t first_token, token_t second_token, token_t temp_token) {
  token_t rezult;
  int token_type = temp_token.token_type;
  switch (token_type) {
  case PLUS:
    rezult.token_value = first_token.token_value + second_token.token_value;
    break;
  case MINUS:
    rezult.token_value = first_token.token_value - second_token.token_value;
    break;
  case MULTIP:
    rezult.token_value = first_token.token_value * second_token.token_value;
    break;
  case DIV:
    rezult.token_value = first_token.token_value / second_token.token_value;
    break;
  case MOD:
    rezult.token_value =
        std::fmod(first_token.token_value, second_token.token_value);
    break;
  case EXP:
    rezult.token_value =
        std::pow(first_token.token_value, second_token.token_value);
    break;
  }
  rezult.token_type = (token_type_t)0;
  rezult.token_weight = 1;
  rezult.member_amount = (member_amount_t)0;
  return rezult;
}

int s21::calculator::creat_out_row(row_t *out_row, row_t *in_row) {
  stack_1t stack;
  init_stack(&stack);
  init_row(out_row);
  in_row->token_pos = 0;
  int rezult = 1;
  while (stack.tokens_amount > 0 || in_row->token_pos < in_row->tokens_amount) {
    token_t temp_stack_token, temp_in_row_token;
    if (in_row->token_pos == in_row->tokens_amount) {
      while (stack.tokens_amount > 0) {
        temp_stack_token = pop_stack(&stack);
        if (temp_stack_token.token_type == 1) {
          rezult = 0;
          break;
        }
        write_row(out_row, &temp_stack_token);
      }
    } else {
      if (stack.tokens_amount > 0) {
        temp_stack_token = read_token_in_stack(&stack);
      } else {
        init_token(&temp_stack_token);
        temp_stack_token.token_weight = -2;
      }
      temp_in_row_token = in_row->token_row[in_row->token_pos];
      if (temp_in_row_token.token_weight == 1) {
        write_row(out_row, &temp_in_row_token);
        in_row->token_pos += 1;
      } else if (temp_in_row_token.token_weight == 0) {
        push_stack(&stack, &temp_in_row_token);
        in_row->token_pos += 1;
      } else if (temp_in_row_token.token_weight > 1) {
        if (temp_in_row_token.token_weight == 5) {
          push_stack(&stack, &temp_in_row_token);
          in_row->token_pos += 1;
        } else if ((temp_stack_token.token_weight == 5 ||
                    temp_stack_token.token_weight == 0) &&
                   temp_in_row_token.token_weight >= 1) {
          push_stack(&stack, &temp_in_row_token);
          in_row->token_pos += 1;
        } else if (temp_in_row_token.token_weight <=
                   temp_stack_token.token_weight) {
          temp_stack_token = pop_stack(&stack);
          write_row(out_row, &temp_stack_token);
          push_stack(&stack, &temp_in_row_token);
          in_row->token_pos += 1;
        } else if (temp_in_row_token.token_weight >
                       temp_stack_token.token_weight &&
                   temp_stack_token.token_weight != -2) {
          push_stack(&stack, &temp_in_row_token);
          in_row->token_pos += 1;
        } else if (temp_stack_token.token_weight == -2) {
          push_stack(&stack, &temp_in_row_token);
          in_row->token_pos += 1;
        } else {
          write_row(out_row, &temp_in_row_token);
          in_row->token_pos += 1;
        }
      } else if (temp_in_row_token.token_weight == -1) {
        while (temp_stack_token.token_weight != 0 &&
               temp_stack_token.token_weight != 5) {
          if (stack.tokens_amount == 0) {
            rezult = 0;
            break;
          }
          temp_stack_token = pop_stack(&stack);
          write_row(out_row, &temp_stack_token);
          temp_stack_token = read_token_in_stack(&stack);
        }
        temp_stack_token = pop_stack(&stack);
        if (temp_stack_token.token_weight == 5) {
          write_row(out_row, &temp_stack_token);
        }
        in_row->token_pos += 1;
      }
    }
    if (rezult == 0)
      break;
  }
  return rezult;
}

void s21::calculator::add_multip_if_needed(row_t *row) {
  row_t new_row;
  init_row(&new_row);
  int new_counter = 0;
  for (int i = 0; i < row->tokens_amount - 1; i++) {
    if (row->token_row[i].token_weight == 1 &&
        row->token_row[i + 1].token_weight == 0) {
      new_row.token_row[new_counter] = row->token_row[i];
      new_counter++;
      new_row.token_row[new_counter].token_weight = 3;
      new_row.token_row[new_counter].token_value = 0;
      new_row.token_row[new_counter].token_type = (token_type_t)4;
      new_row.token_row[new_counter].member_amount = (member_amount_t)2;
      new_counter++;

    } else if (row->token_row[i].token_weight == 1 &&
               row->token_row[i + 1].token_weight == 5) {
      new_row.token_row[new_counter] = row->token_row[i];
      new_counter++;
      new_row.token_row[new_counter].token_weight = 3;
      new_row.token_row[new_counter].token_value = 0;
      new_row.token_row[new_counter].token_type = (token_type_t)4;
      new_row.token_row[new_counter].member_amount = (member_amount_t)2;
      new_counter++;
    } else {
      new_row.token_row[new_counter] = row->token_row[i];
      new_counter++;
    }
  }
  new_row.token_row[new_counter] = row->token_row[row->tokens_amount - 1];
  new_counter++;
  for (int i = 0; i < new_counter; i++) {
    row->token_row[i] = new_row.token_row[i];
  }
  row->tokens_amount = new_counter;
}

void s21::calculator::remove_unary_minus_and_plus(row_t *row) {
  row_t new_row;
  init_row(&new_row);
  int new_counter = 0, counter = 0;
  if (row->tokens_amount > 1) {
    remove_leading_unary_minus_and_plus(row, &new_row, &new_counter, &counter);
  }
  while (counter + 1 < row->tokens_amount) {
    remove_middle_unary_minus_and_plus(row, &new_row, &new_counter, &counter);
  }
  new_row.token_row[new_counter] = row->token_row[counter];
  new_counter++;
  counter++;
  new_row.tokens_amount = new_counter;
  for (int i = 0; i < new_counter; i++) {
    row->token_row[i] = new_row.token_row[i];
  }
  row->tokens_amount = new_counter;
}

void s21::calculator::remove_leading_unary_minus_and_plus(row_t *row,
                                                          row_t *new_row,
                                                          int *new_counter,
                                                          int *counter) {
  int first_token_weight = row->token_row[*counter].token_weight;
  int second_token_weight = row->token_row[*counter + 1].token_weight;
  if (first_token_weight == 2 && second_token_weight == 1) {
    if (row->token_row[*counter].token_type == 3) {
      new_row->token_row[*new_counter].token_value =
          (-1) * row->token_row[*counter + 1].token_value;
    } else {
      new_row->token_row[*new_counter].token_value =
          row->token_row[*counter + 1].token_value;
    }
    new_row->token_row[*new_counter].token_type = (token_type_t)0;
    new_row->token_row[*new_counter].token_weight = 1;
    new_row->token_row[*new_counter].member_amount = (member_amount_t)0;
    *counter += 2;
    *new_counter += 1;
    new_row->tokens_amount = *new_counter;
  } else if (first_token_weight == 2) {
    if (row->token_row[*counter].token_type == 3) {
      new_row->token_row[*new_counter].token_value = -1;
    } else {
      new_row->token_row[*new_counter].token_value = 1;
    }
    new_row->token_row[*new_counter].token_type = (token_type_t)0;
    new_row->token_row[*new_counter].token_weight = 1;
    new_row->token_row[*new_counter].member_amount = (member_amount_t)0;
    *new_counter += 1;
    token_t new_token;
    new_token.token_type = (token_type_t)4;
    add_token_features(&new_token);
    new_row->token_row[*new_counter] = new_token;
    *new_counter += 1;
    *counter += 1;
  }
}

void s21::calculator::remove_middle_unary_minus_and_plus(row_t *row,
                                                         row_t *new_row,
                                                         int *new_counter,
                                                         int *counter) {
  int zero_token_weight = row->token_row[*counter - 1].token_weight;
  int first_token_weight = row->token_row[*counter].token_weight;
  int second_token_weight = row->token_row[*counter + 1].token_weight;
  if (zero_token_weight == 0 || zero_token_weight == 5) {
    if (first_token_weight == 2 &&
        (second_token_weight == 0 || second_token_weight == 5)) {
      if (row->token_row[*counter].token_type == 3) {
        new_row->token_row[*new_counter].token_value = -1;
      } else {
        new_row->token_row[*new_counter].token_value = 1;
      }
      new_row->token_row[*new_counter].token_type = (token_type_t)0;
      new_row->token_row[*new_counter].token_weight = 1;
      new_row->token_row[*new_counter].member_amount = (member_amount_t)0;
      *new_counter += 1;
      token_t new_token;
      new_token.token_type = (token_type_t)4;
      add_token_features(&new_token);
      new_row->token_row[*new_counter] = new_token;
      *new_counter += 1;
      *counter += 1;
    } else if (first_token_weight == 2 && second_token_weight == 1) {
      if (row->token_row[*counter].token_type == 3) {
        new_row->token_row[*new_counter].token_value =
            -1 * row->token_row[*counter + 1].token_value;
      } else {
        new_row->token_row[*new_counter].token_value =
            row->token_row[*counter + 1].token_value;
      }
      new_row->token_row[*new_counter].token_type = (token_type_t)0;
      new_row->token_row[*new_counter].token_weight = 1;
      new_row->token_row[*new_counter].member_amount = (member_amount_t)0;
      *new_counter += 1;
      *counter += 2;
    } else {
      new_row->token_row[*new_counter] = row->token_row[*counter];
      *new_counter += 1;
      *counter += 1;
    }
  } else {
    new_row->token_row[*new_counter] = row->token_row[*counter];
    *new_counter += 1;
    *counter += 1;
  }
  new_row->tokens_amount = *new_counter;
}

void s21::calculator::init_stack(s21::calculator::stack_1t *stack) {
  stack->tokens_amount = 0;
}

s21::calculator::token_t
s21::calculator::pop_stack(s21::calculator::stack_1t *stack) {
  token_t rezult;
  if (stack->tokens_amount > 0) {
    rezult = stack->token_stack[stack->tokens_amount - 1];
    stack->tokens_amount -= 1;
  } else {
    rezult.member_amount = (member_amount_t)-1;
  }
  return rezult;
}

void s21::calculator::push_stack(s21::calculator::stack_1t *stack,
                                 s21::calculator::token_t *token) {
  stack->token_stack[stack->tokens_amount] = *token;
  stack->tokens_amount += 1;
}

s21::calculator::token_t
s21::calculator::read_token_in_stack(s21::calculator::stack_1t *stack) {
  s21::calculator::token_t rezult;
  if (stack->tokens_amount > 0) {
    rezult = stack->token_stack[stack->tokens_amount - 1];
  } else {
    rezult.member_amount = (s21::calculator::member_amount_t)-1;
  }
  return rezult;
}

int s21::calculator::parce_init_string(string_t *init_string, row_t *init_row) {
  int rezult = 1; // rezult = 0 - failed to read init_string
  if (init_string->string_lenth > 0) {
    while (init_string->string_pos < init_string->string_lenth) {
      char letter = init_string->init_string[init_string->string_pos];
      if (letter <= '9' && letter >= '0') {
        rezult = read_number(init_string, init_row);
      } else {
        rezult = read_operand(init_string, init_row);
      }
      if (rezult == 0)
        break;
    }
  } else {
    rezult = 0;
  }
  return rezult;
}

void s21::calculator::init_string(string_t *init_string, char start_string[]) {
  init_string->string_lenth = (int)strlen(start_string);
  init_string->string_pos = 0;
  for (int i = 0; i < init_string->string_lenth; i++) {
    init_string->init_string[i] = start_string[i];
  }
  init_string->init_string[init_string->string_lenth] = '\0';
}

void s21::calculator::init_row(row_t *row) {
  row->tokens_amount = 0;
  row->token_pos = 0;
}

void s21::calculator::write_row(row_t *row, token_t *token) {
  row->token_row[row->tokens_amount] = *token;
  row->tokens_amount += 1;
}

s21::calculator::token_t s21::calculator::pop_row(row_t *row) {
  token_t rezult;
  if (row->tokens_amount > 0) {
    rezult = row->token_row[row->tokens_amount - 1];
    row->tokens_amount -= 1;
  } else {
    rezult.member_amount = (member_amount_t)-1;
  }
  return rezult;
}

void s21::calculator::init_token(token_t *token) {
  token->token_type = (token_type_t)0;
  token->token_value = 0;
  token->token_weight = 0;
}
