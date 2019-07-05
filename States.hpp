#ifndef STATES_HPP
#define STATES_HPP

enum class State{
    Menu = 0,
    Settings = 1,
    Game = 2,
    Pause = 3
};

class GameState{
protected:
    void setState(State s) const;
    void setPreviousState() const;
    State getState() const;
    State getPreviousState() const;
    float getWindowWidth() const;
    float getWindowHeight() const;
};

#endif // !STATES_HPP