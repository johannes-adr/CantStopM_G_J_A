#include "Testing.h"
#include "iostream"
#include "../Utils/Utils.h"
#include "optional"
#include "../CantStop/Game/Game.h"
#include "../CantStop/Player/Bot/SkippingBot.h"

#define OK(){return std::optional<std::string>();}
#define ASSERT_GEN(a, b,operator) {std::stringstream ss{};if(!(a operator b)){ss<<#a << " != " <<#b << "  {"<<a <<" != "<<b << "}" << " (Line "<<__LINE__<<")";return std::optional(ss.str());}}
#define ASSERT_FALSE(a,b) ASSERT_GEN(a,b,!=)
#define ASSERT(a,b) ASSERT_GEN(a,b,==)
TestResult TEST_Game_Load_Board() {
    auto game = Game();
    game.loadBoard("0,1.1,2 2,4.1,1");
    Column colCopy = game.getColumnsCopy()[1];

    Column expected = Column();
    expected.height = 4;
    expected.playerProgress[0] = {2,4};
    expected.playerProgress[1] = {1,1};

    ASSERT(expected.height, colCopy.height);
    ASSERT(expected.playerProgress[0], colCopy.playerProgress[0])
    ASSERT(expected.playerProgress[1], colCopy.playerProgress[1])
    ASSERT(expected, colCopy)

    OK()
}


TestResult TEST_Game_Update(){
    auto game = Game();
    auto player1 = SkippingBot();
    auto player2 = SkippingBot();
    auto* currentPlayer = &player1;
    game.setPlayer(&player1,&player2);
    for(int i = 0;i < 1000;i++){
        ASSERT(game.getCurrentPlayer(), currentPlayer);
        game.update();
        currentPlayer = currentPlayer==&player1?&player2:&player1;
    }
    OK()
}

TestResult TEST_Player_doMove(){
    static Array<Column, 11> columns_before_pass;
    class TestBot: public Bot{
        bool alreadyMoved = false;
        SelectedColumns selectColumns(DiceCombination &combs, Game &game) override{
            if(alreadyMoved){
                columns_before_pass = game.getColumnsCopy();
                return {};
            }
            alreadyMoved = true;
            Vec<int> v;
            v.push_back(2);
            v.push_back(3);
            v.push_back(4);
            return v;
        }
    };


    auto game = Game();
    auto expectedGame = Game();
    expectedGame.loadBoard("0,0.0,0 0,0.0,0 0,1.0,0 0,1.0,0"); //2 & 3 Col with 1 progress player 1 - no checkpoints
    auto player1 = TestBot();
    auto player2 = SkippingBot();
    game.setPlayer(&player1,&player2);
    ASSERT(game.getCurrentPlayer(), &player1);
    OK()
}

TestResult TEST_randomDice(){
    static DiceCombination dcombs;
    class TestBot: public Bot{
        bool alreadyMoved = false;
        SelectedColumns selectColumns(DiceCombination &combs, Game &game) override{
            dcombs = combs;
            return {};
        }
    };
    auto game = Game();
    auto tb1 = TestBot();
    auto tb2 = TestBot();
    game.setPlayer(&tb1,&tb2);

    int min = 100;
    int max = -100;
    for(int i = 0;i < 1000;i++){
        game.update();
        for(auto diceNum : dcombs.dices){
            if(diceNum<min)min=diceNum;
            if(diceNum>max)max=diceNum;
        }
    }
    ASSERT(min,1);
    ASSERT(max,6);
    OK();
}

TestResult TEST_VecContains(){
    Vec<int> i{};
    i.push_back(2);
    i.push_back(5);
    i.push_back(10);
    ASSERT(Utils::vecContains(i,2),true);
    ASSERT(Utils::vecContains(i,6),false);
    OK();
}


TestResult TEST_GameWinCondition(){
    auto p1 = SkippingBot();
    auto p2 = SkippingBot();
    {
        auto game = Game();
        game.setPlayer(&p1,&p2);
        game.loadBoard("2,2.0,0 4,4.0,0 6,6.0,0");
        ASSERT(game.update(),1);
    }

    {
        auto game = Game();
        game.setPlayer(&p1,&p2);
        game.loadBoard("0,0.2,2 0,0.4,4 0,0.6,6");
        ASSERT(game.update(),2);
    }

    {
        auto game = Game();
        game.setPlayer(&p1,&p2);
        game.loadBoard("2,2.0,0 4,4.0,0 5,5.0,0");
        ASSERT(game.update(),0);
    }
    OK();
}


Test::Test() {
    addTest("loadBoardFunction", TEST_Game_Load_Board);
    addTest("Gameupdate",TEST_Game_Update);
    addTest("Playermove (Progress / Checkpoint)",TEST_Player_doMove);
    addTest("RandomDiceGen",TEST_randomDice);
    addTest("VecContains", TEST_VecContains);
    addTest("WinCondition",TEST_GameWinCondition);
}

void Test::runTests() {
    for (auto& test: tests) {
        std::cout << "Running '" << test.first << "'... ";
        auto result = test.second();
        if(result.has_value()){
            std::cout << C_RED << "ERROR: " << C_RESET  << result.value()<< std::endl;
        }else{
            std::cout << C_BLUE << "OK" << C_RESET << std::endl;
        }
    }
}

void Test::addTest(const std::string& name, Func f) {
    tests[name] = std::move(f);
}