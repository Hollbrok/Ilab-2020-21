#pragma once

#include "tree.h"

const double exp_value = 2.7182818284;

int FORMULA_COUNTER = 1;

int IF_COUNTER = 0;
int WHILE_COUNTER = 0;

int LOGIC_COUNTER = 0;

bool is_free_objs = false;

//------------------------------------------------------------------------------------------------------------

#define IS_ARITHMETIC_FUNCTION(root)                            \
    (root->get_data_type() == ARITHMETIC_FUNCTION)

#define IS_END_OF_LINE(root)                                    \
    (root->get_data_type() == END_OF_LINE)

#define IS_NUMBER(root)                                         \
    (root->get_data_type() == NUMBER)

#define IS_VARIABLE(root)                                       \
    (root->get_data_type() == VARIABLE)

#define IS_POW(root)                                            \
    ( (root->get_data_type() == OPERATOR) && (root->get_data_value() == OP_POW_VAL) )

#define IS_EQUAL(root)                                          \
    ( (root->get_data_type() == OPERATOR) && (root->get_data_value() == OP_EQUAL_VAL) )

#define IS_MUL(root)                                            \
    ( (root->get_data_type() == OPERATOR) && (root->get_data_value() == OP_TIMES_VAL) )

#define IS_DEL(root)                                            \
    ( (root->get_data_type() == OPERATOR) && (root->get_data_value() == OP_DEL_VAL) )

#define L_AND_R_NULL(root)                                      \
    ( (root->get_left() == nullptr) && (root->get_right() == nullptr) )

#define L_OR_R_NULL(root)                                       \
    ( (root->get_left() == nullptr) || (root->get_right() == nullptr) )

#define Lroot(root)                                             \
    root->get_left()

#define Rroot(root)                                             \
    root->get_right()


//------------------------------------------------------------------------------------------------------------


#define IS_R_B_BRACKET(index)                                          \
    ( (objs_->obj[index].type_of_object == BLOCK_BRACKET) && (objs_->obj[index].value == R_BRACKET_BLOCK_VAL) )

#define IS_L_B_BRACKET(index)                                          \
    ( (objs_->obj[index].type_of_object == BLOCK_BRACKET) && (objs_->obj[index].value == L_BRACKET_BLOCK_VAL) )



//------------------------------------------------------------------------------------------------------------

#define IS_CUR_OBJECT_L_BLOCK_BRACKET                                   \
    ( (objs_->obj[cur_size_].type_of_object == BLOCK_BRACKET) && (objs_->obj[cur_size_].value == L_BRACKET_BLOCK_VAL) )

#define IS_CUR_OBJECT_R_BLOCK_BRACKET                                   \
    ( (objs_->obj[cur_size_].type_of_object == BLOCK_BRACKET) && (objs_->obj[cur_size_].value == R_BRACKET_BLOCK_VAL) )

#define IS_CUR_OBJECT_PLUS_OR_MIN                                       \
    ( (objs_->obj[cur_size_].type_of_object == OPERATOR) && ( (objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL) ) )

#define IS_CUR_OBJECT_LOGIC_OP                                          \
    ( (objs_->obj[cur_size_].type_of_object == LOGICAL_OPERATOR) && ( (objs_->obj[cur_size_].value == OP_IS_EQUAL_VAL) || (objs_->obj[cur_size_].value == OP_BELOW_VAL) || (objs_->obj[cur_size_].value == OP_ABOVE_VAL) ) )

#define IS_CUR_OBJECT_EQUAL_OP                                          \
    ( (objs_->obj[cur_size_].type_of_object == OPERATOR) && (objs_->obj[cur_size_].value == OP_EQUAL_VAL) )

#define IS_CUR_OBJECT_END_OF_LINE                                       \
    ( (objs_->obj[cur_size_].type_of_object == END_OF_LINE) && (objs_->obj[cur_size_].value == END_OF_LINE_VAL) )

#define IS_CUR_OBJECT_LOGIC_FUNC                                        \
    ( (objs_->obj[cur_size_].type_of_object == LOGICAL_FUNCTION) && ( (objs_->obj[cur_size_].value == IF_VAL) || (objs_->obj[cur_size_].value == WHILE_VAL) ) )


//------------------------------------------------------------------------------------------------------------

#define PRINT_UNDEFINE_OP_VALUE                                 \
    printf("Undefined OP value = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define PRINT_UNDEFINE_TYPE                                     \
    printf("Undefined type of object = [%s]. Line: %d\n", get_type_of_object(start_root->get_data()->type_of_object), __LINE__)

#define PRINT_UNDEFINE_FUNC                                     \
    printf("Undefinied func = [%s]. Line: %d\n", get_value_of_object(objs_, start_root->get_data()), __LINE__)

#define PRINT_L_PART_OF_MUL                                                                                                     \
    if ( IS_ARITHMETIC_FUNCTION(Lroot(start_root))  || IS_NUMBER(Lroot(start_root)) || IS_VARIABLE(Lroot(start_root)) ||        \
        IS_POW(Lroot(start_root)) || IS_POW(Lroot(start_root)) || IS_MUL(Lroot(start_root)) || IS_DEL(Lroot(start_root)))       \
    {                                                                                                                           \
        print_subtree(Lroot(start_root), buffer);                                                                               \
        strcat(buffer, " \\cdot ");                                                                                             \
    }                                                                                                                           \
    else                                                                                                                        \
    {                                                                                                                           \
        strcat(buffer, "\\left(");                                                                                              \
        print_subtree(Lroot(start_root), buffer);                                                                               \
        strcat(buffer, "\\right) \\cdot ");                                                                                     \
    }                                                                                           


#define PRINT_R_PART_OF_MUL                                                                                                     \
    if (IS_ARITHMETIC_FUNCTION(Rroot(start_root)) || IS_NUMBER(Rroot(start_root)) || IS_VARIABLE(Rroot(start_root)) ||          \
        IS_POW(Rroot(start_root)) || IS_POW(Rroot(start_root)) || IS_MUL(Rroot(start_root)) || IS_DEL(Rroot(start_root)))       \
    {                                                                                                                           \
        print_subtree(Rroot(start_root), buffer);                                                                               \
    }                                                                                                                           \
    else                                                                                                                        \
    {                                                                                                                           \
        strcat(buffer, "\\left(");                                                                                              \
        print_subtree(Rroot(start_root), buffer);                                                                               \
        strcat(buffer, "\\right)");                                                                                             \
    }


//------------------------------------------------------------------------------------------------------------

#define dR                                                      \
    differenciate(Rroot(start_root))

#define dL                                                      \
    differenciate(Lroot(start_root))

#define copyL                                                   \
    copy_subtree(Lroot(start_root))

#define copyR                                                   \
    copy_subtree(Rroot(start_root))

#define copyF                                                   \
    copy_subtree(start_root)

//------------------------------------------------------------------------------------------------------------

#define ADD_OR_SUB(obj, left, right)                            \
    create_root(obj, left, right)

#define ADDITION(left, right)                                   \
    create_root(CR_ADD, left, right)

#define MULTIPLY(left, right)                                   \
    create_root(CR_MUL, left, right)

#define CR_STATEMENT(left, right)                               \
    create_root(CR_EQUAL, left, right);

#define CR_NUMBER(value)                                        \
    create_root(create_object(NUMBER, value))

//------------------------------------------------------------------------------------------------------------

#define CR_LN                                                   \
    create_object(ARITHMETIC_FUNCTION, LN_VAL)

#define CR_MUL                                                  \
    create_object(OPERATOR, OP_TIMES_VAL)

#define CR_ADD                                                  \
    create_object(OPERATOR, OP_PLUS_VAL)

#define CR_DEL                                                  \
    create_object(OPERATOR, OP_DEL_VAL)

#define CR_EQUAL                                                \
    create_object(OPERATOR, OP_EQUAL_VAL)


//------------------------------------------------------------------------------------------------------------

#define GET_VAL                                                 \
    start_root->get_data_value()

#define GET_TYPE                                                \
    start_root->get_data_type()

//------------------------------------------------------------------------------------------------------------

void tree::create_asm_text_file(bool need_debug)
{
    char* asm_text_buf = make_assem_text();

    FILE* asm_text_file = fopen("user_code[for_user].asm", "wb");
    assert(asm_text_file);

    if(need_debug)
        printf("Asm text buffer:\n"
               "[%s]\n", asm_text_buf);

    fwrite(asm_text_buf, sizeof(char), strlen(asm_text_buf), asm_text_file);

    fclose(asm_text_file);
}

int tree::count_num_of_lines(tree_element* start_root)
{
    int counter = 0;
    if (IS_END_OF_LINE(start_root))
        counter++;
    if (Lroot(start_root))
    {
        counter += count_num_of_lines(Lroot(start_root));
    }
    if (Rroot(start_root))
    {
        counter += count_num_of_lines(Rroot(start_root));
    }

    return counter;
}

void tree::get_asm_text_by_lines(tree_element* start_root, char* buffer)
{
    int start_number_of_lines = objs_->number_of_statements;

    if (objs_->number_of_statements > 2)
    {
        get_asm_text(Rroot(start_root), buffer);
        objs_->number_of_statements--;
        
        strcat(buffer, "\n"); 
        
        get_asm_text_by_lines(Lroot(start_root), buffer);

    }

    else // last string
    {
        get_asm_text(Rroot(start_root), buffer);
        strcat(buffer, "\n");
        get_asm_text(Lroot(start_root), buffer);
    }

    return;
}

char* tree::make_assem_text()
{
    char* buffer = new char[MAX_ASMFILE_SIZE] {0};

    int number_of_statements = 0; //objs_->number_of_statements;
    //printf("statements = %d\n", number_of_statements);

    if (root_->data_->type_of_object == MAIN_FUNCTION)
    {
        objs_->number_of_statements = Rroot(root_)->data_->value;
        number_of_statements = objs_->number_of_statements;
    }
    else
    {
        printf("NO MAIN FUNCTION. Leave..\n");
        strcpy(buffer, "ERROR");
        return buffer;
    }

    //printf("STATEMENTS = %d\n", number_of_statements);

    if (number_of_statements == 0)
        printf("0 lines in text.txt\nLeave..\n");
    else if (number_of_statements == 1)
        get_asm_text(Rroot(root_), buffer);
    else
        get_asm_text_by_lines(Rroot(root_), buffer);

    objs_->number_of_statements = number_of_statements;

    //get_asm_text(root_, buffer);
    
    strcat(buffer, "\n\thlt");

    return buffer;
}

void tree::get_asm_text(tree_element* start_root,char* buffer)
{
    switch (GET_TYPE)
    {
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_EQUAL_VAL:
                {
                    strcat(buffer, "\tpush ");
                    get_asm_text(Rroot(start_root), buffer);
                    strcat(buffer, "\n\tpop ");
                    get_asm_text(Lroot(start_root), buffer);
                    break;
                }
                case OP_PLUS_VAL:
                {
                    //strcat(buffer, "\tpush "); // !
                    get_asm_text(Lroot(start_root), buffer);
                    strcat(buffer, "\n\tpush ");
                    get_asm_text(Rroot(start_root), buffer);
                    strcat(buffer, "\n\tadd\n");
                    break;
                }
                case OP_MIN_VAL:
                {
                    get_asm_text(Lroot(start_root), buffer);
                    strcat(buffer, "\n\tpush ");
                    get_asm_text(Rroot(start_root), buffer);
                    strcat(buffer, "\n\tsub\n");
                    break;
                }
                case OP_TIMES_VAL:
                {
                    get_asm_text(Lroot(start_root), buffer);
                    strcat(buffer, "\n\tpush ");
                    get_asm_text(Rroot(start_root), buffer);
                    strcat(buffer, "\n\tmul\n");
                    break;
                }
            }
            break;
        }
        case VARIABLE:
        {
            //const char* regist_type = get_reg_type(GET_VAL);
            //strcat(buffer, "rax");
            strcat(buffer, get_reg_type(GET_VAL));
            break;
        }
        case NUMBER:
        {
            char* number = new char[20];

            _itoa(GET_VAL, number, 10);
            //strcat(buffer, " ");
            strcat(buffer, number);

            delete[] number;
            return;
            break;
        }
        case ARITHMETIC_FUNCTION:
        {
            switch (GET_VAL)
            {
                case PRINT_VAL:
                    strcat(buffer, "\tpush ");
                    get_asm_text(Lroot(start_root), buffer);
                    strcat(buffer, "\n\tprint");
                    break;
                default:
                    printf("UNKNOWN VALUE OF ARITHMETIC FUNCTION. Line: %d. Value = %d\n", __LINE__, GET_VAL);
            }
            
            //printf("Still need to add case ARITHMETIC_FUNCTION in get_asm_text");
            break;
        }
        case END_OF_LINE: // Вообще в дереве не должно быть ";"
        {
            printf("LOGIC ERROR on line: %d\n", __LINE__);
            break;
        }
        case LOGICAL_FUNCTION:
        {
            switch (GET_VAL)
            {
                case IF_VAL:
                {
                    strcat(buffer, "\tpush 0\n");
                    if (Lroot(start_root)->get_data_type() == LOGICAL_OPERATOR)
                    {

                    }
                    else
                    {
                        strcat(buffer, "\tpush ");
                        get_asm_text(Lroot(start_root), buffer);
                    }

                    strcat(buffer, "\n\tje :END_IF_");

                    char* label_index = new char[20];

                    _itoa(IF_COUNTER, label_index, 10);
                    strcat(buffer, label_index);
                    strcat(buffer, "\n");

                    if (Rroot(start_root)->get_data_type() == BINDER)
                    {
                        get_asm_text_by_lines(Rroot(start_root), buffer);
                    }
                    else
                    {
                        get_asm_text(Rroot(start_root), buffer);
                    }

                    strcat(buffer, "\n\nEND_IF_");
                    strcat(buffer, label_index);
                    strcat(buffer, ":\n");

                        IF_COUNTER++;

                    delete[] label_index;
                    break; 
                }
                case WHILE_VAL:
                {
                    char* label_index = new char[20];


                    strcat(buffer, "\nSTART_WHILE_");
                    _itoa(WHILE_COUNTER, label_index, 10);
                    strcat(buffer, label_index);
                    strcat(buffer, ":\n\n");


                    strcat(buffer, "\tpush 0\n");
                    if (Lroot(start_root)->get_data_type() == LOGICAL_OPERATOR)
                    {
                        printf("\tSTILL NEED TO ADD\n");
                    }
                    else
                    {
                        strcat(buffer, "\tpush ");
                        get_asm_text(Lroot(start_root), buffer);
                    }


                    strcat(buffer, "\n\tje :END_WHILE_");

                    _itoa(WHILE_COUNTER, label_index, 10);
                    strcat(buffer, label_index);
                    strcat(buffer, "\n");

                    if (Rroot(start_root)->get_data_type() == BINDER)
                    {
                        get_asm_text_by_lines(Rroot(start_root), buffer);
                    }
                    else
                    {
                        get_asm_text(Rroot(start_root), buffer);
                    }

                    strcat(buffer, "\n\tjmp :START_WHILE_");
                    strcat(buffer, label_index);
                    strcat(buffer, "\n");
                    
                    strcat(buffer, "\n\nEND_WHILE_");
                    strcat(buffer, label_index);
                    strcat(buffer, ":\n");

                    WHILE_COUNTER++;

                    delete[] label_index;
                    break;
                }
                default:
                    printf("UNDEFINIED VALUE OF LOGICAL FUNCTION. Line: %d\n", __LINE__);
                break;
            }
            break;
        }
        case MAIN_FUNCTION:
        {
            if (Lroot(start_root))
                printf("Language doesn't support argument in main()\n");
            else 
                get_asm_text_by_lines(Rroot(start_root), buffer);

            break;
        }
        default:
            printf("type = %d\n", GET_TYPE);
            PRINT_UNDEFINE_TYPE;
    }
}

const char* get_reg_type(int type)
{
    switch (type)
    {
        case 0:
            return "rax";
        case 1:
            return "rbx";
        case 2:
            return "rcx";
        case 3:
            return "rdx";
        default:
            return "COCK_REGISTR";
    }
}

int hm_elements(tree_element* root)
{
    int hm = 0;

    if (L_AND_R_NULL(root))
    {
        hm += 1;
    }
    else
    {
        if (Lroot(root) != nullptr)
        {
            hm += hm_elements(Lroot(root));
        }
        if (Rroot(root) != nullptr)
        {
            hm += hm_elements(Rroot(root));
        }

        hm += 1;
    }

    return hm;
}

bool tree_element::check_numbers(tree_element* start_root)
{
    if (GET_TYPE == VARIABLE)
        return false;
    if (GET_TYPE == NUMBER)
        return true;
    if (GET_TYPE == ARITHMETIC_FUNCTION)
        return false;//return check_numbers(Lroot(start_root));

    if (Lroot(start_root))
    {
        if (check_numbers(Lroot(start_root)))
        {
            if (Rroot(start_root))
                return check_numbers(Rroot(start_root));
            else
                return false;
        }
        else
            return false;
    }
    else if (Rroot(start_root))
    {
        if (check_numbers(Rroot(start_root)))
        {
            if (Lroot(start_root))
                return check_numbers(Lroot(start_root));
            else 
                return false;
        }
        else
            return false;
    }
    else
        return false;

    
}

int tree::calculate(tree_element* start_root)
{

    int result = get_number(start_root);

    return result;
}

int tree::get_number(tree_element* start_root)
{
    switch (GET_TYPE)
    {
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_PLUS_VAL: 
                    return get_number(Lroot(start_root)) + get_number(Rroot(start_root));
                case OP_MIN_VAL:
                    return get_number(Lroot(start_root)) - get_number(Rroot(start_root));
                case OP_TIMES_VAL:
                    return get_number(Lroot(start_root)) * get_number(Rroot(start_root));
                case OP_DEL_VAL:
                    return get_number(Lroot(start_root)) / get_number(Rroot(start_root));
                case OP_POW_VAL:
                    return static_cast<int>( pow( get_number(Lroot(start_root)), get_number(Rroot(start_root)) ) );
                default:
                    PRINT_UNDEFINE_OP_VALUE;
            }
            break;
        }
        case NUMBER:
            return GET_VAL;
        default:
            PRINT_UNDEFINE_TYPE;
    }

    return -666;
}

void tree::optimizer_number(tree_element* start_root)
{
    switch (GET_TYPE)
    {
        case NUMBER:
            return;
        case VARIABLE:
            return;
        case ARITHMETIC_FUNCTION:
        {
            if (check_numbers(Lroot(start_root)))
            {
                printf("У функции все аргументы -- это числа\n");
                int result = calculate(Lroot(start_root));
                
                delete_subtree(Lroot(start_root));
                start_root->set_left(CR_NUMBER(result));
            }
            else
                optimizer_number(Lroot(start_root));  // Вместо return нужно вызывать optimizer(Lroot(start_root));
            break;
        }
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_MIN_VAL:
                case OP_PLUS_VAL:
                case OP_DEL_VAL:
                case OP_TIMES_VAL:
                case OP_POW_VAL:
                    if (check_numbers((start_root)))
                    {
                        printf("У %s все аргументы -- это числа\n", get_value_of_object(objs_, start_root->get_data()));
                        int result = calculate(start_root);

                        if (start_root->get_prev() != nullptr)
                        {
                            tree_element* prev = start_root->get_prev();

                            if (prev->get_left() == start_root)
                            {
                                delete_subtree(start_root);
                                prev->set_left(CR_NUMBER(result));
                            }
                            else if (prev->get_right() == start_root)
                            {
                                delete_subtree(start_root);
                                prev->set_right(CR_NUMBER(result));
                            }
                            else printf("Error in line: %d\n", __LINE__);

                        }
                        else
                        {
                            delete_subtree(start_root);
                            set_root(CR_NUMBER(result));
                        }

                    }
                    else
                    {
                        optimizer_number(Lroot(start_root));              // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                        optimizer_number(Rroot(start_root));
                    }                                               // и create_root(..) подсоединить к prev start_root, если есть, или сделать root_, если нету;
                    break;
                /*case OP_MIN_VAL:
                    if (check_numbers((start_root)))
                        printf("У - все аргументы -- это числа\n");
                    else
                    {
                        optimizer(Lroot(start_root));              // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                        optimizer(Rroot(start_root));
                    }   // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                                 // и create_root(..) подсоединить к prev start_root, если есть, или сделать root_, если нету;
                    break;
                case OP_TIMES_VAL:
                    if (check_numbers((start_root)))
                        printf("У * все аргументы -- это числа\n");
                    else
                    {
                        optimizer(Lroot(start_root));              // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                        optimizer(Rroot(start_root));
                    }   // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                                 // и create_root(..) подсоединить к prev start_root, если есть, или сделать root_, если нету;
                    break;
                case OP_DEL_VAL:
                    if (check_numbers((start_root)))
                        printf("У / все аргументы -- это числа\n");
                    else
                    {
                        optimizer(Lroot(start_root));              // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                        optimizer(Rroot(start_root));
                    }   // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                                 // и create_root(..) подсоединить к prev start_root, если есть, или сделать root_, если нету;
                    break;
                case OP_POW_VAL:
                    if (check_numbers((start_root)))
                        printf("У ^ все аргументы -- это числа\n");
                    else
                    {
                        optimizer(Lroot(start_root));              // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                        optimizer(Rroot(start_root));
                    }   // Вместо return нужно вызывать calculator от start_root, потом delete_subtree,
                                 // и create_root(..) подсоединить к prev start_root, если есть, или сделать root_, если нету;
                    break;*/
                default:
                    PRINT_UNDEFINE_OP_VALUE;
                    break;
            }
            break;

        }
        default:
            PRINT_UNDEFINE_TYPE;
            break;
    }

    return;
}

void tree::optimizer_operator(tree_element* start_root)
{
    switch (GET_TYPE)
    {
    case NUMBER:
        return;
    case VARIABLE:
        return;
    case ARITHMETIC_FUNCTION:
    {
        /*if (check_numbers(Lroot(start_root)))
        {
            printf("У функции все аргументы -- это числа\n");
            int result = calculate(Lroot(start_root));

            delete_subtree(Lroot(start_root));
            start_root->set_left(CR_NUMBER(result));
        }
        else
            optimizer_number(Lroot(start_root));  // Вместо return нужно вызывать optimizer(Lroot(start_root));
        */
        break;
    }
    case OPERATOR:
    {
        switch (GET_VAL)
        {
            case OP_MIN_VAL:
            case OP_PLUS_VAL:
            {
                if (start_root->get_left()->get_data_type() == NUMBER)
                {
                    if (start_root->get_left()->get_data_value() == 0) // то есть выражние допустим x +- 0 ==>> x 
                    {
                        tree_element* copy_right = copy_subtree(start_root->get_right());

                        if (start_root->get_prev() != nullptr)
                        {
                            tree_element* prev = start_root->get_prev();
                            if (prev->get_left() == start_root)
                            {
                                prev->add_to_left(copy_right);
                                delete_subtree(start_root);
                            }
                            else if (prev->get_right() == start_root)
                            {
                                prev->add_to_right(copy_right);
                                delete_subtree(start_root);
                            }
                            else printf("Error in line: %d\n", __LINE__);
                        }
                        else
                        {
                            set_root(copy_right);//root_ = copy_right;
                            delete_subtree(start_root);
                        }
                    }
                    else
                    {
                        //optimizer_operator(Lroot(start_root));
                        optimizer_operator(Rroot(start_root));
                    }
                }
                else if (start_root->get_right()->get_data_type() == NUMBER)
                {
                    if (start_root->get_right()->get_data_value() == 0) // то есть выражние допустим x +- 0 ==>> x 
                    {
                        tree_element* copy_left = copy_subtree(start_root->get_left());

                        if (start_root->get_prev() != nullptr)
                        {
                            tree_element* prev = start_root->get_prev();
                            if (prev->get_left() == start_root)
                            {
                                prev->add_to_left(copy_left);
                                delete_subtree(start_root);
                            }
                            else if (prev->get_right() == start_root)
                            {
                                prev->add_to_right(copy_left);
                                delete_subtree(start_root);
                            }
                            else printf("Error in line: %d\n", __LINE__);
                        }
                        else
                        {
                            set_root(copy_left);//root_ = copy_left;
                            delete_subtree(start_root);
                        }
                    }
                    else
                    {
                        //optimizer_operator(Lroot(start_root));
                        optimizer_operator(Rroot(start_root));
                    }
                }
                else
                {
                    optimizer_operator(Lroot(start_root));
                    optimizer_operator(Rroot(start_root));
                }

                break;
            }
            case OP_DEL_VAL:
            {
                if (start_root->get_left()->get_data_type() == NUMBER)
                {
                    if (start_root->get_left()->get_data_value() == 0) // то есть выражние допустим 0 / f(x) ==>> 0 
                    {
                        if (start_root->get_prev() != nullptr)
                        {
                            tree_element* prev = start_root->get_prev();
                            if (prev->get_left() == start_root)
                            {
                                prev->add_to_left(CR_NUMBER(0));
                                delete_subtree(start_root);
                            }
                            else if (prev->get_right() == start_root)
                            {
                                prev->add_to_right(CR_NUMBER(0));
                                delete_subtree(start_root);
                            }
                            else printf("Error in line: %d\n", __LINE__);
                        }
                        else
                        {
                            set_root(CR_NUMBER(0));//root_ = CR_NUMBER(0);
                            delete_subtree(start_root);
                        }
                    }
                    else
                    {
                        //optimizer_operator(Lroot(start_root));
                        optimizer_operator(Rroot(start_root));
                    }
                }
                else if (start_root->get_right()->get_data_type() == NUMBER)
                {
                    if (start_root->get_right()->get_data_value() == 1) // то есть выражние допустим f(x) / 1 ==>> f(x)
                    {
                        if (start_root->get_prev() != nullptr)
                        {
                            tree_element* prev = start_root->get_prev();
                            if (prev->get_left() == start_root)
                            {
                                prev->add_to_left(copyL);
                                delete_subtree(start_root);
                            }
                            else if (prev->get_right() == start_root)
                            {
                                prev->add_to_right(copyL);
                                delete_subtree(start_root);
                            }
                            else printf("Error in line: %d\n", __LINE__);
                        }
                        else
                        {
                            set_root(copyL);//root_ = copyL;
                            delete_subtree(start_root);
                        }
                    }
                    else
                    {
                        //optimizer_operator(Lroot(start_root));
                        optimizer_operator(Rroot(start_root));
                    }
                }
                else
                {
                    optimizer_operator(Lroot(start_root));
                    optimizer_operator(Rroot(start_root));
                }

                break;
            }
            case OP_TIMES_VAL:
            {
                if ( (start_root->get_left()->get_data_type() == NUMBER) || (start_root->get_right()->get_data_type() == NUMBER))
                {
                    if (start_root->get_left()->get_data_type() == NUMBER) // 1 * f(x) ==>> f(x)
                    {

                        if (start_root->get_left()->get_data_value() == 1)
                        {
                            if (start_root->get_prev() != nullptr)
                            {
                                tree_element* prev = start_root->get_prev();
                                if (prev->get_left() == start_root)
                                {
                                    prev->add_to_left(copyR);
                                    delete_subtree(start_root);
                                }
                                else if (prev->get_right() == start_root)
                                {
                                    prev->add_to_right(copyR);
                                    delete_subtree(start_root);
                                }
                                else printf("Error in line: %d\n", __LINE__);
                            }
                            else
                            {
                                set_root(copyR);//root_ = copyR;
                                delete_subtree(start_root);
                            }
                        }
                        else if (start_root->get_left()->get_data_value() == 0)
                        {
                            if (start_root->get_prev() != nullptr)
                            {
                                tree_element* prev = start_root->get_prev();

                                if (prev->get_left() == start_root)
                                {
                                    prev->add_to_left(CR_NUMBER(0));
                                    delete_subtree(start_root);
                                }
                                else if (prev->get_right() == start_root)
                                {
                                    prev->add_to_right(CR_NUMBER(0));
                                    delete_subtree(start_root);
                                }
                                else printf("Error in line: %d\n", __LINE__);
                            }
                            else
                            {
                                set_root(CR_NUMBER(0));// root_ = CR_NUMBER(0);
                                delete_subtree(start_root);
                            }
                        }
                        else
                        {
                            //optimizer_operator(Lroot(start_root));
                            optimizer_operator(Rroot(start_root));
                        }
                    }
                    else if (start_root->get_right()->get_data_type() == NUMBER) // f(x) * 1 ==>> f(x)
                    {
                        if (start_root->get_right()->get_data_value() == 1)
                        {
                            if (start_root->get_prev() != nullptr)
                            {
                                tree_element* prev = start_root->get_prev();
                                if (prev->get_left() == start_root)
                                {
                                    prev->add_to_left(copyL);
                                    delete_subtree(start_root);
                                }
                                else if (prev->get_right() == start_root)
                                {
                                    prev->add_to_right(copyL);
                                    delete_subtree(start_root);
                                }
                                else printf("Error in line: %d\n", __LINE__);
                            }
                            else
                            {
                                set_root(copyL);//root_ = copyL;
                                delete_subtree(start_root);
                            }
                        }
                        else if (start_root->get_right()->get_data_value() == 0)
                        {
                            if (start_root->get_prev() != nullptr)
                            {
                                tree_element* prev = start_root->get_prev();
                                if (prev->get_left() == start_root)
                                {
                                    prev->add_to_left(CR_NUMBER(0));
                                    delete_subtree(start_root);
                                }
                                else if (prev->get_right() == start_root)
                                {
                                    prev->add_to_right(CR_NUMBER(0));
                                    delete_subtree(start_root);
                                }
                                else printf("Error in line: %d\n", __LINE__);
                            }
                            else
                            {
                                set_root(CR_NUMBER(0));// root_ = CR_NUMBER(0);
                                delete_subtree(start_root);
                            }
                        }
                        else
                        {
                            optimizer_operator(Lroot(start_root));
                            //optimizer_operator(Rroot(start_root));
                        }
                    }
                }
                else
                {
                    optimizer_operator(Lroot(start_root));
                    optimizer_operator(Rroot(start_root));
                }

                break;
            }
            case OP_POW_VAL:
                /*if (check_numbers((start_root)))
                {
                    printf("У %s все аргументы -- это числа\n", get_value_of_object(objs_, start_root->get_data()));
                    int result = calculate(start_root);

                    if (start_root->get_prev() != nullptr)
                    {
                        tree_element* prev = start_root->get_prev();

                        if (prev->get_left() == start_root)
                        {
                            delete_subtree(start_root);
                            prev->set_left(CR_NUMBER(result));
                        }
                        else if (prev->get_right() == start_root)
                        {
                            delete_subtree(start_root);
                            prev->set_right(CR_NUMBER(result));
                        }
                        else printf("Error in line: %d\n", __LINE__);

                    }
                    else
                    {
                        delete_subtree(start_root);
                        root_ = CR_NUMBER(result);
                    }

                }
                else
                {
                    optimizer_number(Lroot(start_root));  
                    optimizer_number(Rroot(start_root));
                }    */                                           
                break;
            default:
                PRINT_UNDEFINE_OP_VALUE;
                break;
        }
        break;

    }
    default:
        PRINT_UNDEFINE_TYPE;
        break;
    }

    return;
}

void tree_element::delete_subtree(tree_element* start_root)
{
    if (Lroot(start_root))
        delete_subtree(Lroot(start_root));

    if (Rroot(start_root))
        delete_subtree(Rroot(start_root));

    delete start_root;
    start_root = nullptr;

    return;
}

char* tree::get_formula(tree_element* start_root)
{
    char* buffer = new char[MAX_FORMULA_SIZE] {0};

    strcat(buffer, "\\begin{equation}\n");
    print_subtree(start_root, buffer);

    strcat(buffer, "\n\\end{equation} \n");

    return buffer;
}

void tree::print_subtree(tree_element* start_root, char* buffer)
{
    switch (GET_TYPE)
    {
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_TIMES_VAL:
                {
                    PRINT_L_PART_OF_MUL;
                    PRINT_R_PART_OF_MUL;

                    break;
                }
                case OP_DEL_VAL:
                {
                    strcat(buffer, "\\frac{");
                    print_subtree(Lroot(start_root), buffer);
                    strcat(buffer, "}{");
                    print_subtree(Rroot(start_root), buffer);
                    strcat(buffer, "} ");
                    break;
                }
                case OP_POW_VAL:
                {
                    if(IS_NUMBER(Lroot(start_root)))
                        print_subtree(Lroot(start_root), buffer);
                    else
                    {
                        strcat(buffer, "\\left(");
                        print_subtree(Lroot(start_root), buffer);
                        strcat(buffer, "\\right)");
                    }

                    strcat(buffer, "^{");
                    print_subtree(Rroot(start_root), buffer);
                    strcat(buffer, "} ");
                    break;
                }
                case OP_MIN_VAL:
                case OP_PLUS_VAL:
                {
                    print_subtree(Lroot(start_root), buffer);
                    strcat(buffer, get_value_of_object(objs_, start_root->get_data()));
                    print_subtree(Rroot(start_root), buffer);
                    break;
                }
                default:
                    break;
            }
            return;
            break;
        }
        case NUMBER:
        {
            char* number = new char[20];
         
            _itoa(start_root->get_data_value(), number, 10);
            strcat(buffer, number);
            
            delete[] number;
            return;
            break;
        }
        case VARIABLE:
        {
            strcat(buffer, get_value_of_object(objs_, start_root->get_data()));
            return;
            break;
        }
        case ARITHMETIC_FUNCTION:
        {
            strcat(buffer, "\\");
            strcat(buffer, get_value_of_object(objs_, start_root->get_data()));

            //if (IS_NUMBER(Lroot(start_root)) || IS_VARIABLE(Lroot(start_root)))
              //  print_subtree(Lroot(start_root), buffer);
            if(true)//else
            {
                strcat(buffer, "(");
                print_subtree(Lroot(start_root), buffer);
                strcat(buffer, ") ");
 
            }
            break;
        }
        default:
            PRINT_UNDEFINE_TYPE;
            return;
    }
    return;
}

Object* create_object(int type, int value)
{
    struct Object* obj = new Object;

    obj->type_of_object = type;
    obj->value = value;

    return obj;
}

tree_element* create_root(struct Object* obj, tree_element* left, tree_element* right, tree_element* prev)
{
    tree_element* root = new tree_element;
    
    root->set_left(left);

    if(left)
        left->set_prev(root);

    root->set_right(right);
    
    if(right)
        right->set_prev(root);

    root->set_data(obj);

    root->set_prev(prev);

    return root;
}

tree_element* tree::differenciate(tree_element* start_root)
{
    switch (GET_TYPE)
    {
        case OPERATOR:
        {
            switch (GET_VAL)
            {
                case OP_MIN_VAL:
                case OP_PLUS_VAL:
                {
                    fprintf(tex_, "Как в детстве нас учили ходить, так и сейчас мы возьмем следующую производную:\n");
                    fprintf(tex_, get_formula(start_root));

                    fprintf(tex_, "Даже Рома Глаз знает, что производная от суммы или разности равна соответственно сумме/разности"
                                  " производных ее частей\\\\");

                    fprintf(tex_, "Поэтому посчитаем производную слева: \n");
                    fprintf(tex_, get_formula(Lroot(start_root)));

                    tree_element* left_dif = dL;
                    fprintf(tex_, "Её производная с точностью до распределение Ферми-Дирака получается равной:\n");
                    fprintf(tex_, get_formula(left_dif));

                    fprintf(tex_, "А после, если останутся силы, производную правой части, которая равна: \n");
                    fprintf(tex_, get_formula(Rroot(start_root)));

                    tree_element* right_dif = dR;
                    fprintf(tex_, "На лекции по русской литературу я узнал об законе больших чисел Бернулли-Горяйнова,"
                                  " из которого следует следующее выражение для производной:\n");
                    fprintf(tex_, get_formula(right_dif));

                    return ADD_OR_SUB(create_object(OPERATOR, GET_VAL), left_dif, right_dif);
                }
                case OP_TIMES_VAL:
                {
                    fprintf(tex_, "Чтобы попа не потела, не кусали комары, полторашка научит вас брать диффуры."
                                  " Шучу! Мы возьмем следующую производную:\n");
                    fprintf(tex_, get_formula(start_root));

                    fprintf(tex_, "На научной конференции 982 года по квантовой термодинамике Пушкин доказал, что мы живем в "
                                  "3.14-мерном пространстве и оно кошка-симметрично,"
                                  " отсюда как раз-таки следует, что производная от произведения это:\n\n"
                                  "  \\begin{equation}\n" 
                                  "  f(x) \\cdot g(x) = f^{'}(x) \\cdot g(x) + f(x) \\cdot g^{'}(x)\n"
                                  " \\end{equation} \\\\");

                    fprintf(tex_, "Поэтому по методу Центрирования галактик рассчитаем производную f(x), которое равна: \n");
                    fprintf(tex_, get_formula(Lroot(start_root)));

                    tree_element* left_dif = dL;
                    fprintf(tex_, " P.S. тут полторашка словила шизу и начала бегать по комнате, поэтому за правильность "
                                  "результата она не ручается."
                                  " С погрешностью в 0.1 почку вискаса получаем:\n");
                    fprintf(tex_, get_formula(left_dif));

                    fprintf(tex_, "Ну так как Mrs.Patrikovna сейчас бегает за своим хвостом, то следующую производную: \n");
                    fprintf(tex_, get_formula(Rroot(start_root)));

                    tree_element* right_dif = dR;
                    fprintf(tex_, "Остальную часть я попробую взять сам, в этом мне поможет баночка охоты крепкого. *Буль-Буль*, получаем что-то такое:\n");
                    fprintf(tex_, get_formula(right_dif));

                    return ADDITION(MULTIPLY(left_dif, copyR), MULTIPLY(right_dif, copyL));
                }
                case OP_POW_VAL:
                {
                    fprintf(tex_, "Чтобы получить ответ необходимо сделать сложный мув, а именно взять эту производную:\n");
                    fprintf(tex_, get_formula(start_root));

                    fprintf(tex_, "Степень-степень-степень, что же делать с этим? Для этого заглянем в АнтиДемидовича, том 1, страница 112, примеры 1-2\n");
                    fprintf(tex_, "\nНо чтобы не париться с различными случаями можно ее взять в обшем случае:\n\n"
                        "  \\begin{equation}\n"
                        "  f(x)^{g(x)} = e^{g(x)\\cdot ln(f(x))}  = f(x)^{g(x)} \\cdot \\left(g(x)\\cdot ln(f(x)) \\right)^{'} =  \n"
                        " \\end{equation} \\\\");
                    
                    fprintf(tex_, "Значит нужно рассчитать следующую производную:\n\n");

                    tree_element* deriv_part = create_root(CR_MUL, copyR, create_root(CR_LN, copyL));
                    fprintf(tex_, get_formula(deriv_part));

                    tree_element* derivative = differenciate(deriv_part);
                    fprintf(tex_, "В итоге получаем следующим результат:\n");
                    fprintf(tex_, get_formula(derivative));
                    
                    return MULTIPLY(derivative, copyF);
                }
                default:
                    PRINT_UNDEFINE_OP_VALUE;
            }
            break;
        }
        case NUMBER:
            fprintf(tex_, "Ссылаясь на 2 том Кудрявцева, производная от константы = $e^{i\\pi} + 1 = 0$.\n\n");
            return CR_NUMBER(0);

        case VARIABLE:
            fprintf(tex_, "В свою же очередь производная от переменной = $- \\cos(\\pi) + \\sin(0) = 1$.\n\n");
            return CR_NUMBER(1);
        case ARITHMETIC_FUNCTION:
        {
            switch (GET_VAL)
            {
                case LN_VAL:
                    fprintf(tex_, "Опираясь на Кудрявцева, том 1, страница 112, пример 11 можно получить производную логарифма.\n\n");
                    return create_root(CR_DEL, differenciate( copy_subtree(start_root->get_left()) ), copy_subtree(start_root->get_left()));

                default:
                    PRINT_UNDEFINE_FUNC;
            }
        }
        default:
            PRINT_UNDEFINE_TYPE;
    }
    
    printf("Something bad in diff\n");
    return nullptr;
}

tree_element* tree_element::copy_subtree(tree_element* start_element)
{
    tree_element* new_start = new tree_element;

    struct Object* obj = new Object;
    obj->type_of_object = start_element->get_data()->type_of_object;
    obj->value = start_element->get_data()->value;

    new_start->set_data(obj);

    if ((start_element->get_left() == nullptr) && (start_element->get_right() == nullptr))
    {
        return new_start;
    }
    if (start_element->get_left() != nullptr)
    {
        tree_element* left_subtree = copy_subtree(start_element->get_left());
        new_start->set_left(left_subtree);
        left_subtree->set_prev(new_start);
    }
    if (start_element->get_right() != nullptr)
    {
        tree_element* right_subtree = copy_subtree(start_element->get_right());
        new_start->set_right(right_subtree);
        right_subtree->set_prev(new_start);
    }

    return new_start;
}

tree_element* tree_element::add_to_left(tree_element* new_element)
{
    assert(this && "You passed nullptr tree");
    assert(new_element && "Can't calloc memory for tree_element");

    new_element->set_prev(this);

    this->set_left(new_element);

    return new_element;
}

tree_element* tree_element::add_to_right(tree_element* new_element)
{
    assert(this && "You passed nullptr tree");
    assert(new_element && "Can't calloc memory for tree_element");

    new_element->set_prev(this);

    this->set_right(new_element);

    return new_element;
}

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
    data_(data),
    prev_(prev),
    left_(left),
    right_(right)
{
}

tree_element::~tree_element()
{
    assert(this && "You passed nullptr to ~tree_element");
    data_ = POISON;

    prev_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    
}

tree::tree(const char* name) :
    cur_size_(0),
    error_state_(0),
    name_(name),
    root_(nullptr)
{
    is_free_objs = true;
    assert(this && "You passed nullptr to constructor");
    assert(name && "You need to pass name");
}

tree::~tree()
{
    assert(this && "nullptr in desctructor");
    //printf("%s\n", __FUNCSIG__);
    // assert(root_);

    if (root_)
         root_->free_all();
    else
        printf("No free\n");

    if (false)
    {
        delete this;
    }
    if (!is_free_objs)
    {
        Objs_destructor(objs_);
        is_free_objs = true;
    }
   
    cur_size_ = -1;
    error_state_ = -1;
    name_ = nullptr;
    root_ = nullptr;
}

void tree_element::free_all()
{
    assert(this);
    if (get_left())
        left_->free_all();
    if (get_right())
        right_->free_all();

    if (data_)
    {
        //printf("delete\n");
        //delete data_;
        //data_ = nullptr;
    }
    if (this)
        delete this;
    else
        printf("root is nullptr");

    return;
}

tree_element* tree::add_to_left(tree_element* x, data_type number)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && tmp)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;

        x->set_left(tmp);
    }
    else
        printf("You must pass x\n");

    return tmp;
}

tree_element* tree::add_to_right(tree_element* x, data_type number)
{
    assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
    assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;
    }
    else if (cur_size_)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        x->set_right(tmp);

        cur_size_++;
    }
    else
        printf("You must pass x\n");

    return tmp;
}

tree_element* tree::add_to_left(tree_element* x, tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    //tree_element* tmp = new tree_element;
    //assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = new_element;

        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //new_element->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && new_element)
    {
        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //tmp->set_data(number);

        cur_size_++;

        x->set_left(new_element);
    }
    else
        printf("You must pass x\n");

    return new_element;
}

tree_element* tree::add_to_right(tree_element* x, tree_element* new_element)
{
    assert(this && "You passed nullptr tree");

    //tree_element* tmp = new tree_element;
    //assert(tmp && "Can't calloc memory for tree_element");

    if ((x == nullptr) && (cur_size_ == 0))
    {
        root_ = new_element;

        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //new_element->set_data(number);

        cur_size_++;
    }
    else if (cur_size_ && new_element)
    {
        new_element->set_prev(x);
        new_element->set_right(nullptr);
        new_element->set_left(nullptr);
        //tmp->set_data(number);

        cur_size_++;

        x->set_right(new_element);
    }
    else
        printf("You must pass x\n");

    return new_element;
}

void tree::print_tree(bool need_graphviz_dump) const
{
    if (need_graphviz_dump)
    {
        graphviz_dump("dump_for_me.dot");

        system("iconv.exe -t UTF-8 -f  CP1251 < dump_for_me.dot > dump_temp.dot");
       
        system("dot dump_temp.dot -Tpdf -o dump_for_me.pdf");
       
        system("del dump_for_me.dot");
      
        system("ren dump_temp.dot dump_for_me.dot");
 
        system("dump_for_me.pdf");

    }

    return;
}

void tree::graphviz_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=record, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n\n");

    //tree_element* tmp = root_;

    print_all_elements(root_, dump, objs_);
    fprintf(dump, "}\n");

    fclose(dump);

    //graphviz_dump("dump.dot");
    //printf("1");

    return;
}

void tree::show_tree(const char* name_of_file) const
{
    char* dot_name = new char[50]{ 0 };
    strcat(dot_name, name_of_file);
    strcat(dot_name, ".dot");

    char* pdf_name = new char[50]{ 0 };
    strcat(pdf_name, name_of_file);
    strcat(pdf_name, ".pdf");

    graphviz_beauty_dump(dot_name);

    char* sys1 = new char[100]{ 0 };
    strcat(sys1, "iconv.exe -t UTF-8 -f  CP1251 < ");
    strcat(sys1, dot_name);
    strcat(sys1, " > TEMP_176831.dot");

    system(sys1);


    char* sys2 = new char[100]{ 0 };
    strcat(sys2, "dot TEMP_176831.dot  -Tpdf -o ");
    strcat(sys2, pdf_name);
    system(sys2);
    


    char* sys3 = new char[100]{ 0 };
    strcat(sys3, "del ");
    strcat(sys3, dot_name);
    system(sys3);




    char* sys4 = new char[100]{ 0 };
    strcat(sys4, "ren TEMP_176831.dot ");
    strcat(sys4, dot_name);
    system(sys4);
    
    char* sys5 = new char[50]{0};
    strcat(sys5, pdf_name);
    system(sys5);


    delete[] dot_name;
    delete[] pdf_name;
    delete[] sys1;
    delete[] sys2;
    delete[] sys3;
    delete[] sys4;
    delete[] sys5;

}

void tree::graphviz_beauty_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=ellipse, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

    tree_element* root = root_;

    print_all_elements_beauty(root, dump, objs_);
    fprintf(dump, "}\n");

    fclose(dump);
    return;
}

char* make_buffer(const char* name_file)
{
    FILE* database = fopen("database.txt", "rb");
    assert(database && "Can't open database.txt");

    long file_length = size_of_file(database);

    char* buffer = new char[file_length + 1];
    assert(buffer && "Can't calloc memory for buffer");

    fread(buffer, sizeof(char), file_length, database);
    return buffer;
}

void tree_element::print_elem(FILE* database)
{
    assert(database);
    assert(this);

    fprintf(database, "[\n");

    if (get_left() != nullptr)
    {
        //fprintf(database, "?%.*s?\n", length_, data_);
        get_left()->print_elem(database);
    }

    if (get_right() != nullptr)
        get_right()->print_elem(database);

    if ((get_right() == nullptr) && (get_left() == nullptr))
        //fprintf(database, "`%.*s`\n", length_, data_);

    fprintf(database, "]\n");

    return;
}

void print_all_elements(tree_element* tmp, FILE* dump, struct Objects* objs)
{
    assert(tmp && "tmp is nullptr in print_all_elements");
    
    if (tmp->get_left())
    {
        print_all_elements(tmp->get_left(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n\n", tmp, tmp->get_left());
    }
    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n\n", tmp, tmp->get_right());
    }

    //printf("MAIN TYPE is %d\n", tmp->get_data()->type_of_object);

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
    {
        if (tmp->get_prev() != nullptr)
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{ {<f0> TYPE = [%s] | <here> VALUE = [%s]} | PREV [%p] }\" , style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_prev());
            else
                fprintf(dump, "\"%p\" [label = \"{ {<f0> TYPE = [%s] | <here> VALUE = [%d]} | PREV [%p] }\" , style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_prev());
        }
        else
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
        }
    }
    else
    {
        if (tmp->get_prev() == nullptr)
        {
            if (tmp->get_data()->type_of_object == NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p] | [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
            else if (tmp->get_data()->type_of_object == BINDER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p] | [%p]}\",style = filled, fillcolor = \"#1F85DE\"] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| right}| {<f2> [%p] | [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_right());
        }
        else
        {
            //printf("HERE type is %d\n", tmp->get_data()->type_of_object);

            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right} | {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightblue] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else if (tmp->get_data()->type_of_object == NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right} | {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else if (tmp->get_data()->type_of_object == LOGICAL_FUNCTION)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right} | {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = \"#fd02f4\"] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else if (tmp->get_data()->type_of_object == BINDER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right}| {<f2>  [%p]| [%p]| [%p]}\",style = filled, fillcolor = \"#1F85DE\"] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right} | {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
        }
    }

    return;
}

void print_all_elements_beauty(tree_element* tmp, FILE* dump, struct Objects* objs)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_left())
    {
        print_all_elements_beauty(tmp->get_left(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n", tmp, tmp->get_left());
    }
    if (tmp->get_right())
    {
        print_all_elements_beauty(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp, tmp->get_right());
    }

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
    {
            if (tmp ->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = lightgreen] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->get_data()->value);
    }
    else
    {
        if (tmp->get_prev() == nullptr)
        {
            if ((tmp->get_data()->type_of_object != NUMBER) && (tmp->get_data()->type_of_object != BINDER))
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = red] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
            {
                if (tmp->get_data()->type_of_object == BINDER)
                    fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = \"#1F85DE\"] \n", tmp, tmp->get_data()->value);
                else
                    fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = red] \n", tmp, tmp->get_data()->value);
            }
        }
        else
        {
            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = lightblue] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else if ((tmp->get_data()->type_of_object != NUMBER) && (tmp->get_data()->type_of_object != BINDER))
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = purple] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
            {
                if (tmp->get_data()->type_of_object == BINDER)
                    fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = \"#1F85DE\"] \n", tmp, tmp->get_data()->value);
                else
                    fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = purple] \n", tmp, tmp->get_data()->value);
            }
        }
    }

    return;
}

tree_element* tree::fill_by_lines(tree_element* start_root)
{
    int start_number_of_lines = objs_->number_of_statements;

    if (objs_->number_of_statements > 2)
    {
        tree_element* right_subtree = get_statement();
        objs_->number_of_statements--;

        tree_element* left_subtree = nullptr;
        left_subtree = fill_by_lines(left_subtree);

        start_root = create_root(create_object(BINDER, start_number_of_lines), left_subtree, right_subtree);
    }
    else
    {
        tree_element* right_subtree = get_statement();
        tree_element* left_subtree = get_statement();
        start_root = create_root(create_object(BINDER, objs_->number_of_statements), left_subtree, right_subtree);
    }

    return start_root;
}

tree_element* tree::fill_by_lines(tree_element* start_root, int& number_of_lines)
{
    int start_number_of_lines = number_of_lines;

    if (number_of_lines > 2)
    {
        tree_element* right_subtree = get_statement();
        number_of_lines--;

        tree_element* left_subtree = nullptr;
        left_subtree = fill_by_lines(left_subtree, number_of_lines);

        start_root = create_root(create_object(BINDER, start_number_of_lines), left_subtree, right_subtree);
    }
    else
    {
        tree_element* right_subtree = get_statement();
        tree_element* left_subtree = get_statement();
        start_root = create_root(create_object(BINDER, number_of_lines), left_subtree, right_subtree);
    }

    //printf("start_root = %p\n", start_root);

    return start_root;
}

int tree::count_statements()
{
    int num_of_statements = 0;

    for (size_t i = 0; i < objs_->number_of_objects; i++)
    {
        if (objs_->obj[i].type_of_object == BLOCK_BRACKET)
        {
            int counter_of_block_brackets = 1;
            i++;

            while (counter_of_block_brackets != 0)
            {
                if (IS_R_B_BRACKET(i))
                    counter_of_block_brackets--;
                else if (IS_L_B_BRACKET(i))
                    counter_of_block_brackets++;

                i++;
            }

            num_of_statements++;
        }
        else
        {
            if (objs_->obj[i].type_of_object == END_OF_LINE)
                num_of_statements++;
        }
    }
    
    return num_of_statements;
}

void tree::fill_tree(struct Objects* main_object, bool need_print, bool beauty_print)
{
    assert(this && "Nullptr in tree");
    assert(main_object && "nullptr Objects struct");

    objs_ = main_object;
   
    int number_of_statements = count_statements();
    objs_->number_of_statements = number_of_statements;
    
    if (number_of_statements == 0)
        printf("0 lines in text.txt\nLeave..\n");
    else if (number_of_statements == 1)
        root_ = get_statement();      
    else
        root_ = fill_by_lines(root_);
        
    objs_->number_of_statements = number_of_statements;

    if (need_print)
    {
        if (beauty_print)
            show_tree();
        else
            print_tree();
    }

    is_free_objs = false;
    return;
}

const char* get_type_of_object(TYPE type)
{
    switch (type)
    {
        case OPERATOR:
            return "Operator";
        case NUMBER:
            return "Number";
        case BRACKET:
            return "Bracket";
        case VARIABLE:
            return "Variable";
        case ARITHMETIC_FUNCTION:
            return "ARITHMETIC Function";
        case END_OF_LINE:
            return "END-LINE symbol";
        case BINDER:
            return "BINDER";
        case LOGICAL_OPERATOR:
            return "LOGIC OP";
        case LOGICAL_FUNCTION:
            return "LOGIC function";
        case MAIN_FUNCTION:
            return "MAIN function";
        default:
            return "UNINDENTIFIED TYPE";
    }
}

const char* get_value_of_object(struct Objects* objs, struct Object* obj) 
{
    if (obj->type_of_object == VARIABLE)
    {
        return objs->variables_names[obj->value];
    }
    else if (obj->type_of_object == BINDER)
    {
        switch (obj->value)
        {
            case 1:
                return "1";
            case 2:
                return "2";
            case 3:
                return "3";
            case 4:
                return "4";
            case 5:
                return "5";
            case 6:
                return "6";
            case 7:
                return "7";
            case 8:
                return "8";

        }
    }
    else
    {
        switch (obj->value)
        {
            case L_BRACKET_VAL:
                return "(";
            case R_BRACKET_VAL:
                return ")";
            case L_BRACKET_BLOCK_VAL:
                return "{";
            case R_BRACKET_BLOCK_VAL:
                return "}";
            case OP_PLUS_VAL:
                return "+";
            case OP_MIN_VAL:
                return "-";
            case OP_TIMES_VAL:
                return "*";
            case OP_DEL_VAL:
                return "/";
            case OP_POW_VAL:
                return "^";
            case OP_EQUAL_VAL:
                return "=";
            case OP_BELOW_VAL:
                return "<";
            case OP_ABOVE_VAL:
                return ">";
            case OP_IS_EQUAL_VAL:
                return "==";
            case SIN_VAL:
                return "sin";
            case COS_VAL:
                return "cos";
            case LN_VAL:
                return "ln";
            case EXP_VAL:
                return "exp";
            case END_OF_LINE_VAL:
                return ";";
            case IF_VAL:
                return "if";
            case WHILE_VAL:
                return "while";
            case PRINT_VAL:
                return "print";
            case MAIN_VAL:
                return "main";
            case FOR_VAL:
                return "for";
            default:
                return "UNINDENTIFIED TYPE";
        }
    }

    return "UNINDENTIFIED TYPE ERROR";
}

tree_element* tree::get_block()
{
    tree_element* result = nullptr;

    if (objs_->obj[cur_size_].type_of_object != BLOCK_BRACKET)
    {
        return get_statement();
    }
    else if (!IS_L_B_BRACKET(cur_size_))
    {
        printf("ERROR IN BRACKET. Leave..\n");
        return nullptr;
    }
    else
    {
        cur_size_++;  // from '{' to next element

        int true_lines = 0;
        int tmp_cur_size = cur_size_;

        int bracket_counter = 1;

        while (bracket_counter != 0)
        {
            if (IS_R_B_BRACKET(tmp_cur_size))
            {
                bracket_counter--;
            }
            else if (IS_L_B_BRACKET(tmp_cur_size))
            {
                while (!(IS_R_B_BRACKET(tmp_cur_size)))
                    tmp_cur_size++;

                true_lines++;
            }


            if ((objs_->obj[tmp_cur_size].type_of_object == END_OF_LINE) && (objs_->obj[tmp_cur_size].value == END_OF_LINE_VAL))
            {
                true_lines++;
            }
            tmp_cur_size++;

        }

        int start_number_of_lines = true_lines;

        if (true_lines > 1)
        {
            int number_of_lines = true_lines;

            if (number_of_lines > 2)
            {
                tree_element* right_subtree = get_statement();
                number_of_lines--;

                tree_element* left_subtree = nullptr;
                left_subtree = fill_by_lines(left_subtree, number_of_lines);

                result = create_root(create_object(BINDER, true_lines), left_subtree, right_subtree);
            }
            else
            {
                tree_element* right_subtree = get_statement();
                tree_element* left_subtree = get_statement();
                result = create_root(create_object(BINDER, start_number_of_lines), left_subtree, right_subtree);
            }

            return result;
        }
        else
        {
            result = get_statement();
            return result;
        }
    }

    printf("Error in logic. Line: %d\n", __LINE__);
    return nullptr;
}

tree_element* tree::get_logic()
{
    tree_element* left_part_of_logic = nullptr;

    if (objs_->obj[cur_size_].type_of_object == BRACKET)
    {
        cur_size_++;

        left_part_of_logic = get_part_of_logic();
        
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            cur_size_++;
            return left_part_of_logic;
        }

        Object* logic_element = create_object(objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
        cur_size_++;

        tree_element* logic_result = create_root(logic_element, left_part_of_logic, get_part_of_logic());

        if (objs_->obj[cur_size_].type_of_object != BRACKET)
            printf("ERROR BRACKETS IN GET_LOGIC!! WARNING!!!!\n");
        else
            cur_size_++; // skip ')'

        return logic_result; //return left_part_of_logic;
    }
    else
    {
        printf("ERROR: NEED BRACKETS IN LOGIC. line: %d\n", __LINE__);
        return nullptr;
    }

}

tree_element* tree::get_part_of_logic()
{
    tree_element* tmp_element_1 = nullptr;

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
    {
        if (objs_->obj[cur_size_].value == OP_MIN_VAL)
        {
            cur_size_++;
            tmp_element_1 = MULTIPLY(CR_NUMBER(-1), get_operator());
        }
        else
        {
            cur_size_++;
            tmp_element_1 = get_operator(); //ADDITION(get_operator(), get_operator());
        }

    }
    else
    {
        tmp_element_1 = get_operator();
    }

    if (cur_size_ >= objs_->number_of_objects)
        return tmp_element_1;

    tree_element* tmp_element = new tree_element;

    do
    {
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            if (objs_->obj[cur_size_].value == R_BRACKET_VAL)
            {
                if (L_AND_R_NULL(tmp_element))
                {
                    tmp_element = tmp_element_1;
                    return tmp_element;
                }
                else
                {
                    return tmp_element;
                }
            }
            else
            {
                printf("BAD BRACKETS in get_express\n");
                return nullptr;
            }
        }
        else if (objs_->obj[cur_size_].type_of_object == END_OF_LINE)
        {
            if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
            {
                tmp_element = tmp_element_1;
                return tmp_element;
            }
            else
            {
                return tmp_element;
            }
        }
        else if (objs_->obj[cur_size_].type_of_object == LOGICAL_OPERATOR)
        {
            if (L_AND_R_NULL(tmp_element))
            {
                tmp_element = tmp_element_1;
                return tmp_element;
            }
            else
            {
                return tmp_element;
            }
        }

        if (IS_CUR_OBJECT_PLUS_OR_MIN)
        {
            if (!L_OR_R_NULL(tmp_element))
            {
                tree_element* new_tmp_element = new tree_element;

                new_tmp_element->set_data(&(objs_->obj[cur_size_]));

                new_tmp_element->set_left(tmp_element);
                tmp_element->set_prev(new_tmp_element);

                tree_element* tmp_element_2 = nullptr;

                cur_size_++;

                tmp_element_2 = get_operator();

                new_tmp_element->set_right(tmp_element_2);
                tmp_element_2->set_prev(new_tmp_element);

                tree_element* swap = tmp_element;
                tmp_element = new_tmp_element;
                new_tmp_element = swap;
            }
            else if (L_AND_R_NULL(tmp_element))
            {
                tmp_element->set_data(&(objs_->obj[cur_size_]));

                tmp_element->set_left(tmp_element_1);
                tmp_element_1->set_prev(tmp_element);

                cur_size_++;
                tree_element* tmp_element_2 = nullptr;
                tmp_element_2 = get_operator();

                tmp_element->set_right(tmp_element_2);
                tmp_element_2->set_prev(tmp_element);

            }
            else
            {
                printf("I HAVE BAD LOGIC(((\n");
            }
        }
        else
        {
            printf("NEED cur_size_++, cur_size_ = %d\n", cur_size_);
            printf("type = %d\nvalue = %d\n", objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
            break;
        }


    } while (IS_CUR_OBJECT_PLUS_OR_MIN && !IS_CUR_OBJECT_LOGIC_OP && !(objs_->obj[cur_size_].type_of_object == END_OF_LINE));

    return tmp_element;
}

tree_element* tree::get_statement()
{
    tree_element* result = nullptr;

    if (IS_CUR_OBJECT_LOGIC_FUNC)
    {
        Object* logic_type = create_object(LOGICAL_FUNCTION, objs_->obj[cur_size_].value);
        cur_size_++;

        tree_element* logic_argument = get_logic();
        
        tree_element* logic_block = nullptr;

        if (IS_CUR_OBJECT_L_BLOCK_BRACKET)
            logic_block = get_block();
        else
        {
            logic_block = get_statement();
            cur_size_--; // because next we well do cur_size_++ and we need TO NEUTRALIZE this because we haven't '{}'
        }

        result = create_root(logic_type, logic_argument, logic_block);
        
        cur_size_++; // MAYBE += 2 !!!!!! <-- 90% probability NOT
        return result;
    }
    else if ( (objs_->obj[cur_size_].type_of_object == MAIN_FUNCTION) && (objs_->obj[cur_size_].value == MAIN_VAL) )
    {
        //printf("HERE\n");
        Object* main_obj = create_object(MAIN_FUNCTION, MAIN_VAL);

        cur_size_++;

        if ((objs_->obj[cur_size_ + 1].type_of_object == BRACKET) && (objs_->obj[cur_size_ + 1].value == R_BRACKET_VAL))
        {
            cur_size_ += 1 + 1;
            //printf("CUR_OBJECT TYPE = %d\n", objs_->obj[cur_size_].type_of_object);
            tree_element* main_block = get_block();
            tree_element* result = create_root(main_obj, nullptr, main_block);
            return result;
        }

        printf("BAD HERE\n");
        tree_element* main_arg = get_bracket();
        tree_element* main_block = get_block();
        tree_element* result = create_root(main_obj, main_arg, main_block);
        return result;
    }
    else if ( (objs_->obj[cur_size_].type_of_object == ARITHMETIC_FUNCTION) && (objs_->obj[cur_size_].value == PRINT_VAL) )
    {
        Object* print_obj = create_object(ARITHMETIC_FUNCTION, PRINT_VAL);
        cur_size_++;

        tree_element* print_arg = get_bracket();
        result = create_root(print_obj, print_arg);
        return result;
    }
    else
    {
        tree_element* tmp_element_1 = get_number();

        if (IS_CUR_OBJECT_EQUAL_OP)
        {
            cur_size_++;
            result = CR_STATEMENT(tmp_element_1, get_expression());
        }
        else
        {
            cur_size_++;
            return tmp_element_1;
        }

        cur_size_++;
    }
    
    return result;
}

tree_element* tree::get_expression()
{
    tree_element* tmp_element_1 = nullptr;
    
    if (IS_CUR_OBJECT_PLUS_OR_MIN)
    {
        if (objs_->obj[cur_size_].value == OP_MIN_VAL)
        {
            cur_size_++;
            tmp_element_1 = MULTIPLY(CR_NUMBER(-1), get_operator());
        }
        else
        {
            cur_size_++;
            tmp_element_1 = get_operator();
        }

    }
    else
    {
        tmp_element_1 = get_operator();
    }

    if (cur_size_ >= objs_->number_of_objects)
        return tmp_element_1;

    tree_element* tmp_element = new tree_element;

    do
    {
        if (objs_->obj[cur_size_].type_of_object == BRACKET)
        {
            if (objs_->obj[cur_size_].value == R_BRACKET_VAL)
            {
                if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
                {
                    tmp_element = tmp_element_1;
                    return tmp_element;
                }
                else
                {
                    return tmp_element;
                }
            }
            else
            {
                printf("BAD BRACKETS in get_express\n");
            }
        }
        if (objs_->obj[cur_size_].type_of_object == END_OF_LINE)
        {
            if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
            {
                tmp_element = tmp_element_1;
                return tmp_element;
            }
            else
            {
                return tmp_element;
            }
        }


        if (IS_CUR_OBJECT_PLUS_OR_MIN)
        {            
            if (!L_OR_R_NULL(tmp_element))
            {
                tree_element* new_tmp_element = new tree_element;

                new_tmp_element->set_data(&(objs_->obj[cur_size_])); 

                new_tmp_element->set_left(tmp_element);
                tmp_element->set_prev(new_tmp_element);

                tree_element* tmp_element_2 = nullptr;
                
                cur_size_++;

                tmp_element_2 = get_operator();

                new_tmp_element->set_right(tmp_element_2);
                tmp_element_2->set_prev(new_tmp_element);

                tree_element* swap = tmp_element;
                tmp_element = new_tmp_element;
                new_tmp_element = swap;
            }
            else if (L_AND_R_NULL(tmp_element))
            {
                tmp_element->set_data(&(objs_->obj[cur_size_]));

                tmp_element->set_left(tmp_element_1);
                tmp_element_1->set_prev(tmp_element);
                
                cur_size_++;
                tree_element* tmp_element_2 = nullptr;
                tmp_element_2 = get_operator();

                tmp_element->set_right(tmp_element_2);
                tmp_element_2->set_prev(tmp_element);

            }
            else
            {
                printf("I HAVE BAD LOGIC(((\n");
            }
        }
        else
        {
            printf("I HAVE VAN LOGIC(((.Line = %d\n"
                    "NEED cur_size_++, cur_size_ = %d\n"
                    "type = %d\nvalue = %d\n", __LINE__, cur_size_, objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
            break;
        }
    } 
    while (IS_CUR_OBJECT_PLUS_OR_MIN && !IS_CUR_OBJECT_END_OF_LINE);

    return tmp_element;
}

tree_element* tree::get_operator()
{
    tree_element* tmp_element_1 = get_pow();
    tree_element* tmp_element = new tree_element;

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        tmp_element->set_left(tmp_element_1);
        tmp_element_1->set_prev(tmp_element);
    }
    else
    {
        delete tmp_element;
        return tmp_element_1;
    }

    while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        if ((tmp_element->get_right() != nullptr))
        {
            tree_element* new_tmp_element = new tree_element;
         
            new_tmp_element->set_data(&(objs_->obj[cur_size_])); 
            new_tmp_element->set_right(tmp_element);
            tmp_element->set_prev(new_tmp_element);

            tree_element* tmp_element_2 = nullptr;

            cur_size_++;

            tmp_element_2 = get_pow();

            new_tmp_element->set_left(tmp_element_2);
            tmp_element_2->set_prev(new_tmp_element);

            tree_element* swap = tmp_element;
            tmp_element = new_tmp_element;
            new_tmp_element = swap;
        }
        else
        {
            tmp_element->set_data(&(objs_->obj[cur_size_]));

            cur_size_++;
            tree_element* tmp_element_2 = nullptr;
            tmp_element_2 = get_pow();

            tmp_element->set_right(tmp_element_2);
            tmp_element_2->set_prev(tmp_element);

        }
    }

    return tmp_element;
}

tree_element* tree::get_pow()
{
    tree_element* tmp_element_1 = nullptr;

    tmp_element_1 = get_bracket(); 

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && (objs_->obj[cur_size_].value == OP_POW_VAL)) // if   "^"
    {
        tree_element* tmp_element_2 = nullptr;
        tree_element* tmp_element = new tree_element;

        tmp_element->set_data(&(objs_->obj[cur_size_]));

        cur_size_++;
        
        tmp_element_2 = get_pow(); 

        tmp_element->set_left(tmp_element_1);
        tmp_element->set_right(tmp_element_2);

        tmp_element_1->set_prev(tmp_element);
        tmp_element_2->set_prev(tmp_element);

        return tmp_element;
    }

    return tmp_element_1;

}

tree_element* tree::get_bracket()
{
    tree_element* tmp_element = nullptr;

    if (objs_->obj[cur_size_].type_of_object == BRACKET)
    {
        cur_size_++;

        tmp_element = get_expression();
        
        if (objs_->obj[cur_size_].type_of_object != BRACKET)
            printf("ERROR IN BRACKETS!! WARNING!!!!\n");
        else
            cur_size_++;

        return tmp_element;
    }
    else
    {
        tmp_element = get_func();

        if (tmp_element == nullptr) // Не выделилась память в get_func
            return nullptr;
    }

    printf("Error in logic. Line: %d\n", __LINE__);
    return nullptr;

}

tree_element* tree::get_func()
{
    tree_element* tmp_element = nullptr;

    if ((objs_->obj[cur_size_].type_of_object == NUMBER) || (objs_->obj[cur_size_].type_of_object == VARIABLE))
    {
        tmp_element = get_number();
    }
    else if (objs_->obj[cur_size_].type_of_object == ARITHMETIC_FUNCTION)
    {
        switch (objs_->obj[cur_size_].value)
        {
            case LN_VAL:
            case SIN_VAL:
            case COS_VAL:
            case TG_VAL:
            case CTG_VAL:
            case SH_VAL:
            case CH_VAL:
            {
                tmp_element = create_root(create_object(ARITHMETIC_FUNCTION, objs_->obj[cur_size_++].value), get_bracket());
                break;
            }
            default:
                printf("Undefined type of ARITHMETIC function\ntype = %d\n", objs_->obj[cur_size_].value);
                return nullptr;
        }

        
    }
    else
    {
        printf("Troubles in get_func()\n");
        return nullptr;
    }

    return tmp_element;
}

tree_element* tree::get_number()
{
    tree_element* tmp_element = new tree_element;
    
    tmp_element->set_data(&(objs_->obj[cur_size_]));

    cur_size_++;

    return tmp_element; 
}