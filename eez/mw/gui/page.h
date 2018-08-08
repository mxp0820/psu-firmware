/*
 * EEZ Middleware
 * Copyright (C) 2016-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "eez/mw/gui/view.h"

namespace eez {
namespace mw {
namespace gui {

class Page {
public:
    virtual ~Page() {}

	virtual void pageWillAppear();

    virtual bool onEncoder(int counter);
    virtual bool onEncoderClicked();
};

class SetPage : public Page {
public:
	virtual void edit();
	virtual int getDirty() = 0;
	virtual void set() = 0;
	virtual void discard();

protected:
	int editDataId;

	static void onSetValue(float value);
	virtual void setValue(float value);
};

class InternalPage : public Page {
public:
    virtual void refresh() = 0;
    virtual bool drawTick() = 0;
    virtual WidgetCursor findWidget(int x, int y) = 0;
    virtual void drawWidget(const WidgetCursor &widgetCursor, bool selected) = 0;
    virtual int getAction(const WidgetCursor &widgetCursor) = 0;
};

const Style *getSelectFromEnumContainerStyle();
const Style *getSelectFromEnumItemStyle();
const Style *getSelectFromEnumDisabledItemStyle();

class SelectFromEnumPage : public InternalPage {
public:
    SelectFromEnumPage(const data::EnumItem *enumDefinition_, uint8_t currentValue_, bool (*disabledCallback_)(uint8_t value), void (*onSet_)(uint8_t));

    void refresh();
    bool drawTick();
    WidgetCursor findWidget(int x, int y);
    void drawWidget(const WidgetCursor &widgetCursor, bool selected);
    int getAction(const WidgetCursor &widgetCursor);

    void selectEnumItem();

private:
    const data::EnumItem *enumDefinition;
    uint8_t currentValue;
    bool (*disabledCallback)(uint8_t value);
    void (*onSet)(uint8_t);

    int numItems;
    int x;
    int y;
    int width;
    int height;
    int itemWidth;
    int itemHeight;

    bool isDisabled(int i);

    void getItemPosition(int itemIndex, int &x, int &y);
    void getItemLabel(int itemIndex, char *text, int count);
};

}
}
} // namespace eez::mw::gui