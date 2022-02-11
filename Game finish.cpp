#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#define Number_of_free_space (size_of_map1_2 * size_of_map1_2) - number_of_walls(size_of_map1_2, map1_3)
using namespace std;
int userNumber = 0;
int number_of_coins = 0;
int X_new = 0, Y_new = 0, X_old = 0, Y_old = 0;
int number_of_focused_option = 0;
int number_of_options = 0;
int amount_of_coins = 0;
int number_of_levels = 0;
bool Rand_om = false;
bool multi_form_map = false;
int size_of_map1_0 = 0;
int difficulty = 1;
int vis_x = 0;
int vis_y = 0;
void out_data() {
    FILE* data;
    data = fopen("C:\\Users\\Kniroke\\source\\repos\\Game4\\data\\data.txt", "r");
    if (!data) cout << "File was not opened";
    fscanf(data, "Number of coins: %d\nNumber of levels : %d\nSize of map : %d\nRandom : %b\n Multi-form map: %b\nDifficulty: %d",
        &amount_of_coins, &number_of_levels, &size_of_map1_0, &multi_form_map, &difficulty);
}
void print_menu(char** menu_1, int* height1_1, int* width1_1) {
    for (int i = 0; i < *height1_1; i++) {
        for (int j = 0; j < *width1_1; j++)
            cout << menu_1[i][j];
        cout << endl;
    }
}
enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};
void SetColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
int entered_size_of_map() {
    int size_of_map;
    do {
        cout << "Enter an odd size of a map from 7 to 23" << endl;
        cin >> size_of_map;
    } while ((size_of_map < 0) || (size_of_map < 7) || (size_of_map > 23) || ((size_of_map % 2) == 0));
    return size_of_map;
}
void put_rand_coins(char** map1_3) {
    srand(time(NULL));
    int rand_y = 0;
    int rand_x = 0;
    int coins_now = 0;
    while (coins_now != amount_of_coins) {
        rand_y = rand() % (size_of_map1_0);
        rand_x = rand() % (size_of_map1_0);
        if ((map1_3[rand_y][rand_x] != '#') && (map1_3[rand_y][rand_x] != '@') && (map1_3[rand_y][rand_x] != '0')) {
            map1_3[rand_y][rand_x] = '0';
            coins_now++;
        };
    }
}
char** fulfill_map() {
    char** map = new char* [size_of_map1_0];
    for (int i = 0; i < size_of_map1_0; i++)map[i] = new char[size_of_map1_0];
    for (int i = 0; i < size_of_map1_0; i++)
        for (int j = 0; j < size_of_map1_0; j++) map[i][j] = ' ';
    return map;
}
void clean_array(char** map1_3, int height_of_map, int width_of_map) {
    for (int i = 0; i < height_of_map; i++) {
        for (int j = 0; j < width_of_map; j++) {
            map1_3[i][j] = ' ';
        }
    }
}
void center_the_text(char** map1_3, string(*text1_1), int height_of_map, int width_of_map, int y) {
    int length_of_text = text1_1->length();
    int x = (width_of_map - length_of_text) / 2;
    for (int j = 0; j < length_of_text; x++, j++) {
        map1_3[y][x] = (*text1_1)[j];
    }
}
int put_the_text(int x, int y, int height, int width, char** menu1_2, string* text1_1) {
    int length_of_text = text1_1->length() - 1;
    for (int j = 0; (x < length_of_text + x) && (j < (length_of_text + 1)); x++, j++)
        menu1_2[y][x] = (*text1_1)[j];
    return length_of_text;
}
void put_the_text_in_option_menu(int height, int width, char** menu1_1) {
    string
        text0_1 = { "Number of coins" },
        text1_1 = { "Number of levels" },
        text2_1 = { "Size of map" },
        text3_1 = { "Random" },
        text4_1 = { "Multi-form map" },
        text5_1 = { "Difficulty" },
        text6_1 = { "Back" };
    int x = 0, y = 0;
    y = 1; x = 1;
    put_the_text(x, y, height, width, menu1_1, &text0_1);
    x = 23;
    put_the_text(x, y, height, width, menu1_1, &text1_1);
    y = 5; x = 1;
    put_the_text(x, y, height, width, menu1_1, &text2_1);
    x = 23;
    put_the_text(x, y, height, width, menu1_1, &text3_1);
    y = 9; x = 1;
    put_the_text(x, y, height, width, menu1_1, &text4_1);
    x = 23;
    put_the_text(x, y, height, width, menu1_1, &text5_1);
    y = 13; x = 16;
    put_the_text(x, y, height, width, menu1_1, &text6_1);
    y = 0; x = 0;
}
char** menu_creating(int* height, int* width) {
    char** menu = new char* [*height];
    for (int i = 0; i < *height; i++)
        menu[i] = new char[*width];
    for (int i = 0; i < *height; i++)
        for (int j = 0; j < *width; j++)
            menu[i][j] = ' ';
    return menu;
}
void menu_moving(char* choose1) {
    if (*choose1 == 72) {
        if (number_of_focused_option > 0)
            number_of_focused_option--;
        else if (number_of_focused_option == 0)
            number_of_focused_option = number_of_options;
    }//стрілка вверх    
    else if (*choose1 == 80) {
        if (number_of_focused_option < number_of_options)
            number_of_focused_option++;
        else if (number_of_focused_option == number_of_options)
            number_of_focused_option = 0;
    }//стрілка вниз
}
void option_menu_moving(char* choose1) {
    if (*choose1 == 72) {
        if (number_of_focused_option > 0) {
            number_of_focused_option = number_of_focused_option - 2;
        }
        else if (number_of_focused_option < 2) {
            number_of_focused_option = number_of_focused_option + 2;
        }//стрілка вверх    
    }
    else if (*choose1 == 80) {
        if (number_of_focused_option < number_of_options) {
            number_of_focused_option = number_of_focused_option + 2;
        }
        else if (number_of_focused_option > 2) {
            number_of_focused_option = number_of_focused_option - 2;
        }
    }//стрілка вниз
    else if (*choose1 == 75) {
        if (number_of_focused_option > 0) {
            number_of_focused_option--;
        }
        else if (number_of_focused_option == 0) {
            number_of_focused_option = number_of_options;
        }
    }//стрілка вліво  
    else if (*choose1 == 77) {
        if (number_of_focused_option < number_of_options) {
            number_of_focused_option++;
        }
        else if (number_of_focused_option == number_of_options) {
            number_of_focused_option = 0;
        }
    }//стрілка вправо
}
void clear_focus(char** menu1_2, int width) {
    if (number_of_focused_option == 0)
        for (int i = 0; i < width; i++) {
            menu1_2[0][i] = ' ';
            for (int i = 0; i < width; i++)menu1_2[2][i] = ' ';
            menu1_2[1][0] = ' ';
            menu1_2[1][(width - 1)] = ' ';
        }
    else if (number_of_focused_option == 1) {
        for (int i = 0; i < width; i++)menu1_2[4][i] = ' ';
        for (int i = 0; i < width; i++)menu1_2[6][i] = ' ';
        menu1_2[5][0] = ' ';
        menu1_2[5][(width - 1)] = ' ';
    }
    else if (number_of_focused_option == 2) {
        for (int i = 0; i < 12; i++)menu1_2[8][i] = ' ';
        for (int i = 0; i < 12; i++)menu1_2[10][i] = ' ';
        menu1_2[9][0] = ' ';
        menu1_2[9][11] = ' ';
    }
}
void option_clear_focus(char** menu1_2) {
    if (number_of_focused_option == 0) {
        for (int i = 0; i <= 21; i++)menu1_2[0][i] = ' ';
        for (int i = 0; i <= 21; i++)menu1_2[2][i] = ' ';
        menu1_2[1][0] = ' ';
        menu1_2[1][20] = ' ';
    }
    else if (number_of_focused_option == 1) {
        for (int i = 22; i <= 43; i++)menu1_2[0][i] = ' ';
        for (int i = 22; i <= 43; i++)menu1_2[2][i] = ' ';
        menu1_2[1][22] = ' ';
        menu1_2[1][42] = ' ';
    }
    else if (number_of_focused_option == 2) {
        for (int i = 0; i <= 21; i++)menu1_2[4][i] = ' ';
        for (int i = 0; i <= 21; i++)menu1_2[6][i] = ' ';
        menu1_2[5][0] = ' ';
        menu1_2[5][20] = ' ';
    }
    else if (number_of_focused_option == 3) {
        for (int i = 22; i <= 43; i++)menu1_2[4][i] = ' ';
        for (int i = 22; i <= 43; i++)menu1_2[6][i] = ' ';
        menu1_2[5][22] = ' ';
        menu1_2[5][42] = ' ';
    }
    else if (number_of_focused_option == 4) {
        for (int i = 0; i <= 21; i++)menu1_2[8][i] = ' ';
        for (int i = 0; i <= 21; i++)menu1_2[10][i] = ' ';
        menu1_2[9][0] = ' ';
        menu1_2[9][20] = ' ';
    }
    else if (number_of_focused_option == 5) {
        for (int i = 22; i <= 43; i++)menu1_2[8][i] = ' ';
        for (int i = 22; i <= 43; i++)menu1_2[10][i] = ' ';
        menu1_2[9][22] = ' ';
        menu1_2[9][42] = ' ';
    }
    else if (number_of_focused_option == 6) {
        for (int i = 22; i <= 43; i++)menu1_2[12][i] = ' ';
        for (int i = 22; i <= 43; i++)menu1_2[14][i] = ' ';
        menu1_2[13][16] = ' ';
        menu1_2[13][20] = ' ';
    }

}
void start_focused(char** menu1_1, int height1_1, int width1_1) {
    system("cls");
    number_of_focused_option = 0;
    for (int i = 0; i < width1_1; i++)menu1_1[0][i] = '-';
    for (int i = 0; i < width1_1; i++)menu1_1[2][i] = '-';
    menu1_1[1][0] = '|';
    menu1_1[1][(width1_1 - 1)] = '|';
    print_menu(menu1_1, &height1_1, &width1_1);
    clear_focus(menu1_1, width1_1);
}
void option_focused(char** menu1_1, int height1_1, int width1_1) {
    system("cls");
    number_of_focused_option = 1;
    for (int i = 0; i < width1_1; i++)menu1_1[4][i] = '-';
    for (int i = 0; i < width1_1; i++)menu1_1[6][i] = '-';
    menu1_1[5][0] = '|';
    menu1_1[5][(width1_1 - 1)] = '|';
    print_menu(menu1_1, &height1_1, &width1_1);
    clear_focus(menu1_1, width1_1);
}
void exit_focused(char** menu1_1, int height1_1, int width1_1) {
    system("cls");
    number_of_focused_option = 2;
    for (int i = 0; i < width1_1; i++)menu1_1[8][i] = '-';
    for (int i = 0; i < width1_1; i++)menu1_1[10][i] = '-';
    menu1_1[9][0] = '|';
    menu1_1[9][(width1_1 - 1)] = '|';
    print_menu(menu1_1, &height1_1, &width1_1);
    clear_focus(menu1_1, width1_1);
}
void Number_of_coins_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 0;
    for (int i = 0; i < 21; i++)menu1_2[0][i] = '-';
    for (int i = 0; i < 21; i++)menu1_2[2][i] = '-';
    menu1_2[1][0] = '|';
    menu1_2[1][20] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Number_of_levels_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 1;
    for (int i = 22; i < 43; i++)menu1_2[0][i] = '-';
    for (int i = 22; i < 43; i++)menu1_2[2][i] = '-';
    menu1_2[1][22] = '|';
    menu1_2[1][42] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Size_of_map_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 2;
    for (int i = 0; i < 21; i++)menu1_2[4][i] = '-';
    for (int i = 0; i < 21; i++)menu1_2[6][i] = '-';
    menu1_2[5][0] = '|';
    menu1_2[5][20] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Random_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 3;
    for (int i = 22; i < 43; i++)menu1_2[4][i] = '-';
    for (int i = 22; i < 43; i++)menu1_2[6][i] = '-';
    menu1_2[5][22] = '|';
    menu1_2[5][42] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Multi_form_map_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 4;
    for (int i = 0; i < 21; i++)menu1_2[8][i] = '-';
    for (int i = 0; i < 21; i++)menu1_2[10][i] = '-';
    menu1_2[9][0] = '|';
    menu1_2[9][20] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Difficulty_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 5;
    for (int i = 22; i < 43; i++)menu1_2[8][i] = '-';
    for (int i = 22; i < 43; i++)menu1_2[10][i] = '-';
    menu1_2[9][22] = '|';
    menu1_2[9][42] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
void Back_focused(char** menu1_2, int height, int width) {
    system("cls");
    number_of_focused_option = 6;
    for (int i = 22; i < 43; i++)menu1_2[12][i] = '-';
    for (int i = 22; i < 43; i++)menu1_2[14][i] = '-';
    menu1_2[13][16] = '|';
    menu1_2[13][20] = '|';
    print_menu(menu1_2, &height, &width);
    option_clear_focus(menu1_2);
}
char option_box_with_choose(char* choose, char** menu1_1, int height, int width) {
    do {
        if (number_of_focused_option == 0) {
            Number_of_coins_focused(menu1_1, height, width);
            cout << "Number of coins is:" << amount_of_coins;
        }
        else if (number_of_focused_option == 1) {
            Number_of_levels_focused(menu1_1, height, width);
            cout << "Number of levels is:" << number_of_levels;
        }
        else if (number_of_focused_option == 2) {
            Size_of_map_focused(menu1_1, height, width);
            cout << "Size of map is:" << size_of_map1_0;
        }
        else if (number_of_focused_option == 3) {
            Random_focused(menu1_1, height, width);
            if (Rand_om == 1) cout << "Random is applied";
            else if (Rand_om == 0) cout << "Random is excluded";
        }
        else if (number_of_focused_option == 4) {
            Multi_form_map_focused(menu1_1, height, width);
            if (multi_form_map == 1)cout << "Multi form map is applied";
            if (multi_form_map == 0)cout << "Multi form map is excluded";

        }
        else if (number_of_focused_option == 5) {
            Difficulty_focused(menu1_1, height, width);
            if (Rand_om == 0) cout << "Casual";
            else if (Rand_om == 1) cout << "Easy";
            else if (Rand_om == 2) cout << "Medium";
            else if (Rand_om == 3) cout << "Hard";
            else if (Rand_om == 4) cout << "Nightmare";
        }
        else if (number_of_focused_option == 6) {
            Back_focused(menu1_1, height, width);
        }
        *choose = _getch();
        *choose = _getch();
        option_menu_moving(choose);
    } while ((*choose != 27) && ((*choose != 13) && (number_of_focused_option != 6)));
    return *choose = 27;
}
void put_number_of_coins_yourself() {
    do {
        cin >> amount_of_coins;
        if (amount_of_coins < 0) {
            cout << "Please, enter a number from 0 " << endl;
        }
    } while (amount_of_coins < 0);
}
void put_number_of_levels_yourself() {
    do {
        cin >> number_of_levels;
        if (number_of_levels < 0) {
            cout << "Please, enter a number from 0 " << endl;
        }
    } while (amount_of_coins < 0);
}
void main_box_with_choose(char* choose, char** menu1, int height, int width) {
    do {
        if (number_of_focused_option == 0) {
            start_focused(menu1, height, width);
        }
        if (number_of_focused_option == 1) {
            option_focused(menu1, height, width);
        }
        if (number_of_focused_option == 2) {
            exit_focused(menu1, height, width);
        }
        *choose = _getch();
        if (*choose == 224) *choose = _getch();
        menu_moving(choose);
    } while (((*choose) != 27) && (*choose != 13));
}
//!!!
char Enter_values_yourself(char choose, int size_of_map1_2, bool Rand_om) {
    //    int y = 0;
    //    if (choose == 27) return choose;
    //    ofstream Data("data.txt");
    //    data.open("data\\data.txt", ios::out| ios::binary) ;
    //    
    //    if (number_of_focused_option == 0) {
    //        put_number_of_coins_yourself();
    //        data.seekp(17);
    //        put();
    //    }
    //    else if (number_of_focused_option == 1) {
    //        put_number_of_levels_yourself();
    //        data.setCoins(number_of_coins);
    //        data.setLevels(number_of_levels);
    //        // fscanf(data, "Number of coins: %d\n", &number_of_coins);
    //        // fprintf(data, "Number of levels : %d", number_of_levels);
    //    }
    //    else if (number_of_focused_option == 2) {
    //        size_of_map1_0 = entered_size_of_map();
    //        data.setCoins(number_of_coins);
    //        data.setLevels(number_of_levels);
    //        data.setMapSize(size_of_map1_0);
    //        // fscanf(data, "Number of coins: %d\nNumber of levels : %d\n", &number_of_coins, &number_of_levels);
    //        // fprintf(data, "Size of map : %d", size_of_map1_0);
    //    }
    //    else if (number_of_focused_option == 3) {
    //        Rand_om = !Rand_om;
    //        data.setRandom(Rand_om);
    //    }
    //    data.save();
    //    out_data();
    return '\0';
}
//!!!
char option_menu() {
    number_of_options = 6;
    char choose;
    int height = 14, width = 43;/*34 знаки, 4 пропуски по 2 після кожної строки та рамка 4 по 2  та 1 пропуск між рамками*/
    char** menu1_1 = menu_creating(&height, &width);
    put_the_text_in_option_menu(height, width, menu1_1);
    choose = option_box_with_choose(&choose, menu1_1, height, width);
    if (choose == 27) {
        system("cls");
        number_of_focused_option = 0;
        return choose;
    }
    choose = Enter_values_yourself(choose, size_of_map1_0, Rand_om);
    delete[] menu1_1;
    number_of_focused_option = 0;
    option_menu();
}
void start_menu(int y) {
    number_of_options = 2;
    int height = 11, width = 12;
    char choose1;
    char** menu = menu_creating(&height, &width);
    string
        text0 = { "Start game" },
        text1 = { "Options" },
        text2 = { "Exit" };
    y = 1;
    center_the_text(menu, &text0, height, width, y);
    y = 5;
    center_the_text(menu, &text1, height, width, y);
    y = 9;
    center_the_text(menu, &text2, height, width, y);
    y++;
    print_menu(menu, &height, &width);
    main_box_with_choose(&choose1, menu, height, width);
    char** map1_2 = fulfill_map();
    if ((number_of_focused_option == 0) && (Rand_om == true)) {
        srand(time(NULL));
        size_of_map1_0 = 7 + rand() % 10;
        if (size_of_map1_0 % 2 == 0) size_of_map1_0++;
        number_of_coins = 1 + rand() % 15;
        put_rand_coins(map1_2);
    }
    if (choose1 == 27) exit(0);
    else if (number_of_focused_option == 1) {
        number_of_focused_option = 0;
        choose1 = option_menu();
        if (choose1 == 27) start_menu(0);
    }
    else if (number_of_focused_option == 2) exit(0);
    delete[] menu;
    number_of_focused_option = 0;
}
void choice_in_the_end(char** menu1, int height, int width) {
    number_of_options = 1;
    int y = 0;
    char choose;
    string text1_2 = { "Yes?" }, text2_2 = { "No?" };
    y = 1;//перша строка між лініями фокусу
    center_the_text(menu1, &text1_2, height, width, y);
    y = 5;//друга строка між лініями фокусу
    center_the_text(menu1, &text2_2, height, width, y);
    print_menu(menu1, &height, &width);
    main_box_with_choose(&choose, menu1, height, width);
    if (choose == 27) exit(0);
    if (number_of_focused_option == 1) exit(0);
    delete[] menu1;
}
void end_game_menu(string congratulations) {
    int height = 11, width = 12;
    int y = 5;
    char** menu = menu_creating(&height, &width);
    clean_array(menu, height, width);
    system("cls");
    center_the_text(menu, &congratulations, height, width, y);
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 12; j++) {
            cout << menu[i][j];
        }
        cout << endl;
    };
    system("pause");//Очікування команди гравця.
    clean_array(menu, height, width);
    system("cls");
    cout << "Play again?" << endl;
    choice_in_the_end(menu, height, width);
}
void perevirkaMonet(char** map1_4, int size_of_map1_3) {
    number_of_coins = 0;
    for (int i = 0; i < size_of_map1_3; i++) {
        for (int j = 0; j < size_of_map1_3; j++) {
            if (map1_4[i][j] == '0') {
                number_of_coins++;
            }
        }
    }
}
void printMap(char** map1_3)
{
    system("cls");// очистити консоль
    perevirkaMonet(map1_3, size_of_map1_0);// перевірка кількості монет в матриці
    for (int y = 0; y < size_of_map1_0; y++) {
        for (int x = 0; x < size_of_map1_0; x++) {
            if (map1_3[y][x] == '#')
            {
                SetColor(15, 15);
                // встановлюємо "пензлик" білого кольору тексту та білого кольору фон
            }
            else if (map1_3[y][x] == ' ')
            {
                SetColor(0, 0);
                // встановлюємо "пензлик" чорного кольору тексту та чорного кольору фон
            }
            else if (map1_3[y][x] == '0')
            {
                SetColor(2, 0);
                // встановлюємо "пензлик" зеленого кольору тексту та чорного кольору фон
            }
            else if (map1_3[y][x] == '@')
            {
                SetColor(4, 0);
                // встановлюємо "пензлик" червоного кольору тексту та чорного кольору фон
            }
            else if (map1_3[y][x] == 'N') {
                SetColor(3, 0);
            }
            else if (map1_3[y][x] == 'l')
            {
                SetColor(4, 0);
                // встановлюємо "пензлик" червоного кольору тексту та білого кольору фон
            }
            cout << map1_3[y][x];
        }
        SetColor(0, 0);
        // встановлюємо "пензлик" чорного кольору тексту та чорного кольору фон
        cout << endl;
    }
    cout << "Monet zalishilosya:" << number_of_coins << endl;
}
void beautiful_walls(char** map1_2, int x, int y, int size_of_map, int min_x, int min_y, int max_x, int max_y) {
    int k = 0;
    int diagonal_x = x;
    if (x > size_of_map)
        diagonal_x = x - size_of_map;
    int diagonal = 0;
    for (bool until_wall_meet_end = true; until_wall_meet_end; diagonal_x = x, diagonal = (size_of_map - 1) - diagonal_x)
    {
        if (k % 4 == 0) {
            if (((y + 2) < (max_x - 1)) && ((y + 2)) == x) { // виконання ітерацій до тих пір поки ячейка не дійде до правого нижнього кута
                k++; y--;
            }
            else if (x < (max_x - 1)) {
                x++;
                map1_2[y][x] = '#';
            }
            else if (x == (max_x - 1)) until_wall_meet_end = false;
        }
        else if (k % 4 == 1) {
            if (y == diagonal) { // Виконання ітерацій до тих пір поки ячейка не дійде до правого верхнього кута
                k++;
            }
            else if ((y - 1) > min_y)  y--;
            else if ((y - 1) == min_y)  until_wall_meet_end = false;
            map1_2[y][x] = '#';
        }
        else if (k % 4 == 2) {
            if (y == x) // Виконання ітерацій до тих пір поки ячейка не дійде до лівого верхнього кута
                k++;
            else if ((y != x) && ((x - 1) > min_x)) x--;
            else if ((y != x) && ((x - 1) < min_x)) until_wall_meet_end = false;
            map1_2[y][x] = '#';
        }
        else if (k % 4 == 3) {
            if (y == diagonal) // Виконання ітерацій до тих пір поки ячейка не дійде до лівого нижнього кута
                k++;
            else if ((y != diagonal) && ((y + 1) < max_y))y++;
            else if ((y + 1) == (max_y - 1)) until_wall_meet_end = false;
            map1_2[y][x] = '#';
        }
    }
}
void divided_map(char** map1_2) {
    int half_of_the_map = (size_of_map1_0 - 1) / 2;
    int min_of_x = 0;
    int min_of_y = 0;
    int max_of_x = 0;
    int max_of_y = 0;
    int x = 0, y = 0;
    x = half_of_the_map / 2;
    y = x;
    max_of_y = half_of_the_map;
    max_of_x = max_of_y;
    beautiful_walls(map1_2, x, y, half_of_the_map, min_of_x, min_of_y, max_of_x, max_of_y);
    y = half_of_the_map + x;
    min_of_x = 0;
    min_of_y = max_of_y;
    max_of_y = (size_of_map1_0 - 1);
    beautiful_walls(map1_2, x, y, half_of_the_map, min_of_x, min_of_y, max_of_x, max_of_y);
    x = y;
    min_of_x = min_of_y;
    max_of_x = max_of_y;
    beautiful_walls(map1_2, x, y, half_of_the_map, min_of_x, min_of_y, max_of_x, max_of_y);
    y = (half_of_the_map - 1) / 2;
    min_of_y = 0;
    max_of_y = half_of_the_map;
    beautiful_walls(map1_2, x, y, half_of_the_map, min_of_x, min_of_y, max_of_x, max_of_y);
    system("cls");
    printMap(map1_2);
}
void setPositionPacmen(char** map1_2) {
    map1_2[Y_old][X_old] = ' ';
    map1_2[Y_new][X_new] = '@';
    Y_old = Y_new;
    X_old = X_new;
    printMap(map1_2);
}
int movePacmenUp(char** map1_2) {
    if (((Y_new - 1) >= 0) && (map1_2[Y_new - 1][X_new] != '#')) {
        Y_new = Y_new - 1;
        if (map1_2[Y_new][X_new] == 'N') return Y_new;
        setPositionPacmen(map1_2);
    }
    else {
        cout << "Can't go up" << endl;
    }
}
int movePacmenDown(char** map1_2) {
    if (((Y_new + 1) <= (size_of_map1_0 - 1)) && (map1_2[Y_new + 1][X_new] != '#')) {
        Y_new = Y_new + 1;
        if (map1_2[Y_new][X_new] == 'N') return Y_new;
        setPositionPacmen(map1_2);
    }
    else {
        cout << "Nevdacha hodu Down" << endl;
    }
}
int movePacmenRight(char** map1_2) {
    if ((map1_2[Y_new][X_new + 1] != '#') && ((X_new + 1) <= (size_of_map1_0 - 1))) {
        X_new = X_new + 1;
        if (map1_2[Y_new][X_new] == 'N') return X_new;
        setPositionPacmen(map1_2);
    }
    else {
        cout << "Nevdacha hodu Right" << endl;
    }
}
int movePacmenLeft(char** map1_2) {
    if ((map1_2[Y_new][X_new - 1] != '#') && ((X_new - 1) >= 0)) {
        X_new = X_new - 1;
        if (map1_2[Y_new][X_new] == 'N') return X_new;
        setPositionPacmen(map1_2);
    }
    else {
        cout << "Nevdacha hodu Left" << endl;
    }
}
void getUserKeyNumber() {
    userNumber = _getch();// зчитування алфавітної клавіатури
    if (userNumber == 224) {// "костиль" для зчитування стрілочок
        userNumber = _getch();
    }
}
void move_pacman(char** map1_1) {
    getUserKeyNumber();
    if (userNumber == 72) {//стрілочка вверх
        movePacmenUp(map1_1);
    }
    else if (userNumber == 80) {//стрілочка вниз
        movePacmenDown(map1_1);
    }
    else if (userNumber == 75) {//стрілочка ліворуч
        movePacmenLeft(map1_1);
    }
    else if (userNumber == 77) {//стрілочка праворуч
        movePacmenRight(map1_1);
    }
}
void put_portal_to_next_level(char** map1_3) {
    srand(time(NULL));
    bool until_be_put = true;
    int rand_y = 0;
    int rand_x = 0;
    while (until_be_put) {
        rand_y = rand() % (size_of_map1_0);
        rand_x = rand() % (size_of_map1_0);
        if ((map1_3[rand_y][rand_x] != '#') && (map1_3[rand_y][rand_x] != '@') && (map1_3[rand_y][rand_x] != '0')) {
            map1_3[rand_y][rand_x] = 'N';
            number_of_levels--;
            until_be_put = false;
        };
    }
    printMap(map1_3);
}
int vector_of_vision(int vis_x, int vis_y) {
    int vector = 0;
    if (vis_x == 1) vector = 0;//рух вправо
    else if (vis_x == -1) vector = 1;//рух вліво
    else if (vis_y == 1) vector = 2;//рух вниз
    else if (vis_y == -1) vector = 3;//рух вверх
    return vector;
}
int area_of_visibility_check(int area_of_visibility, int vector, int y, int x, int length_of_chase, char** map) {
    for (int i = 0; i < area_of_visibility; i++) {
        if (vector == 0)
            if (map[y + i][x] == '@')
                length_of_chase = i;
            else if (vector == 1)
                if (map[y - i][x] == '@')
                    length_of_chase = i;
                else if (vector == 2)
                    if (map[y][x + i] == '@')
                        length_of_chase = i;
                    else if (vector == 3)
                        if (map[y][x - i] == '@')
                            length_of_chase = i;
    }
    return length_of_chase;
}
void check_up_and_down(int y, int x, int vector, int length_of_chase, int area_of_visibility, char** map, bool enemy_is_alarm_on) {
    vector = 2 + rand() % 3;
    length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
    if ((vector == 2) && (length_of_chase == 0)) {
        vector = 3;
        length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
        if (length_of_chase == 0) enemy_is_alarm_on = false;
    }
    else if ((vector == 3) && (length_of_chase == 0)) {
        vector = 2;
        length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
        if (length_of_chase == 0) enemy_is_alarm_on = false;
    }
}
void check_left_and_right(int y, int x, int vector, int length_of_chase, int area_of_visibility,
    char** map, bool enemy_is_alarm_on) {
    vector = rand() % 1;
    length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
    if ((vector == 0) && (length_of_chase == 0)) {
        vector = 1;
        length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
        if (length_of_chase == 0) enemy_is_alarm_on = false;
    }
    else if ((vector == 1) && (length_of_chase == 0)) {
        vector = 0;
        length_of_chase = area_of_visibility_check(area_of_visibility, vector, y, x, length_of_chase, map);
        if (length_of_chase == 0) enemy_is_alarm_on = false;
    }
}
int detour_by_enemy(int x, int y, int vector, char** map) {
    if ((map[y + 1][x + 1] == '@') || (map[y + 1][x - 1] == '@')) {
        if (map[y + 1][x] == ' ') {
            vector = 2;
            if (map[y][x + 1] == ' ') {
                vector = rand() % 1;//якщо число дорівнює 0, то ворог йде вправо, якщо ні, то ворог йде вниз
                if (vector == 1) vector = 2;
            }
            else if (map[y][x - 1] == ' ') {
                vector = rand() % 1;//якщо число дорівнює 1, то ворог йде вліво, якщо ні, то ворог йде вниз
                if (vector == 0) vector = 2;
            }
        }
    }
    else if ((map[y - 1][x - 1] == '@') || (map[y - 1][x + 1] == '@')) {
        if (map[y - 1][x] == ' ') {
            vector = 3;
            if (map[y][x - 1] == ' ') {
                vector = rand() % 1;//якщо число дорівнює 1, то ворог йде вліво, якщо ні, то ворог йде вверх
                if (vector == 0) vector = 3;
            }
            else if (map[y][x + 1] == ' ') {
                vector = rand() % 1;//якщо число дорівнює 0, то ворог йде вправо, якщо ні, то ворог йде вверх
                if (vector == 1) vector = 3;
            }
        }
    }
    return vector;
}
int testing_path(int vis_x, int vis_y, char** map, int x, int y, int length_of_path) {
    srand(time(NULL));
    length_of_path = 1 + rand() % (size_of_map1_0 - 2);
    int vector = vector_of_vision(vis_x, vis_y);
    for (int i = 0; i <= length_of_path; i++) {
        if (vector == 0) {
            if ((map[y][x+i] == '#')||((x + i) == size_of_map1_0)) length_of_path = i-1;
        }
        else if (vector == 1) {
            if (map[y][x-i] == '#') length_of_path = i-1;
            else if ((x - i) == 0) length_of_path = i;       
        }
        else if (vector == 2) {
            if ((map[y+i][x] == '#')||((y + i) == size_of_map1_0)) length_of_path = i - 1;       
        }
        else if (vector == 3) {
            if (map[y-i][x] == '#') length_of_path = i - 1;
            else if((y - i) == 0)length_of_path = i;
        }
    }
    return length_of_path;
}
bool enemy_is_alarm(int x, int y, int vector, int length_of_chase, int area_of_visibility,
    char** map, bool enemy_is_alarm_on) {
    for (int i = 0; i < area_of_visibility; i++) testing_path(vis_x, vis_y, map, x, y, length_of_chase);
    if(//обхід
        ((map[y][x+1]=='#')||//якщо справа є стіна
        (map[y][x-1]=='#'))&&//або зліва є стіна
       ((map[y-1][x]==' ')||//та зверху
        (map[y+1][x]==' '))||//або знизу є прохід
       ((map[y-1][x]=='#')||//або: зверху є стіна
        (map[y+1][x]=='#'))&&//чи знизу є стіна
        (map[y][x-1]==' ')||//та зліва
        (map[y][x+1]==' ')//або зправа є прохід
       )
    {
        if ((vector == 0) || (vector == 1)) {
            if (((map[y + 1][x]) == ' ')) { //якщо ворог рухається вправо або вліво, та знизу є прохід
                vector = 2;
                if (map[y - 1][x] == ' ')//якщо є прохід ще й зверху
                    check_up_and_down(y, x, vector, length_of_chase, area_of_visibility, map, enemy_is_alarm_on);
            }
            else if ((map[y - 1][x]) == ' ') { vector = 3; }//якщо є прохід тільки зверху
        }   
        else if ((vector == 2) || (vector == 3)) {//якщо ворог рухається вниз або вверх
            if ((map[y][x + 1]) == ' ') {//та справа є прохід
                vector = 0;
                if (map[y][x - 1] == ' ') {//або ще й зліва є прохід
                    check_left_and_right(y, x, vector, length_of_chase, area_of_visibility, map, enemy_is_alarm_on);
                }
            }
            else if((map[y][x - 1]) == ' ') {vector = 1;}//та є прохід тільки зліва
        }
    }
}
void moving_enemies(int vector, char** map, int &x, int &y, int step) {
        if (vector == 0)
    {
        map[y][x] = ' ';
        map[y][x+step] = 'l';
        x += step;
        printMap(map);
    }
    else if (vector == 1) {
        map[y][x] = ' ';
        map[y][x-step] = 'l';
        x -=step;
        printMap(map);
    }
    else if (vector == 2) {
        map[y][x] = ' ';
        map[y+step][x] = 'l';
        y +=step;
        printMap(map);
    }
    else if (vector == 3) {
        map[y][x] = ' ';
        map[y-step][x] = 'l';
        y -=  step;
        printMap(map);
    }
}
int chaotic_way(int x, int y, char** map) {
    bool filled_area = true;
    do {
        srand(time(NULL));
        vis_x = (rand() % 3) - 1;
        //якщо число буде націло кратне 3, то остача буде 0, якщо 2 то віднявши одиницю--1
        vis_y = (rand() % 3) - 1;
        
        if (((abs(vis_y) == 1) != (abs(vis_x) == 1)) &&
            /*Напрямок не приймає діагональних значень,
            або виходячих за рамки і ще якщо є стінка*/
            (((y + vis_y) <= (size_of_map1_0 - 1)) && 
             ((x + vis_x) <= (size_of_map1_0 - 1)))&&
            (((y + vis_y) >= 0) && 
             ((x + vis_x) >= 0))&&
            ((map[vis_y+y][x]!='#') && //напрямок не збігається з стінкою.
            (map[y][vis_x+x] != '#'))) {
            filled_area = false;
        }
    } while (filled_area);

    int length_of_path = 0;
    length_of_path = testing_path(vis_x, vis_y, map, x, y, length_of_path);
    return length_of_path;
}   
void enemy_feel_player_passing_by(char** map1, int  y, int x, bool more_sensitive_enemy, int vector, char** map, bool game_over) {
    if (more_sensitive_enemy == true) {
        if (map[y + 1][x] == '@') game_over = true;
        else if (map[y][x + 1] == '@') game_over = true;
        else if (map[y - 1][x] == '@') game_over = true;
        else if (map[y][x - 1] == '@')game_over = true;
        detour_by_enemy(x, y, vector, map);
    }
}
int enemies(int& length_of_path, int area_of_visibility, bool& calm, int& x, int& y, int step,
    char** map, bool more_harder_enemy, bool& game_over) {
    if (calm) {
        length_of_path = chaotic_way(x, y, map);
        calm = false;
    }
    int vector = vector_of_vision(vis_x, vis_y);
    if (more_harder_enemy == true) enemy_feel_player_passing_by(map, y, x, more_harder_enemy, vector, map, game_over);
    if (enemy_is_alarm_on) enemy_is_alarm();
    if (length_of_path != 0){
    moving_enemies(vector, map, x, y, step);
    length_of_path--;
    }
    else if (length_of_path == 0){
        calm = true;
    }

    return length_of_path;
}
int difficulty_of_game(bool more_harder_enemy) {
    int area_of_visibility = 0;
    if (difficulty == 1) area_of_visibility = 4;
    else if (difficulty == 2) area_of_visibility = 8;
    else if (difficulty == 3) area_of_visibility = size_of_map1_0;
    else if (difficulty == 4) {
        area_of_visibility = size_of_map1_0;
        more_harder_enemy = true;
    }
    return area_of_visibility;
}
void enemy1(int area_of_visibility, int& length_of_path, bool& calm, int& x, int& y, int step,
    char** map, bool more_harder_enemy, bool& game_over) {
    length_of_path = enemies(length_of_path, area_of_visibility, calm, x, y, step, map, more_harder_enemy, game_over);
}
void enemy2(int area_of_visibility, int& length_of_path, bool& calm, int& x, int& y, int step,
    char** map, bool more_harder_enemy, bool game_over) {
    length_of_path = enemies(length_of_path, area_of_visibility, calm, x, y, step, map, more_harder_enemy, game_over);
    printMap(map);
}
void enemy_spawn(int& x_enemy, int& y_enemy, char** map, bool& filled_place, bool& no_enemies) {
    bool dont_spawn = false;
    if (difficulty == 0) no_enemies = true;
    if (no_enemies == false) {
        do {
            srand(time(NULL));
            x_enemy = rand() % (size_of_map1_0 - 1);
            y_enemy = rand() % (size_of_map1_0 - 1);
            if ((map[y_enemy][x_enemy] != '#') && (map[y_enemy][x_enemy] != '@') && (map[y_enemy][x_enemy] != '0')) {
                if ((x_enemy > 4) && (y_enemy > 4))
                    filled_place = false;
            }
        } while (filled_place);
        map[y_enemy][x_enemy] = 'l';
        printMap(map);
    }
}
void making_map(char** map1_1, int y) {
    if (multi_form_map == true)
        divided_map(map1_1);
    else beautiful_walls(map1_1, (size_of_map1_0 - 1) / 2, (size_of_map1_0 - 1) / 2, size_of_map1_0, 0, 0, size_of_map1_0, size_of_map1_0);
    put_rand_coins(map1_1);
    setPositionPacmen(map1_1);
}
void all_coins_collected(char** map1_1) {
    string congratulations = "You won";
    if (number_of_coins == 0) {
        put_portal_to_next_level(map1_1);
        while ((userNumber != 27) && (map1_1[Y_new][X_new] != 'N')) {
            move_pacman(map1_1);
        }
    }
    delete[]map1_1;
    if (number_of_levels == 0) {
        end_game_menu(congratulations);
        out_data();
    }
    X_old = 0; Y_old = 0;
    X_new = 0; Y_new = 0;
}
void Game_over(bool game_over, char** map1_1) {
    if (game_over == true) {
        string sad_text = "Game over!";
        delete[]map1_1;
        end_game_menu(sad_text);
        out_data();
        X_old = 0; Y_old = 0;
        X_new = 0; Y_new = 0;
    }
}
void main() {
    int y = 0;//координата строки
    bool no_enemies = false;
    bool game_over = false;
    int step = 1;
    bool more_harder_enemy = false;
    int area_of_visibility = difficulty_of_game(more_harder_enemy);
    if (more_harder_enemy == true) step = 3;
    bool enemy_is_alarm_on = false;
    int enemy1_length_of_path = 0;
    //int enemy2_length_of_path = 0;
    bool calm = true;
    bool filled_place = true;
    out_data();
    char** map1_1 = fulfill_map();
    start_menu(y);
    making_map(map1_1, y);
    int enemy1_x = 0;
    int enemy1_y = 0;
    //int enemy2_x = 0;
    //int enemy2_y = 0;
    enemy_spawn(enemy1_x, enemy1_y, map1_1, filled_place, no_enemies);
    //enemy_spawn(enemy2_x, enemy2_y, map1_1, filled_place, no_enemies);
    while (true) {
        while ((userNumber != 27) && (number_of_coins != 0)) {
            move_pacman(map1_1);
            enemy1(area_of_visibility, enemy1_length_of_path, calm, enemy1_x, enemy1_y, step, map1_1, more_harder_enemy, game_over);
            //   enemy2(area_of_visibility, enemy2_length_of_path, calm, enemy2_x, enemy2_y, step, map1_1, more_harder_enemy, game_over);
            if (game_over == true) userNumber = 27;
        }
        Game_over(game_over, map1_1);
        all_coins_collected(map1_1);
    }
}