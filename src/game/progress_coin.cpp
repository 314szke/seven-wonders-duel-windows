#include "progress_coin.h"


ProgressCoin::ProgressCoin(uint32_t identification) :
    ID(identification),
    is_visible(false),
    is_taken(false)
{}

void ProgressCoin::setVisible()
{
    is_visible = true;
}

void ProgressCoin::setTaken()
{
    is_taken = true;
}

bool ProgressCoin::isVisible() const
{
    return is_visible;
}

bool ProgressCoin::isTaken() const
{
    return is_taken;
}

void ProgressCoin::takeAction()
{

}
