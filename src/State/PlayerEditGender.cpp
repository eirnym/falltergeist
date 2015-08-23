/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// Falltergeist includes
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Game/DudeObject.h"
#include "../State/PlayerEditGender.h"
#include "../UI/ImageList.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PlayerEditGender::PlayerEditGender() : State()
{
}

PlayerEditGender::~PlayerEditGender()
{
}

void PlayerEditGender::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    Point bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
    int bgX = bgPos.x();
    int bgY = bgPos.y();

    auto bg = new UI::Image("art/intrface/charwin.frm");
    bg->setX(bgX+236);
    bg->setY(bgY+0);

    _maleImage = new UI::ImageList((std::vector<std::string>){
                                    "art/intrface/maleoff.frm",
                                    "art/intrface/maleon.frm"
                                }, bgX+260, bgY+2);
    _maleImage->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onMaleButtonPress(dynamic_cast<Event::Mouse*>(event)); });

    _femaleImage = new UI::ImageList((std::vector<std::string>){
                                                            "art/intrface/femoff.frm",
                                                            "art/intrface/femon.frm"
                                                            }, bgX+310, bgY+2);
    _femaleImage->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onFemaleButtonPress(dynamic_cast<Event::Mouse*>(event)); });

    auto doneBox = new UI::Image("art/intrface/donebox.frm");
    doneBox->setX(bgX+250);
    doneBox->setY(bgY+42);

    auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+281, bgY+45);
    auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf", 0xb89c28ff);
    doneLabel->setFont(font3_b89c28ff);

    auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+260, bgY+45);
    doneButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onDoneButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    addUI(bg);
    addUI(doneBox);
    addUI(doneButton);
    addUI(doneLabel);
    addUI(_maleImage);
    addUI(_femaleImage);
    setGender(Game::getInstance()->player()->gender());
}

void PlayerEditGender::onDoneButtonClick(Event::Mouse* event)
{
    Game::getInstance()->popState();
}

void PlayerEditGender::onFemaleButtonPress(Event::Mouse* event)
{
    setGender(GENDER::FEMALE);
}

void PlayerEditGender::onMaleButtonPress(Event::Mouse* event)
{
    setGender(GENDER::MALE);
}

void PlayerEditGender::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
            Game::getInstance()->popState();
            break;
        case SDLK_RETURN:
            Game::getInstance()->player()->setGender(_gender);
            Game::getInstance()->popState();
            break;
        case SDLK_LEFT:
        case SDLK_RIGHT:
            setGender(_gender);
            break;
    }
}

void PlayerEditGender::setGender(GENDER gender)
{
    _gender = gender;
    _maleImage->setCurrentImage(gender == GENDER::MALE ? 0 : 1);
    _femaleImage->setCurrentImage(gender == GENDER::FEMALE ? 1 : 0);
}

}
}
