
// Generated by Maze_Lib_Test/GenTestList.ps1

typedef struct
{
    const char * mName;
    int (*mFunction)();
}
TestInfo;

extern int TestA_00();
extern int TestA_01();
extern int TestA_02();
extern int TestA_03();
extern int TestA_04();
extern int TestA_05();
extern int TestA_06();
extern int TestA_07();

static const TestInfo TESTS[] =
{
    { "TestA_00.cpp", TestA_00 },
    { "TestA_01.cpp", TestA_01 },
    { "TestA_02.cpp", TestA_02 },
    { "TestA_03.cpp", TestA_03 },
    { "TestA_04.cpp", TestA_04 },
    { "TestA_05.cpp", TestA_05 },
    { "TestA_06.cpp", TestA_06 },
    { "TestA_07.cpp", TestA_07 },
};

