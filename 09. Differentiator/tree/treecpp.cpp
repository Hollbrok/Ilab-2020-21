#include "tree.h"

const double exp_value = 2.7182818284;

int FORMULA_COUNTER = 1;

bool is_free_objs = false;

#define IS_FUNCTION(root)                                       \
    (root->get_data_type() == FUNCTION)

#define IS_NUMBER(root)                                         \
    (root->get_data_type() == NUMBER)

#define IS_VARIABLE(root)                                       \
    (root->get_data_type() == VARIABLE)

#define IS_POW(root)                                            \
    ( (root->get_data_type() == OPERATOR) && (root->get_data_value() == OP_POW_VAL) )

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

#define PRINT_UNDEFINE_OP_VALUE                                 \
    printf("Undefined OP value = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define PRINT_UNDEFINE_TYPE                                     \
    printf("Undefined type of object = [%s]\n", get_type_of_object(start_root->get_data()->type_of_object))

#define PRINT_UNDEFINE_FUNC                                     \
    printf("Undefinied func = [%s]\n", get_value_of_object(objs_, start_root->get_data()))

#define ADD_OR_SUB(obj, left, right)                            \
    create_root(obj, left, right)

#define ADDITION(left, right)                                   \
    create_root(CR_ADD, left, right)

#define MULTIPLY(left, right)                                   \
    create_root(CR_MUL, left, right)

#define EXPONENTIATION(left, right)                             \
    create_root(CR_MUL, left, right)

#define dR                                                      \
    differenciate(Rroot(start_root))

#define dL                                                      \
    differenciate(Lroot(start_root))

#define POWER()                                                 \
    create_root()

#define copyL                                                   \
    copy_subtree(Lroot(start_root))

#define copyR                                                   \
    copy_subtree(Rroot(start_root))

#define copyF                                                   \
    copy_subtree(start_root)

#define CR_LN                                                   \
    create_object(FUNCTION, LN_VAL)

#define CR_MUL                                                  \
    create_object(OPERATOR, OP_TIMES_VAL)

#define CR_ADD                                                  \
    create_object(OPERATOR, OP_PLUS_VAL)

#define CR_DEL                                                  \
    create_object(OPERATOR, OP_DEL_VAL)
    
#define CR_NUMBER(value)                                        \
    create_root(create_object(NUMBER, value))

#define GET_VAL                                                 \
    start_root->get_data_value()

#define GET_TYPE                                                \
    start_root->get_data_type()

#define PRINT_L_PART_OF_MUL                                                                                         \
    if ( IS_FUNCTION(Lroot(start_root))  || IS_NUMBER(Lroot(start_root)) || IS_VARIABLE(Lroot(start_root)) ||       \
        IS_POW(Lroot(start_root)) || IS_POW(Lroot(start_root)) || IS_MUL(Lroot(start_root)) || IS_DEL(Lroot(start_root)))   \
    {                                                                                                               \
        print_subtree(Lroot(start_root), buffer);                                                                   \
        strcat(buffer, " \\cdot ");                                                                                 \
    }                                                                                                               \
    else                                                                                                            \
    {                                                                                                               \
        strcat(buffer, "\\left(");                                                                                  \
        print_subtree(Lroot(start_root), buffer);                                                                   \
        strcat(buffer, "\\right) \\cdot ");                                                                         \
    }                                                                                           


#define PRINT_R_PART_OF_MUL                                                                                         \
    if (IS_FUNCTION(Rroot(start_root)) || IS_NUMBER(Rroot(start_root)) || IS_VARIABLE(Rroot(start_root)) ||         \
        IS_POW(Rroot(start_root)) || IS_POW(Rroot(start_root)) || IS_MUL(Rroot(start_root)) || IS_DEL(Rroot(start_root)))         \
    {                                                                                                               \
        print_subtree(Rroot(start_root), buffer);                                                                   \
    }                                                                                                               \
    else                                                                                                            \
    {                                                                                                               \
        strcat(buffer, "\\left(");                                                                                  \
        print_subtree(Rroot(start_root), buffer);                                                                   \
        strcat(buffer, "\\right)");                                                                                 \
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
    if (GET_TYPE == FUNCTION)
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
                    return pow(get_number(Lroot(start_root)), get_number(Rroot(start_root)));
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
}

void tree::optimizer_number(tree_element* start_root)
{
    switch (GET_TYPE)
    {
        case NUMBER:
            return;
        case VARIABLE:
            return;
        case FUNCTION:
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
    case FUNCTION:
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
    printf("elements = %d\n", hm_elements(start_root));

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
        case FUNCTION:
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

void tree::make_article(const char* name_of_file)
{
    assert(this && "Can't do article without tree");

    FILE* tex = fopen("main.tex", "wb");
    assert(tex && "Can't open main.tex file");

    tex_ = tex;

    print_title(tex);
    print_1_section(tex);
    print_2_section(tex);

    main_print(tex);

    print_conclusion(tex);

    print_used_books(tex);

    fprintf(tex, "\\end{document}\n");

    fclose(tex);

    system("iconv.exe -t UTF-8 -f CP1251 < main.tex > temp_main.tex");
    system("del main.tex");
    system("ren temp_main.tex main.tex");

    for (int i = 0; i < 2; i++)
    {
        system("pdflatex main.tex");
    }
     
    char* delete_old_file = new char[50]{ 0 };
    strcat(delete_old_file, "del ");
    strcat(delete_old_file, name_of_file);
    system(delete_old_file);
    delete[] delete_old_file;

    
    char* sys1 = new char[60]{ 0 };

    
    strcat(sys1, "ren main.pdf ");
    strcat(sys1, name_of_file);
    system(sys1);

    char* sys2 = new char[50]{ 0 };
    strcat(sys2, "start ");
    strcat(sys2, name_of_file);
    system(sys2);

    delete[] sys1;
    delete[] sys2;
    



    return;

}

void tree::main_print(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Как вычислить производную в 2021 году}\n\n");

    fprintf(tex, "Сейчас научим тупых греков считать прозводную на следующем примере:\n");

    char* formula = get_formula(get_root());

    fprintf(tex, formula);
    delete[] formula;

    fprintf(tex, "\n");


    tree_element* new_tree_root = differenciate(get_root());

    tree* new_tree = new tree;

    new_tree->set_root(new_tree_root);
    new_tree->objs_ = objs_;

    new_tree->show_tree("diff_tree");


    fprintf(tex, "После двух бессонных ночей, шести пачек вискаса и бутылки охоты крепкого"
        " Мы получили примерно следующее:\n");

    char* formula2 = new_tree->get_formula(new_tree->get_root());

    fprintf(tex, formula2);
    delete[] formula2;


    fprintf(tex, "Но данное выражение какое-то некрасивое, поэтому давайте его преобразуем к следующему виду:\n");

    new_tree->optimizer_number(new_tree->get_root());
    new_tree->show_tree("lvl_1_of_optimization");


    new_tree->optimizer_operator(new_tree->get_root());
    new_tree->show_tree("lvl_2_of_optimization");
    

    new_tree->optimizer_operator(new_tree->get_root());
    new_tree->optimizer_number(new_tree->get_root());
    new_tree->show_tree("lvl_3_of_optimization");


    char* formula3 = new_tree->get_formula(new_tree->get_root());

    fprintf(tex, formula3);
    delete[] formula3;

    return;
}

void print_title(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\documentclass[a4paper,12pt]{article} \n"
        "\n"
        "\n"
        "\n"
        "\\usepackage[utf8]{inputenc}\n"
        "\\usepackage[english, russian]{babel}\n"
        "\\usepackage{caption}\n"
        "\\usepackage{listings}\n"
        "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools }\n"
        "\\usepackage{wasysym}\n"
        "\\usepackage{graphicx}\n"
        "\\usepackage{float} \n"
        "\\usepackage{wrapfig} \n"
        "\\usepackage{fancyhdr} \n"
        "\\usepackage{lscape}\n"
        "\\usepackage{xcolor}\n"
        "\\usepackage[normalem]{ ulem }\n"
        "\\usepackage{hyperref}\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\\hypersetup\n"
        "{\n"
        "    colorlinks = true,\n"
        "    linkcolor = blue,\n"
        "    filecolor = magenta,\n"
        "    urlcolor = blue\n"
        "}\n"
        "\n"
        "\n"
        "\\pagestyle{fancy}\n"
        "\\fancyhead{}\n"
        "\\fancyhead[L]{ 2.2.8 }\n"
        "\\fancyhead[R]{ Талашкевич Даниил, 2 положительная группа крови}\n"
        "\\fancyfoot[C]{ \\thepage }\n"
        "\n"
        "\n"
        "\n"
        "\\begin{document}\n"
        "\n"
        "\n"
        "\\begin{titlepage}\n"
        "\n"
        "\\newpage\n"
        "\\begin{center}\n"
        "\\normalsize Московский физико - технический институт //госудраственный университет)\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{6em}\n"
        "\n"
        "\\begin{center}\n"
        "\\Large Домашняя работа по Физической культуре\\\\\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{1em}\n"
        "\n"
        "\\begin{center}\n"
        "\\large \\textbf{ Исследование термических эффектов,\n"
        "возникающих при упругих деформациях[2.2.8] }\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{2em}\n"
        "\n"
        "\\begin{center}\n"
        "\\large П$ ^ 3$ : Полная Полтрашка Патриковна и Талашкевич Даниил Александрович \\\\\n"
        "Группа Б01 - \\href{ https://vk.com/rt_kiska }{\\textbf{Гладим киску каждый день}}\n"
        "\\end{center}\n"
        "\n"
        "\\vspace{\\fill}\n"
        "\n"
        "\\begin{center}\n"
        "    \\large Иерусалим \\\\ 2 век до н.э.\n"
        "\\end{center}\n"
        "\n"
        "\\end{titlepage}\n"
        "\n"
        "\n"
        "\n"
        "    \\thispagestyle{empty}\n"
        "    \\newpage\n"
        "    \\tableofcontents\n"
        "    \\newpage\n"
        "    \\setcounter{page}{1}\n"
        "\n"
        "\n");


    return;
}

void print_1_section(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Введение в историю Иерусалима}\n\n"
        "Древнейшая часть Иерусалима была заселена в 4-м тысячелетии до н.э.,"
        " что делает его одним из древнейших городов мира. За свою долгую историю,"
        " Иерусалим был как минимум дважды разрушен, 23 раза осаждён, 52 раза атакован"
        " и 44 раза завоёван либо вновь отвоёван.\n\nВ разное время городом владели Израильское царство,"
        " Иудейское царство, Вавилон, Персидская империя и империя Александра Македонского, Египет Птолемеев,"
        " Сирия Селевкидов. После еврейского восстания во II веке до н.э. на некоторое время было восстановлено"
        " Иудейское Царство, но уже в 6 году н.э. на месте него была провозглашена римская провинция Иудея."
        " Вслед за распадом Римской империи, Иерусалим отошёл к Византии. После Византии город принадлежал"
        " арабским халифатам, крестоносцам, государствам Айюбидов и мамлюков, Османской и затем Британской"
        " империям, Иордании и, наконец, Израилю.\n\n Учитывая центральное место, отводимое Иерусалиму как"
        " еврейским, так и палестинским национализмом, на избирательность, неизбежную при"
        " резюмировании более чем 5000 - летней истории его населённости, часто накладывается идеологическая"
        " предвзятость или предшествующий опыт авторов.Еврейские периоды истории города важны для израильских"
        " националистов, дискурс которых предполагает, что современные евреи происходят от израэлитов и"
        " Маккавеев в то время как исламский, христианский и другие нееврейские периоды его истории важны"
        " для палестинского национализма, дискурс которого производит современных палестинцев от всех"
        " разнообразных народов, населявших регион. В результате каждая из сторон утверждает, что история"
        " города была политизирована оппонентами, дабы подкрепить притязания последних на город, и что это"
        " подтверждается разностью акцентов, придаваемых различными авторами разнообразным событиям и эрам в истории города.\n\n");


    return;
}

void print_2_section(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Как древние греки считали производные}\n"
        "Для того, чтобы вычислять производную греки поступили очень умно :"
        " они построили машину времени, переместились в 2021 год н.э., затем"
        " на крысичях украли мой \\textbf{exe}-шник и данную статью с подробнейшим"
        " описанием как искать ее в 2021 году, затем вернулись обратно и сковозь долгие"
        " годы они научились все - таки ее брать.Вы наверное подумаете, что это все чисто"
        " воды обман и выдумка, но у меня есть на то доказательства : \\newpage\n"
        "\n \\begin{figure}[h]\n"
        " \\center{ \\includegraphics[scale = 1]{proof.jpg} }\n"
        " \\label{ photo1:1 }\n"
        " \\end{figure}\n\n"
        " На данном фото видно, как они внаглую просто переписывают мой код!!!!"
        " P.S.Фото взято из архивов национального музея наследний ЮНЕСКО\n\n");

    return;
}

void print_conclusion(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Заключение}\n"
        " При выполнение домашней работы по физической культуре"
        " я узнал про историю Иерусалима, познакомился с тем,"
        " как греки считали производные, а так же сам научился"
        " считать производную по шагам!\n");

    return;
}

void print_used_books(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\\section{Используемые тренажеры}\n"
        " \\begin{enumerate}\n"
        " \\item Скакалка\n"
        " \\item Эскандер\n"
        " \\item Крижометр (отдельное спасибо Крижовичу за то, что предоставил его мне!)\n"
        " \\item Коксовая дорожка\n"
        " \\end{enumerate}\n");

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
                    
                    return EXPONENTIATION(derivative, copyF);
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
        case FUNCTION:
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
    //buffer_(nullptr)
{
    assert(this && "You passed nullptr to constructor");
    assert(name && "You need to pass name");
}

tree::~tree()
{
    assert(this && "nullptr in desctructor");
    printf("%s\n", __FUNCSIG__);
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
        graphviz_dump("dump.dot");

        system("iconv.exe -t UTF-8 -f  CP1251 < dump.dot > dump_temp.dot");
       
        system("dot dump_temp.dot -Tpdf -o dump.pdf");
       
        system("del dump.dot");
      
        system("ren dump_temp.dot dump.dot");
 
        system("dump.pdf");

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
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

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

    //system("iconv.exe -t UTF-8 -f  CP1251 < beauty_tree.dot > beauty_tree_temp.dot");
    system(sys1);


    char* sys2 = new char[100]{ 0 };
    strcat(sys2, "dot TEMP_176831.dot  -Tpdf -o ");
    strcat(sys2, pdf_name);
    //system("dot beauty_tree_temp.dot -Tpdf -o beauty_dump.pdf");
    system(sys2);
    


    char* sys3 = new char[100]{ 0 };
    strcat(sys3, "del ");
    strcat(sys3, dot_name);
    //system("del beauty_tree.dot");
    system(sys3);




    char* sys4 = new char[100]{ 0 };
    strcat(sys4, "ren TEMP_176831.dot ");
    strcat(sys4, dot_name);
    //system("ren beauty_tree_temp.dot beauty_tree.dot");
    system(sys4);
    
    char* sys5 = new char[50]{0};
    strcat(sys5, pdf_name);
    //system("beauty_dump.pdf");
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
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Left\", fontcolor=darkblue]\n", tmp, tmp->get_left());
    }
    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump, objs);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Right\", fontcolor=darkblue]\n", tmp, tmp->get_right());
    }

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
    {
        if (tmp->get_prev() != nullptr)
        {
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
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
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| right}| {<f2> [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_right());
        }
        else
        {
            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightblue] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%s]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), get_value_of_object(objs, tmp->get_data()), tmp->get_left(), tmp->get_prev(), tmp->get_right());
            else
                fprintf(dump, "\"%p\" [label = \"{<f0> TYPE = [%s] | VALUE = [%d]}| {<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, get_type_of_object(tmp->data_->type_of_object), tmp->get_data()->value, tmp->get_left(), tmp->get_prev(), tmp->get_right());
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
            if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = red] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = red] \n", tmp, tmp->get_data()->value);
        }
        else
        {
            if ((tmp->get_data()->type_of_object == OPERATOR) && (tmp->get_data()->value == OP_TIMES_VAL))
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = lightblue] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else if (tmp->get_data()->type_of_object != NUMBER)
                fprintf(dump, "\"%p\" [label = \"%s\",style = filled, fillcolor = purple] \n", tmp, get_value_of_object(objs, tmp->get_data()));
            else
                fprintf(dump, "\"%p\" [label = \"%d\",style = filled, fillcolor = purple] \n", tmp, tmp->get_data()->value);
        }
    }

    return;
}

void tree::fill_tree(struct Objects* main_object, bool need_print)
{
    assert(this && "Nullptr in tree");
    assert(main_object && "nullptr Objects struct");

    objs_ = main_object;

    root_ = get_expression();

    if(need_print)
        show_tree("start_tree");

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
        case FUNCTION:
            return "Function";
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
    else
    {
        switch (obj->value)
        {
            case L_BRACKET_VAL:
                return "(";
            case R_BRACKET_VAL:
                return ")";
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
            case SIN_VAL:
                return "sin";
            case COS_VAL:
                return "cos";
            case LN_VAL:
                return "ln";
            case EXP_VAL:
                return "exp";
            default:
                return "UNINDENTIFIED TYPE";
        }
    }

}

tree_element* tree::get_expression()
{
    tree_element* tmp_element_1 = nullptr;
    
    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
    {
        tree_element* tmp_element = new tree_element;
        tmp_element->set_data(&(objs_->obj[cur_size_]));

        tree_element* tmp_element_2 = nullptr;

        cur_size_++;

        tmp_element_2 = get_operator();

        tmp_element->set_right(tmp_element_1);
        tmp_element->set_left(tmp_element_2);
        
        return tmp_element;
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

        if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)))
        {            
            if ((tmp_element->get_left() != nullptr) && (tmp_element->get_right() != nullptr))
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
            else if ((tmp_element->get_left() == nullptr) && (tmp_element->get_right() == nullptr))
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
            printf("NEED cur_Size_++\n");
            printf("type = %d\nvalue = %d\n", objs_->obj[cur_size_].type_of_object, objs_->obj[cur_size_].value);
            break;
        }
        

    } while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_MIN_VAL) || (objs_->obj[cur_size_].value == OP_PLUS_VAL)));

    return tmp_element;
}

tree_element* tree::get_operator()
{
    tree_element* tmp_element_1 = get_pow();
    tree_element* tmp_element = new tree_element;

    if ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        tmp_element->set_right(tmp_element_1);
        tmp_element_1->set_prev(tmp_element);
    }
    else
    {
        delete tmp_element;
        return tmp_element_1;
    }

    while ((objs_->obj[cur_size_].type_of_object == OPERATOR) && ((objs_->obj[cur_size_].value == OP_TIMES_VAL) || (objs_->obj[cur_size_].value == OP_DEL_VAL)))
    {
        if ((tmp_element->get_left() != nullptr))
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

            tmp_element->set_left(tmp_element_2);
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

}

tree_element* tree::get_func()
{
    tree_element* tmp_element = nullptr;

    if ((objs_->obj[cur_size_].type_of_object == NUMBER) || (objs_->obj[cur_size_].type_of_object == VARIABLE))
    {
        tmp_element = get_number();
    }
    else if (objs_->obj[cur_size_].type_of_object == FUNCTION)
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
                tmp_element = create_root(create_object(FUNCTION, objs_->obj[cur_size_++].value), get_bracket());
                break;
            }
            default:
                printf("Undefined type of function\ntype = %d\n", objs_->obj[cur_size_].value);
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