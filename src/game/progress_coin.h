#pragma once

#include <stdint.h>


class ProgressCoin {
public:
    ProgressCoin(uint32_t identification);

    void setVisible();
    void setTaken();
    bool isVisible() const;
    bool isTaken() const;

    void takeAction();

private:
    uint32_t ID;
    bool is_visible;
    bool is_taken;

/*
    void strategy();
    void law();
    void philosophy();
    void theology();
    void architecture();
    void masonry();
    void agriculture();
    void economy();
    void mathematics();
    void urbanism();
*/
};
