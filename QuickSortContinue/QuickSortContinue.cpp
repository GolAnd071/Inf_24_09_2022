// QuickSortContinue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// crt_spawn.c
// This program accepts a number in the range
// 1-8 from the command line. Based on the number it receives,
// it executes one of the eight different procedures that
// spawn the process named child. For some of these procedures,
// the CHILD.EXE file must be in the same directory; for
// others, it only has to be in the same path.
//

#include <stdio.h>
#include <process.h>

const char* my_env[] =
{
   "THIS=environment will be",
   "PASSED=to child.exe by the",
   "_SPAWNLE=and",
   "_SPAWNLPE=and",
   "_SPAWNVE=and",
   "_SPAWNVPE=functions",
   NULL
};

int main(int argc, char* argv[])
{
    const char* args[4] = { "child", "spawn??", "two", NULL };

    /*
    // Set up parameters to be sent:
    args[0] = "child";
    args[1] = "spawn??";
    args[2] = "two";
    args[3] = NULL;
    */

    if (argc <= 2)
    {
        printf("SYNTAX: SPAWN <1-8> <childprogram>\n");
        exit(1);
    }

    switch (argv[1][0])   // Based on first letter of argument
    {
    case '1':
        _spawnl(_P_WAIT, argv[2], argv[2], "_spawnl", "two", NULL);
        break;
    case '2':
        _spawnle(_P_WAIT, argv[2], argv[2], "_spawnle", "two",
            NULL, my_env);
        break;
    case '3':
        _spawnlp(_P_WAIT, argv[2], argv[2], "_spawnlp", "two", NULL);
        break;
    case '4':
        _spawnlpe(_P_WAIT, argv[2], argv[2], "_spawnlpe", "two",
            NULL, my_env);
        break;
    case '5':
        _spawnv(_P_OVERLAY, argv[2], args);
        break;
    case '6':
        _spawnve(_P_OVERLAY, argv[2], args, my_env);
        break;
    case '7':
        _spawnvp(_P_OVERLAY, argv[2], args);
        break;
    case '8':
        _spawnvpe(_P_OVERLAY, argv[2], args, my_env);
        break;
    default:
        printf("SYNTAX: SPAWN <1-8> <childprogram>\n");
        exit(1);
    }
    printf("from SPAWN!\n");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
