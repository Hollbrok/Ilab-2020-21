#include "akinator.h"

constexpr int LT_BUT_POSITION = 265;
constexpr int LB_BUT_POSITION = 550;

constexpr int X_BUT_SIZE = 250;
constexpr int Y_BUT_SIZE = 100;

const char* BG_PATH		  = "C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/backgraund.jpg";
const char* TX_STYLE_PATH = "C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/CyrilicOld.TTF";

#define L_R_NULLPTR(root)												\
	((root->get_left() == nullptr) && (root->get_right() == nullptr))


#define CR_TEXT(Text_name, size, color, text, Xpos, Ypos)		\
	Text Text_name("", font, size);								\
	Text_name.setColor(color);									\
	Text_name.setStyle(Text::Bold);								\
	Text_name.setString(text);									\
	Text_name.setPosition(Xpos, Ypos)	


#define CR_RECT(Name, Xsize, Ysize, moveX, moveY, color)		\
	RectangleShape Name (Vector2f(Xsize, Ysize));				\
	Name.move(moveX, moveY);									\
	Name.setFillColor(color)	

#pragma warning(disable : 4996)

long size_of_file(FILE *user_code)
{
	assert(user_code);

	fseek(user_code, 0, SEEK_END);
	long file_length = ftell(user_code);
	fseek(user_code, 0, SEEK_SET);

	file_length++;

	return file_length;
}

char* make_buffer(const char* name_file)
{
	FILE* database = fopen("database.txt", "rb");
	assert(database && "Can't open database.txt");

	long file_length = size_of_file(database);

	char* buffer = new char[file_length];
	assert(buffer && "Can't calloc memory for buffer");

	fread(buffer, sizeof(char), file_length, database);
	return buffer;
}

void tree::play()
{
	assert(this && "You passed nullptr yo play()");

	print_hello();

	const char* name_of_file = "database.txt";
	fill_tree(name_of_file);

	while (true)
	{
		int number_of_game = get_number_of_game();

		if (number_of_game == 5)
			break;
		else
			switch (number_of_game)
			{
				case 1:
					play_1();
					break;
				case 2:
					play_2();
					break;
				case 3:
					play_3();
					break;
				case 4:
					play_4();
					break;
				default:
					printf("Not indentified number of regime\n");
					break;
			}
	}

	printf("Updating data base..\n");

	const char* name_of_new_base = "database.txt";
	update_database(name_of_new_base);

	printf("Done!\n");

	return;
}

constexpr bool IsRussianChar1251(const char c)
{
	return (c >= 'А' && c <= 'я') || c == 'ё' || c == 'Ё';
}

int get_number_of_game()
{
	int number_of_game = 0;
	int number_of_scanf_digits = 0;

	char user_data[256] = {};

	while (true)
	{
		printf("Введите цифру режима игры: ");

		gets_s(user_data);
		user_data[strlen(user_data)] = '\0';

		if (IsRussianChar1251(user_data[0]))
			continue;
		if (isalpha(user_data[0]))
			continue;

		if (strlen(user_data) != 1)
		{
			fflush(stdin);
			continue;
		}

		number_of_game = atoi(user_data);

		if (!(0 < number_of_game) || !(number_of_game < 6))
			continue;

		break;
	}
	printf("\n\n");
	return number_of_game;
}

void print_hello()
{
	printf("\t\tПриветствую тебя.\nЧтобы сыграть можешь выбрать один в следующих режимов игры:\n"
			"\t1. Угадать загаданный предмет/героя\n"
			"\t2. Показать базу\n"
			"\t3. Характеристика предмета\n"
			"\t4. Сравнение двух предметов\n"
			"\t5. Выйти\n\n");
	return;
}

void tree::play_1()
{
	assert(this && "You passed nullptr tree to play_1");

	if (root_)
	{
		printf("Правила игры:\n"
			"\t 1) Загадайте предмет\n"
			"\t 2) Я буду угадывать его\n"
			"\t 3) Если ваш да, то введите \"y\" \n"
			"\t 4) Если нет, то \"n\" \n\n\n");

		check_answer(root_);
	}
	else
		printf("Дерево не создано\n");

	return;
}

void tree::play_2()
{
	show_tree();
	return;
}

void tree::play_3()
{
	printf("\t Введите имя предмета, чтобы посмотреть его свойства\n:");
	char* user_object = get_data_from_user();
	printf("Ваш предмет [%s], и он обладает следующими свойствами:\n", user_object);
	
	bool find_word = get_root()->find_word(user_object);

	if (!find_word)
		printf("1. Предмет обладает только одним признаком: ЕГО НЕТ В БАЗЕ\n");
	else
	{
		//printf("here");
		get_root()->get_attributes(user_object);
	}
	printf("\n");
	delete[] user_object;
	return;
}

void tree_element::get_attributes(char* word)
{
	static int counter = 1;
	if (!strncmp(data_, word, length_))
	{
		//printf("ret0\n");
		return;
	}

	if (get_left() != nullptr)
	{
		bool find_answer = get_left()->find_word(word);
		if (find_answer)
		{
			printf("%d. не %.*s\n", counter++, length_, data_);
			get_left()->get_attributes(word);
		}
		else if (get_right() != nullptr)
		{
			printf("%d. %.*s\n", counter++, length_, data_);
			get_right()->get_attributes(word);
		}
	}


	return;
}


void tree::play_4()
{
	printf("\t Введите имя первого предмета, чтобы сравнить его со вторым\n:");
	char* user_object_1 = get_data_from_user();
	
	bool find_word_1 = get_root()->find_word(user_object_1);
	
	if (!find_word_1)
	{
		printf("Извините, но такого слова нет в базе\n");
		return;
	}

	printf("\n\t Введите имя второго предмета\n:");
	char* user_object_2 = get_data_from_user();

	bool find_word_2 = get_root()->find_word(user_object_2);

	if (!find_word_2)
	{
		printf("Извините, но такого слова нет в базе\n");
		return;
	}

	printf("Начинаем сравнение..\n\n");
	
	bool* attributes_1 = new bool[20]{0};
	bool* attributes_2 = new bool[20]{0};

	int cur_size_1 = 0;
	attributes_1 = get_root()->get_attributes_massive(user_object_1, cur_size_1, attributes_1);


	int cur_size_2 = 0;
	attributes_2 = get_root()->get_attributes_massive(user_object_2, cur_size_2, attributes_2);


	get_root()->compare_attributes(attributes_1, cur_size_1, attributes_2, cur_size_2, user_object_1, user_object_2);


	delete[] attributes_1;
	delete[] attributes_2;
	return;
}

void tree_element::compare_attributes(bool* attr1, int size1, bool* attr2, int size2, char* obj1, char* obj2)
{
	int min = size1 < size2 ? size1 : size2;

	int counter = 1;

	int i = 0;

	if (min == 0) {}
	else if (attr1[i] == attr2[i])
	{
		printf("Схожи тем, что :\n");
		while (attr1[i] == attr2[i])
		{
			char* question = get_question_from_massive(attr1, i);
			if (attr1[i++])
				printf("%d. %s\n", counter++, question);
			else printf("%d. НЕ %s\n", counter++, question);
			delete[] question;
		}
	}
	else
		printf("\t НИЧЕГО общего найти не удалось\n\n");

	if(i < size1)
		printf("\n	В свою очередь [%s] имеет слудующие характеристики:\n", obj1);
	counter = 0;

	for (int last_attr = i; last_attr < size1; last_attr++)
	{
		char* question = get_question_from_massive(attr1, last_attr);
		if (attr1[last_attr])
			printf("%d. %s\n", counter++, question);
		else printf("%d. НЕ %s\n", counter++, question);
		delete[] question;
	}

	if(i < size2)
		printf("\n	И на последок [%s] имеет такие свойства:\n", obj2);
	counter = 0;
	//printf("i = %d, size2 = %d\n", i, size2);
	for (int last_attr = i; last_attr < size2; last_attr++)
	{
		//printf("last_attr = %d\n", last_attr);
		char* question = get_question_from_massive(attr2, last_attr);
		if (attr2[last_attr])
			printf("%d. %s\n", counter++, question);
		else printf("%d. НЕ %s\n", counter++, question);
		delete[] question;
	}

	printf("\n\n");

	return;
}

char* tree_element::get_question_from_massive(bool* attributes, int size)
{
	tree_element* start = this;

	char* attribute = new char[100] {0};
	
	for (int i = 0; i < size; i++)
	{
		if (attributes[i] == true)
			start = start->get_right();
		else start = start->get_left();
	}
	
	//printf("1\n");
	strncpy(attribute, start->non_const_get_data(), start->length_);// attribute
	//printf("2\n");
	attribute[start->length_] = '\0';

	return attribute;
}

bool* tree_element::get_attributes_massive(char* word, int& cur_size, bool* attributes)
{
	if (!strncmp(data_, word, length_))
	{
		return attributes;
	}
	if (get_left() != nullptr)
	{
		bool find_answer = get_left()->find_word(word);
		
		if (find_answer)
		{
			//printf("%d. не %.*s\n", counter++, length_, data_);
			attributes[cur_size++] = 0;
			//printf("cur_size++\n");
			get_left()->get_attributes_massive(word, cur_size, attributes);
		}
		else if (get_right() != nullptr)
		{
			//printf("%d. %.*s\n", counter++, length_, data_);
			attributes[cur_size++] = 1;
			//printf("cur_size++. cur_size = %d\n", cur_size);
			get_right()->get_attributes_massive(word, cur_size, attributes);
		}
	}
	return attributes;
}

bool tree_element::find_word(char* word)
{
	//static int counter = 1;
	if (!strncmp(data_, word, length_))
	{
		return true;
	}

	if (get_left() != nullptr)
	{
		if (get_left()->find_word(word))
		{
			return true;
		}
		else if (get_right() != nullptr)
		{
			if (get_right()->find_word(word))
				return true;
			else
				return false;
		}
		else
			return false;
	}

	if ((get_right() == nullptr) && (get_left() == nullptr))
	{
		return false;
	}

	//printf("return true\n");
	return true;
}

void check_answer(tree_element* question)
{
	assert(question && "nullptr question in check_answer");

	if (L_R_NULLPTR(question))
	{
		printf("\t\tКажется я нашел ваш предмет!\n");

		if (question->get_user_answer())
			printf("\t\tЯ так рад, что смог угадать твой предмет!!\n");
		else
		{
			tree_element* prev_question = question->get_prev();

			printf("\t\tЖаль, что не удалось, но я\n\t\tпопробую угадать в следующий раз!\n"
					"\t\tМожешь ввести имя загаданного предмета?\n:");

			tree_element* user_element = create_root(get_data_from_user(), nullptr, nullptr, nullptr);

			printf("\t\tА теперь какое-нибудь его свойство, которого нет в моем слове\n:");
			
			tree_element* user_attribute = create_root(get_data_from_user(), question, user_element, question->get_prev());

			user_element->set_prev(user_attribute);
			
			if (prev_question->get_right() == question)
				prev_question->set_right(user_attribute);
			else if (prev_question->get_left() == question)
				prev_question->set_left(user_attribute);
			else
				printf("Something bad in line: %d", __LINE__);
				
			user_attribute->set_prev(question->get_prev());
			question->set_prev(user_attribute);
			
			printf("\t\tСпасибо, что пополнил базу!\n");
		}
	}
	else if (question->get_user_answer())		// if true ==>> go to right
		check_answer(question->get_right());	//
	else                                        // else go to left
		check_answer(question->get_left());

	return;
}

bool tree_element::get_user_answer()
{
	printf("\t\t%.*s?\n", length_, data_);
	char user_data[256] = {};

	while (true)
	{
		gets_s(user_data);

		if (strlen(user_data) != 1)
		{
			printf("Нет такого варианта ответа\n");
			fflush(stdin);
			continue;
		}

		if ((user_data[0] == 'y') || (user_data[0] == 'Y') || (user_data[0] == 'n') || (user_data[0] == 'N'))
			break;

		printf("Нет такого варианта ответа\n");
		fflush(stdin);
		continue;
	}
	return ((user_data[0] == 'Y') || (user_data[0] == 'y'));
}

char* get_data_from_user()
{
	char* user_data = new char[256];

	gets_s(user_data, 256);

	int length = strlen(user_data);

	while (user_data[length] == '?')
		length--;

	user_data[length] = '\0';

	return user_data;
}

void tree::update_database(const char* name_file)
{
	assert(name_file && "no file name");

	FILE* database = fopen(name_file, "wb");
	assert(database && "Can't open file to update database");

	tree_element* root = get_root();
	root->print_elem(database);

	return;
}

void tree_element::print_elem(FILE* database)
{
	assert(database);
	assert(this);

	fprintf(database, "[\n");

	if (get_left() != nullptr)
	{
		fprintf(database, "?%.*s?\n", length_, data_);
		get_left()->print_elem(database);
	}

	if (get_right() != nullptr)
		get_right()->print_elem(database);

	if ((get_right() == nullptr) && (get_left() == nullptr))
		fprintf(database, "`%.*s`\n", length_, data_);

	fprintf(database, "]\n");

	return;
}


using namespace sf;
	
void tree::graphic_play()
{
	assert(this);

	const char* name_of_file = "database.txt";
	fill_tree(name_of_file);

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	bool NEED_MENU		= false;
	bool REGIME_1		= false;
	bool FIND_WORD		= false;
	bool NEED_UPDATE	= false;
	bool WAIT_WORD		= false;
	bool WORD_DONE		= false;
	bool NEED_QUESTION	= false;
	bool QUESTION_DONE	= false;
	bool NEED_UPDATE_BASE = false;
	bool REGIME_2		= false;
	bool PLAY_AGAIN		= false;
	
	bool DRAW_BUTTON	 = true;
	bool WAIT_FOR_REGIME = true;

	RenderWindow window(VideoMode(800, 939), "Akinator", Style::Default, settings);

	Texture texture;
	texture.loadFromFile(BG_PATH);
	Sprite sprite(texture);
	sprite.setColor(Color::Green);


	Font font; // ШРИФТ
	font.loadFromFile(TX_STYLE_PATH);


	CR_TEXT(text, 50, Color::Red, "Играть", LT_BUT_POSITION + 40, LB_BUT_POSITION + 10);
	CR_TEXT(exit_but, 50, Color::Magenta, "Выйти", LT_BUT_POSITION + 40, LB_BUT_POSITION + 10 + Y_BUT_SIZE + 10);
	CR_TEXT(regime1, 50, Color::Blue, "Угадайка", 120, 350);
	CR_TEXT(regime2, 50, Color::Blue, "Дерево", 120 + X_BUT_SIZE + 50, 350);
	CR_TEXT(yes_text, 50, Color::Green, "Да", 180, 450);
	CR_TEXT(no_text, 50, Color::Red, "Нет", 170 + X_BUT_SIZE + 100, 450);
	CR_TEXT(user_text, 50, Color::Red, "", 150 + 100 + 150, 440);

	CR_RECT(rectangle, X_BUT_SIZE, Y_BUT_SIZE, LT_BUT_POSITION, LB_BUT_POSITION, Color(175, 180, 240));
	CR_RECT(yes_rect, X_BUT_SIZE, Y_BUT_SIZE, 100, 440, Color(175, 180, 240));
	CR_RECT(no_rect, X_BUT_SIZE, Y_BUT_SIZE, 100 + X_BUT_SIZE + 100, 440, Color(175, 180, 240));
	CR_RECT(reg2_rect, X_BUT_SIZE, Y_BUT_SIZE, 100 + X_BUT_SIZE + 50, 340, Color(175, 180, 240));
	CR_RECT(reg1_rect, X_BUT_SIZE, Y_BUT_SIZE, 100, 340, Color(175, 180, 240));
	CR_RECT(exit_rect, X_BUT_SIZE, Y_BUT_SIZE, LT_BUT_POSITION, LB_BUT_POSITION + Y_BUT_SIZE + 10, Color(175, 180, 240));
	CR_RECT(user_word_rect, 500, Y_BUT_SIZE, 150, 440, Color(175, 180, 240));

	tree_element* tmp_root = new tree_element;

	tmp_root = root_;

	char question[100];
	char user_word[100];
	int cur_size = 0;

	char user_question[100];
	int cur_size_q = 0;

	Vector2i pos;
	int x;
	int y;

	while (window.isOpen())
	{
		pos = Mouse::getPosition(window);
		x = pos.x;
		y = pos.y;

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
							window.close();
					}
					if (DRAW_BUTTON)
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
						{
							if ((LB_BUT_POSITION <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE))
							{
								text.setColor(Color::Green);
								window.draw(text);

								DRAW_BUTTON = false;
								NEED_MENU = true;

								text.setColor(Color::Black);
								text.setString("Выберите режим игры:");
								text.move(-150, -330);
								rectangle.move(-170, -330);

								rectangle.setSize(sf::Vector2f(600, 100));
								rectangle.setFillColor(Color(175, 180, 240));
							}
							else if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
								window.close();
						}
					}
					else if (REGIME_1)
					{
						if (true)
						{
							if ((440 <= y) && (y <= 440 + Y_BUT_SIZE))
							{

								if ((100 + X_BUT_SIZE + 100 <= x) && (x <= 100 + X_BUT_SIZE + 100 + X_BUT_SIZE))
								{
									if (tmp_root->get_left())
									{
										tmp_root = tmp_root->get_left();
										strncpy(question, tmp_root->data_, tmp_root->length_);

										question[tmp_root->length_] = '?';
										question[tmp_root->length_ + 1] = '\0';

										text.setPosition(155 + 125 + ((tmp_root->length_ + 1) / 20) * (-30), 230);
										text.setString(question);
									}
									else
									{
										FIND_WORD = true;
										tmp_root->set_left(nullptr);
										tmp_root->set_right(nullptr);

										text.setPosition(205, 230);
										text.setString("Какой был предмет?");
										WAIT_WORD = true;
									
										REGIME_1 = false;

										NEED_UPDATE = true;
									}
								}
								else if ((100 <= x) && (x <= 350))
								{
									if (tmp_root->get_right())
									{
										tmp_root = tmp_root->get_right();

										strncpy(question, tmp_root->data_, tmp_root->length_);

										question[tmp_root->length_] = '?';
										question[tmp_root->length_ + 1] = '\0';

										text.setPosition(155 + 125 + ((tmp_root->length_ + 1) / 20) * (-30), 230);

										text.setString(question);

									}
									else
									{
										FIND_WORD = true;
										tmp_root->set_left(nullptr);
										tmp_root->set_right(nullptr);

										text.setPosition(155 + 125 + (15 / 20 - 1) * (-30), 230);

										text.setString("Спасибо за игру");

										REGIME_1 = false;
									}
								}
							}
						}
					}
					else if (NEED_MENU)
					{
						if ((100 <= x) && (x <= 100 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_1 = true;

								strncpy(question, root_->data_, root_->length_);
								question[root_->length_] = '?';
								question[root_->length_ + 1] = '\0';

								text.setPosition(155 + 125 + ((tmp_root->length_ + 1) / 20 - 1) * (-30), 230);

								text.setCharacterSize(30);
								text.setString(question);
							}
						}
						else if ((100 + X_BUT_SIZE + 50 <= x) && (x <= 100 + X_BUT_SIZE + 50 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_2 = true;
							}
						}
					}
					if ((100 + X_BUT_SIZE + 50 <= x) && (x <= 100 + X_BUT_SIZE + 50 + X_BUT_SIZE))
						if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
							window.close();

				}
			}

			if (WAIT_WORD)
				if (event.type == sf::Event::KeyPressed)
				{
					//printf("here\n\n");
					if (static_cast<char>(event.text.unicode) == 58)
					{
						WAIT_WORD = false;
						WORD_DONE = true;
						user_word[cur_size] = '\0';
						user_text.setPosition(150 + 100 + 150, 440);
					}
					else
					{
						if (event.key.code == Keyboard::Q) user_word[cur_size++] = 'й';
						else if (event.key.code == Keyboard::W) user_word[cur_size++] = 'ц';
						else if (event.key.code == Keyboard::E) user_word[cur_size++] = 'у';
						else if (event.key.code == Keyboard::R) user_word[cur_size++] = 'к';
						else if (event.key.code == Keyboard::T) user_word[cur_size++] = 'е';
						else if (event.key.code == Keyboard::Y) user_word[cur_size++] = 'н';
						else if (event.key.code == Keyboard::U) user_word[cur_size++] = 'г';
						else if (event.key.code == Keyboard::I) user_word[cur_size++] = 'ш';
						else if (event.key.code == Keyboard::O) user_word[cur_size++] = 'щ';
						else if (event.key.code == Keyboard::P) user_word[cur_size++] = 'з';
						else if (event.key.code == Keyboard::LBracket) user_word[cur_size++] = 'х';
						else if (event.key.code == Keyboard::RBracket) user_word[cur_size++] = 'ъ';
						else if (event.key.code == Keyboard::A) user_word[cur_size++] = 'ф';
						else if (event.key.code == Keyboard::S) user_word[cur_size++] = 'ы';
						else if (event.key.code == Keyboard::D) user_word[cur_size++] = 'в';
						else if (event.key.code == Keyboard::F) user_word[cur_size++] = 'а';
						else if (event.key.code == Keyboard::G) user_word[cur_size++] = 'п';
						else if (event.key.code == Keyboard::H) user_word[cur_size++] = 'р';
						else if (event.key.code == Keyboard::J) user_word[cur_size++] = 'о';
						else if (event.key.code == Keyboard::K) user_word[cur_size++] = 'л';
						else if (event.key.code == Keyboard::L) user_word[cur_size++] = 'д';
						else if (event.key.code == Keyboard::Semicolon) user_word[cur_size++] = 'ж';
						else if (event.key.code == Keyboard::Hyphen) user_word[cur_size++] = '-';
						else if (event.key.code == Keyboard::Comma) user_word[cur_size++] = 'б';
						else if (event.key.code == Keyboard::Period) user_word[cur_size++] = 'ю';
						else if (event.key.code == Keyboard::Quote) user_word[cur_size++] = 'э';
						else if (event.key.code == Keyboard::Z) user_word[cur_size++] = 'я';
						else if (event.key.code == Keyboard::X) user_word[cur_size++] = 'ч';
						else if (event.key.code == Keyboard::C) user_word[cur_size++] = 'с';
						else if (event.key.code == Keyboard::V) user_word[cur_size++] = 'м';
						else if (event.key.code == Keyboard::B) user_word[cur_size++] = 'и';
						else if (event.key.code == Keyboard::N) user_word[cur_size++] = 'т';
						else if (event.key.code == Keyboard::M) user_word[cur_size++] = 'ь';
						else if (event.key.code == Keyboard::Q) user_word[cur_size++] = 'й';
						else if (event.key.code == Keyboard::Space) user_word[cur_size++] = ' ';
						else if (event.key.code == Keyboard::Num1) user_word[cur_size++] = '1';
						else if (event.key.code == Keyboard::Num2) user_word[cur_size++] = '2';
						else if (event.key.code == Keyboard::Num3) user_word[cur_size++] = '3';
						else if (event.key.code == Keyboard::Num4) user_word[cur_size++] = '4';
						else if (event.key.code == Keyboard::Num5) user_word[cur_size++] = '5';
						else if (event.key.code == Keyboard::Num6) user_word[cur_size++] = '6';
						else if (event.key.code == Keyboard::Num7) user_word[cur_size++] = '7';
						else if (event.key.code == Keyboard::Num8) user_word[cur_size++] = '8';
						else if (event.key.code == Keyboard::Num9) user_word[cur_size++] = '9';
						else if (event.key.code == Keyboard::Num0) user_word[cur_size++] = '0';
						else if (event.key.code == Keyboard::BackSpace) {
							if (cur_size > 0)
							{
								user_word[cur_size--] = '\0';
								user_text.move(+30, 0);
							}
							else
							{
								user_text.move(+15, 0);
								printf("cur_size == 0\n");
							}
						}

						user_word[cur_size] = '\0';
						user_text.setString(user_word);
						user_text.move(-15, 0);
					}

				}
			if (NEED_QUESTION)
				if (event.type == sf::Event::KeyPressed)
				{
					if (static_cast<char>(event.text.unicode) == 58)
					{
						NEED_QUESTION = false;
						QUESTION_DONE = true;
						user_question[cur_size_q] = '\0';
					}
					else
					{
						if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = 'й';
						else if (event.key.code == Keyboard::W) user_question[cur_size_q++] = 'ц';
						else if (event.key.code == Keyboard::Space) user_question[cur_size_q++] = ' ';
						else if (event.key.code == Keyboard::E) user_question[cur_size_q++] = 'у';
						else if (event.key.code == Keyboard::R) user_question[cur_size_q++] = 'к';
						else if (event.key.code == Keyboard::T) user_question[cur_size_q++] = 'е';
						else if (event.key.code == Keyboard::Y) user_question[cur_size_q++] = 'н';
						else if (event.key.code == Keyboard::U) user_question[cur_size_q++] = 'г';
						else if (event.key.code == Keyboard::I) user_question[cur_size_q++] = 'ш';
						else if (event.key.code == Keyboard::O) user_question[cur_size_q++] = 'щ';
						else if (event.key.code == Keyboard::P) user_question[cur_size_q++] = 'з';
						else if (event.key.code == Keyboard::LBracket) user_question[cur_size_q++] = 'х';
						else if (event.key.code == Keyboard::RBracket) user_question[cur_size_q++] = 'ъ';
						else if (event.key.code == Keyboard::A) user_question[cur_size_q++] = 'ф';
						else if (event.key.code == Keyboard::S) user_question[cur_size_q++] = 'ы';
						else if (event.key.code == Keyboard::D) user_question[cur_size_q++] = 'в';
						else if (event.key.code == Keyboard::F) user_question[cur_size_q++] = 'а';
						else if (event.key.code == Keyboard::G) user_question[cur_size_q++] = 'п';
						else if (event.key.code == Keyboard::H) user_question[cur_size_q++] = 'р';
						else if (event.key.code == Keyboard::J) user_question[cur_size_q++] = 'о';
						else if (event.key.code == Keyboard::K) user_question[cur_size_q++] = 'л';
						else if (event.key.code == Keyboard::L) user_question[cur_size_q++] = 'д';
						else if (event.key.code == Keyboard::Semicolon) user_question[cur_size_q++] = 'ж';
						else if (event.key.code == Keyboard::Hyphen) user_question[cur_size_q++] = '-';
						else if (event.key.code == Keyboard::Comma) user_question[cur_size_q++] = 'б';
						else if (event.key.code == Keyboard::Period) user_question[cur_size_q++] = 'ю';
						else if (event.key.code == Keyboard::Quote) user_question[cur_size_q++] = 'э';
						else if (event.key.code == Keyboard::Z) user_question[cur_size_q++] = 'я';
						else if (event.key.code == Keyboard::X) user_question[cur_size_q++] = 'ч';
						else if (event.key.code == Keyboard::C) user_question[cur_size_q++] = 'с';
						else if (event.key.code == Keyboard::V) user_question[cur_size_q++] = 'м';
						else if (event.key.code == Keyboard::B) user_question[cur_size_q++] = 'и';
						else if (event.key.code == Keyboard::N) user_question[cur_size_q++] = 'т';
						else if (event.key.code == Keyboard::M) user_question[cur_size_q++] = 'ь';
						else if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = 'й';
						else if (event.key.code == Keyboard::Num0) user_question[cur_size_q++] = '0';
						else if (event.key.code == Keyboard::Num1) user_question[cur_size_q++] = '1';
						else if (event.key.code == Keyboard::Num2) user_question[cur_size_q++] = '2';
						else if (event.key.code == Keyboard::Num3) user_question[cur_size_q++] = '3';
						else if (event.key.code == Keyboard::Num4) user_question[cur_size_q++] = '4';
						else if (event.key.code == Keyboard::Num5) user_question[cur_size_q++] = '5';
						else if (event.key.code == Keyboard::Num6) user_question[cur_size_q++] = '6';
						else if (event.key.code == Keyboard::Num7) user_question[cur_size_q++] = '7';
						else if (event.key.code == Keyboard::Num8) user_question[cur_size_q++] = '8';
						else if (event.key.code == Keyboard::Num9) user_question[cur_size_q++] = '9';
						else if (event.key.code == Keyboard::BackSpace) {
							if (cur_size_q > 0)
							{
								user_question[cur_size_q--] = '\0';
								user_text.move(+30, 0);
							}
							else printf("cur_size_q == 0\n");

						}

						user_question[cur_size_q] = '\0';
						user_text.setString(user_question);
						user_text.move(-15, 0);
					}

				}

		}

		//window.clear(Color::White);

		window.draw(sprite);
		window.draw(rectangle);


		if (PLAY_AGAIN)
		{
			window.draw(rectangle);
			window.draw(text);
		}
		
		if (DRAW_BUTTON)
			window.draw(text);

		else if (NEED_MENU)
		{
			window.draw(text);

			window.draw(reg1_rect);
			window.draw(regime1);

			window.draw(reg2_rect);
			window.draw(regime2);

		}
		else if (FIND_WORD && !WAIT_WORD)
		{
			window.draw(text);
			window.draw(rectangle);
			window.draw(text);
		}
		else if (REGIME_1)
		{
			window.draw(text);

			window.draw(yes_rect);
			window.draw(no_rect);

			window.draw(yes_text);
			window.draw(no_text);
		}

		if (WORD_DONE)
		{
			//printf("[%s]\n", user_word);
			WORD_DONE = false;
			NEED_QUESTION = true;
			text.move(-100, 0);
			text.setString("Чем ваш предмет отличается от моего?");
			user_text.setString("");
		}
		if (QUESTION_DONE)
		{
			//printf("[%s]\n", user_question);
			QUESTION_DONE = false;
			NEED_UPDATE_BASE = true;
			text.move(75, 0);
			text.setString("Спасибо большое за игру!");
		}
		if (NEED_QUESTION)
		{
			window.draw(text);

			window.draw(user_word_rect);
			window.draw(user_text);
		}
		if (WAIT_WORD)
		{
			window.draw(user_word_rect);
			window.draw(user_text);
			window.draw(text);
		}
		if (REGIME_2)
		{
			show_tree();
			REGIME_2 = false;

			NEED_MENU = true;
			text.setString("Выберите режим игры:");
		}

		window.draw(exit_rect);
		window.draw(exit_but);

		window.display();
	}

	if (NEED_UPDATE_BASE)
	{
		tree_element* user_element = new tree_element;
		assert(user_element);
		char* new_data = new char[strlen(user_word)];
		strncpy(new_data, user_word, strlen(user_word));


		user_element->data_ = new_data;
		user_element->user_length_ = strlen(user_word);
		user_element->length_ = user_element->user_length_;

		tree_element* user_attribute = new tree_element;
		assert(user_attribute);

		char* new_question = new char[strlen(user_question)];
		strncpy(new_question, user_question, strlen(user_question));


		user_attribute->data_ = new_question;
		user_attribute->user_length_ = strlen(user_question);
		user_attribute->length_ = user_attribute->user_length_;


		user_element->set_prev(user_attribute);


		user_attribute->set_right(user_element);
		user_attribute->set_left(tmp_root);

		if ((tmp_root->get_prev())->get_right() == tmp_root)
			(tmp_root->get_prev())->set_right(user_attribute);

		else if ((tmp_root->get_prev())->get_left() == tmp_root)
			(tmp_root->get_prev())->set_left(user_attribute);

		else
			printf("Something bad in line: %d", __LINE__);

		user_attribute->set_prev(tmp_root->get_prev());
		tmp_root->set_prev(user_attribute);
	}

	const char* name_of_new_base = "database.txt";
	update_database(name_of_new_base);
	printf("Done!\n");

	return;
}
