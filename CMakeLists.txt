cmake_minimum_required(VERSION 3.14)
project(cantstop2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp JdrSFML/GameWindow.cpp JdrSFML/GameWindow.h JdrSFML/IRenderable.cpp JdrSFML/IRenderable.h JdrSFML/SubCanvas/SubCanvas.cpp JdrSFML/SubCanvas/SubCanvas.h CantStop/Game/Game.cpp CantStop/Game/Game.h CantStop/Player/IPlayer.cpp CantStop/Player/IPlayer.h Utils/Utils.cpp Utils/Utils.h CantStop/Game/Dice.cpp CantStop/Game/Dice.h CantStop/Player/TerminalPlayer/TerminalPlayer.cpp CantStop/Player/TerminalPlayer/TerminalPlayer.h CantStop/Player/SFMLPlayer/SFMLPlayer.cpp CantStop/Player/SFMLPlayer/SFMLPlayer.h JdrSFML/JdrSFML.h CantStop/Player/SFMLPlayer/Graphics/GameBackground.cpp CantStop/Player/SFMLPlayer/Graphics/GameBackground.h CantStop/Player/SFMLPlayer/Graphics/RenderableBoardColumn.cpp CantStop/Player/SFMLPlayer/Graphics/RenderableBoardColumn.h CantStop/Player/SFMLPlayer/Graphics/ColorScheme.h JdrSFML/Button.cpp JdrSFML/Button.h JdrSFML/LambdaRenderable.cpp JdrSFML/LambdaRenderable.h CantStop/Player/SFMLPlayer/Graphics/OnTurnDisplay.cpp CantStop/Player/SFMLPlayer/Graphics/OnTurnDisplay.h CantStop/Player/SFMLPlayer/Graphics/RenderableDice.cpp CantStop/Player/SFMLPlayer/Graphics/RenderableDice.h CantStop/Player/Bot/SkippingBot.cpp CantStop/Player/Bot/SkippingBot.h CantStop/Player/Bot/Bot.cpp CantStop/Player/Bot/Bot.h JdrTest/Testing.h JdrTest/Testing.cpp Utils/JVec.h Definitions.h CantStop/Player/Bot/RandomBot.cpp CantStop/Player/Bot/RandomBot.h CantStop/Player/Bot/ScaryBot.cpp CantStop/Player/Bot/ScaryBot.h)
add_executable(cantstop2 ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(cantstop2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)